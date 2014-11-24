/*
 *  gstvaapiuploader.c - VA-API video upload helper
 *
 *  Copyright (C) 2010-2011 Splitted-Desktop Systems
 *    Author: Gwenole Beauchesne <gwenole.beauchesne@splitted-desktop.com>
 *  Copyright (C) 2011-2013 Intel Corporation
 *    Author: Gwenole Beauchesne <gwenole.beauchesne@intel.com>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation; either version 2.1
 *  of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free
 *  Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301 USA
 */

#include "gst/vaapi/sysdeps.h"
#include <string.h>
#include <gst/video/video.h>
#include <gst/vaapi/gstvaapisurface.h>
#include <gst/vaapi/gstvaapiimagepool.h>
#include <gst/vaapi/gstvaapisurfacepool.h>

#include "gstvaapiuploader.h"
#include "gstvaapipluginutil.h"
#include "gstvaapivideobuffer.h"

#define GST_HELPER_NAME "vaapiupload"
#define GST_HELPER_DESC "VA-API video uploader"

GST_DEBUG_CATEGORY_STATIC (gst_debug_vaapi_uploader);
#define GST_CAT_DEFAULT gst_debug_vaapi_uploader

G_DEFINE_TYPE (GstVaapiUploader, gst_vaapi_uploader, G_TYPE_OBJECT);

#define GST_VAAPI_UPLOADER_CAST(obj) \
  ((GstVaapiUploader *)(obj))
#define GST_VAAPI_UPLOADER_GET_PRIVATE(obj) \
  (G_TYPE_INSTANCE_GET_PRIVATE ((obj), GST_VAAPI_TYPE_UPLOADER,	\
       GstVaapiUploaderPrivate))

struct _GstVaapiUploaderPrivate
{
  GstVaapiDisplay *display;
  GstCaps *allowed_caps;
  GstVaapiVideoPool *images;
  GstVideoInfo image_info;
  GstVaapiVideoPool *surfaces;
  GstVideoInfo surface_info;
  guint direct_rendering;
};

enum
{
  PROP_0,

  PROP_DISPLAY,
};

static void
gst_vaapi_uploader_destroy (GstVaapiUploader * uploader)
{
  GstVaapiUploaderPrivate *const priv = uploader->priv;

  gst_caps_replace (&priv->allowed_caps, NULL);
  gst_vaapi_video_pool_replace (&priv->images, NULL);
  gst_vaapi_video_pool_replace (&priv->surfaces, NULL);
  gst_vaapi_display_replace (&priv->display, NULL);
}

static gboolean
ensure_display (GstVaapiUploader * uploader, GstVaapiDisplay * display)
{
  GstVaapiUploaderPrivate *const priv = uploader->priv;

  gst_vaapi_display_replace (&priv->display, display);
  return TRUE;
}

static gboolean
ensure_image (GstVaapiImage * image)
{
  guint i, num_planes, width, height;

  /* Make the image fully dirty */
  if (!gst_vaapi_image_map (image))
    return FALSE;

  gst_vaapi_image_get_size (image, &width, &height);

  num_planes = gst_vaapi_image_get_plane_count (image);
  for (i = 0; i < num_planes; i++) {
    guchar *const plane = gst_vaapi_image_get_plane (image, i);
    if (plane)
      memset (plane, 0, gst_vaapi_image_get_pitch (image, i));
  }

  if (!gst_vaapi_image_unmap (image))
    gst_vaapi_image_unmap (image);
  return TRUE;
}

static gboolean
ensure_allowed_caps (GstVaapiUploader * uploader)
{
  GstVaapiUploaderPrivate *const priv = uploader->priv;
  GstVaapiSurface *surface = NULL;
  GArray *formats = NULL, *out_formats = NULL;
  GstCaps *out_caps;
  guint i;
  gboolean success = FALSE;

  enum
  { WIDTH = 64, HEIGHT = 64 };

  if (priv->allowed_caps)
    return TRUE;

  formats = gst_vaapi_display_get_image_formats (priv->display);
  if (!formats)
    goto cleanup;

  out_formats = g_array_sized_new (FALSE, FALSE, sizeof (GstVideoFormat),
      formats->len);
  if (!out_formats)
    goto cleanup;

  surface = gst_vaapi_surface_new (priv->display,
      GST_VAAPI_CHROMA_TYPE_YUV420, WIDTH, HEIGHT);
  if (!surface)
    goto cleanup;

  for (i = 0; i < formats->len; i++) {
    const GstVideoFormat format = g_array_index (formats, GstVideoFormat, i);
    GstVaapiImage *image;

    if (format == GST_VIDEO_FORMAT_UNKNOWN)
      continue;
    image = gst_vaapi_image_new (priv->display, format, WIDTH, HEIGHT);
    if (!image)
      continue;
    if (ensure_image (image) && gst_vaapi_surface_put_image (surface, image))
      g_array_append_val (out_formats, format);
    gst_vaapi_object_unref (image);
  }

  out_caps = gst_vaapi_video_format_new_template_caps_from_list (out_formats);
  if (!out_caps)
    goto cleanup;

  gst_caps_replace (&priv->allowed_caps, out_caps);
  gst_caps_unref (out_caps);
  success = TRUE;

cleanup:
  if (out_formats)
    g_array_unref (out_formats);
  if (formats)
    g_array_unref (formats);
  if (surface)
    gst_vaapi_object_unref (surface);
  return success;
}

static gboolean
ensure_image_pool (GstVaapiUploader * uploader, GstCaps * caps,
    gboolean * caps_changed_ptr)
{
  GstVaapiUploaderPrivate *const priv = uploader->priv;
  GstVaapiVideoPool *pool;
  GstVideoInfo vi;
  GstVideoFormat format;
  guint width, height;

  if (!gst_video_info_from_caps (&vi, caps))
    return FALSE;

  format = GST_VIDEO_INFO_FORMAT (&vi);
  width = GST_VIDEO_INFO_WIDTH (&vi);
  height = GST_VIDEO_INFO_HEIGHT (&vi);

  *caps_changed_ptr =
      format != GST_VIDEO_INFO_FORMAT (&priv->image_info) ||
      width != GST_VIDEO_INFO_WIDTH (&priv->image_info) ||
      height != GST_VIDEO_INFO_HEIGHT (&priv->image_info);
  if (!*caps_changed_ptr)
    return TRUE;

  pool = gst_vaapi_image_pool_new (priv->display, &vi);
  if (!pool)
    return FALSE;

  gst_video_info_set_format (&priv->image_info, format, width, height);
  gst_vaapi_video_pool_replace (&priv->images, pool);
  gst_vaapi_video_pool_unref (pool);
  return TRUE;
}

static gboolean
ensure_surface_pool (GstVaapiUploader * uploader, GstCaps * caps,
    gboolean * caps_changed_ptr)
{
  GstVaapiUploaderPrivate *const priv = uploader->priv;
  GstVaapiVideoPool *pool;
  GstVideoInfo vi;
  GstVideoFormat format;
  guint width, height;

  if (!gst_video_info_from_caps (&vi, caps))
    return FALSE;

  format = GST_VIDEO_INFO_FORMAT (&vi);
  width = GST_VIDEO_INFO_WIDTH (&vi);
  height = GST_VIDEO_INFO_HEIGHT (&vi);

  *caps_changed_ptr =
      format != GST_VIDEO_INFO_FORMAT (&priv->surface_info) ||
      width != GST_VIDEO_INFO_WIDTH (&priv->surface_info) ||
      height != GST_VIDEO_INFO_HEIGHT (&priv->surface_info);
  if (!*caps_changed_ptr)
    return TRUE;

  /* Always try to downsample source buffers to YUV 4:2:0 format as
     this saves memory bandwidth for further rendering */
  /* XXX: this also means that visual quality is not preserved */
  if (format != GST_VIDEO_FORMAT_ENCODED) {
    const GstVaapiChromaType chroma_type =
        gst_vaapi_video_format_get_chroma_type (format);
    if (chroma_type != GST_VAAPI_CHROMA_TYPE_YUV420) {
      const GstVideoFormat image_format =
          GST_VIDEO_INFO_FORMAT (&priv->image_info);
      GST_INFO ("use implicit conversion of %s buffers to NV12 surfaces",
          gst_video_format_to_string (image_format));
      gst_video_info_set_format (&vi, GST_VIDEO_FORMAT_NV12, width, height);
    }
  }

  pool = gst_vaapi_surface_pool_new (priv->display, &vi);
  if (!pool)
    return FALSE;

  gst_video_info_set_format (&priv->surface_info, format, width, height);
  gst_vaapi_video_pool_replace (&priv->surfaces, pool);
  gst_vaapi_video_pool_unref (pool);
  return TRUE;
}

static void
gst_vaapi_uploader_finalize (GObject * object)
{
  gst_vaapi_uploader_destroy (GST_VAAPI_UPLOADER_CAST (object));

  G_OBJECT_CLASS (gst_vaapi_uploader_parent_class)->finalize (object);
}

static void
gst_vaapi_uploader_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstVaapiUploader *const uploader = GST_VAAPI_UPLOADER_CAST (object);

  switch (prop_id) {
    case PROP_DISPLAY:
      ensure_display (uploader, g_value_get_pointer (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
gst_vaapi_uploader_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  GstVaapiUploader *const uploader = GST_VAAPI_UPLOADER_CAST (object);

  switch (prop_id) {
    case PROP_DISPLAY:
      g_value_set_pointer (value, uploader->priv->display);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
gst_vaapi_uploader_class_init (GstVaapiUploaderClass * klass)
{
  GObjectClass *const object_class = G_OBJECT_CLASS (klass);

  GST_DEBUG_CATEGORY_INIT (gst_debug_vaapi_uploader,
      GST_HELPER_NAME, 0, GST_HELPER_DESC);

  g_type_class_add_private (klass, sizeof (GstVaapiUploaderPrivate));

  object_class->finalize = gst_vaapi_uploader_finalize;
  object_class->set_property = gst_vaapi_uploader_set_property;
  object_class->get_property = gst_vaapi_uploader_get_property;

  g_object_class_install_property (object_class,
      PROP_DISPLAY,
      g_param_spec_pointer ("display",
          "Display",
          "The GstVaapiDisplay this object is bound to",
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));
}

static void
gst_vaapi_uploader_init (GstVaapiUploader * uploader)
{
  GstVaapiUploaderPrivate *priv;

  priv = GST_VAAPI_UPLOADER_GET_PRIVATE (uploader);
  uploader->priv = priv;

  gst_video_info_init (&priv->image_info);
  gst_video_info_init (&priv->surface_info);
}

GstVaapiUploader *
gst_vaapi_uploader_new (GstVaapiDisplay * display)
{
  return g_object_new (GST_VAAPI_TYPE_UPLOADER, "display", display, NULL);
}

gboolean
gst_vaapi_uploader_ensure_display (GstVaapiUploader * uploader,
    GstVaapiDisplay * display)
{
  g_return_val_if_fail (GST_VAAPI_IS_UPLOADER (uploader), FALSE);
  g_return_val_if_fail (display != NULL, FALSE);

  return ensure_display (uploader, display);
}

gboolean
gst_vaapi_uploader_ensure_caps (GstVaapiUploader * uploader,
    GstCaps * src_caps, GstCaps * out_caps)
{
  GstVaapiUploaderPrivate *priv;
  GstVaapiImage *image;
  gboolean image_caps_changed, surface_caps_changed;

  g_return_val_if_fail (GST_VAAPI_IS_UPLOADER (uploader), FALSE);
  g_return_val_if_fail (src_caps != NULL, FALSE);

  if (!out_caps)
    out_caps = src_caps;

  if (!ensure_image_pool (uploader, src_caps, &image_caps_changed))
    return FALSE;
  if (!ensure_surface_pool (uploader, out_caps, &surface_caps_changed))
    return FALSE;
  if (!image_caps_changed && !surface_caps_changed)
    return TRUE;

  priv = uploader->priv;
  priv->direct_rendering = 0;

  /* Check if we can alias source and output buffers (same data_size) */
  image = gst_vaapi_video_pool_get_object (priv->images);
  if (image) {
    if ((gst_vaapi_image_get_format (image) ==
            GST_VIDEO_INFO_FORMAT (&priv->image_info)) &&
        gst_vaapi_image_is_linear (image) &&
        (gst_vaapi_image_get_data_size (image) ==
            GST_VIDEO_INFO_SIZE (&priv->image_info)))
      priv->direct_rendering = 1;
    gst_vaapi_video_pool_put_object (priv->images, image);
  }

  GST_INFO ("direct-rendering: level %u", priv->direct_rendering);
  return TRUE;
}

gboolean
gst_vaapi_uploader_process (GstVaapiUploader * uploader,
    GstBuffer * src_buffer, GstBuffer * out_buffer)
{
  GstVaapiVideoMeta *src_meta, *out_meta;
  GstVaapiSurface *surface;
  GstVaapiImage *image;

  g_return_val_if_fail (GST_VAAPI_IS_UPLOADER (uploader), FALSE);

  out_meta = gst_buffer_get_vaapi_video_meta (out_buffer);
  if (!out_meta) {
    GST_WARNING ("expected an output video buffer");
    return FALSE;
  }

  surface = gst_vaapi_video_meta_get_surface (out_meta);
  g_return_val_if_fail (surface != NULL, FALSE);

  src_meta = gst_buffer_get_vaapi_video_meta (src_buffer);
  if (src_meta) {
    /* GstVaapiVideoBuffer with mapped VA image */
    image = gst_vaapi_video_meta_get_image (src_meta);
    if (!image || !gst_vaapi_image_unmap (image))
      return FALSE;
  } else {
    /* Regular GstBuffer that needs to be uploaded to a VA image */
    image = gst_vaapi_video_meta_get_image (out_meta);
    if (!image) {
      image = gst_vaapi_video_pool_get_object (uploader->priv->images);
      if (!image)
        return FALSE;
      gst_vaapi_video_meta_set_image (out_meta, image);
    }
    if (!gst_vaapi_image_update_from_buffer (image, src_buffer, NULL))
      return FALSE;
  }
  g_return_val_if_fail (image != NULL, FALSE);

  if (!gst_vaapi_surface_put_image (surface, image)) {
    GST_WARNING ("failed to upload YUV buffer to VA surface");
    return FALSE;
  }

  /* Map again for next uploads */
  if (!gst_vaapi_image_map (image))
    return FALSE;
  return TRUE;
}

GstCaps *
gst_vaapi_uploader_get_caps (GstVaapiUploader * uploader)
{
  g_return_val_if_fail (GST_VAAPI_IS_UPLOADER (uploader), NULL);

  if (!ensure_allowed_caps (uploader))
    return NULL;
  return uploader->priv->allowed_caps;
}

GstBuffer *
gst_vaapi_uploader_get_buffer (GstVaapiUploader * uploader)
{
  GstVaapiUploaderPrivate *priv;
  GstVaapiImage *image;
  GstVaapiVideoMeta *meta;
  GstVaapiSurfaceProxy *proxy;
  GstBuffer *buffer;

  g_return_val_if_fail (GST_VAAPI_IS_UPLOADER (uploader), NULL);

  priv = uploader->priv;

  buffer = gst_vaapi_video_buffer_new_from_pool (priv->images);
  if (!buffer) {
    GST_WARNING ("failed to allocate video buffer");
    goto error;
  }

  proxy =
      gst_vaapi_surface_proxy_new_from_pool (GST_VAAPI_SURFACE_POOL
      (priv->surfaces));
  if (!proxy) {
    GST_WARNING ("failed to allocate VA surface");
    goto error;
  }

  meta = gst_buffer_get_vaapi_video_meta (buffer);
  gst_vaapi_video_meta_set_surface_proxy (meta, proxy);
  gst_vaapi_surface_proxy_unref (proxy);

  image = gst_vaapi_video_meta_get_image (meta);
  if (!gst_vaapi_image_map (image)) {
    GST_WARNING ("failed to map VA image");
    goto error;
  }
#if !GST_CHECK_VERSION(1,0,0)
  GST_BUFFER_DATA (buffer) = gst_vaapi_image_get_plane (image, 0);
  GST_BUFFER_SIZE (buffer) = gst_vaapi_image_get_data_size (image);
#endif
  return buffer;

error:
  gst_buffer_unref (buffer);
  return buffer;
}

gboolean
gst_vaapi_uploader_has_direct_rendering (GstVaapiUploader * uploader)
{
  g_return_val_if_fail (GST_VAAPI_IS_UPLOADER (uploader), FALSE);

  return uploader->priv->direct_rendering;
}
