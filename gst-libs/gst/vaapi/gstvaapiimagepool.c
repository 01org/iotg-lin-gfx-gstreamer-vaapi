/*
 *  gstvaapiimagepool.c - Gst VA image pool
 *
 *  Copyright (C) 2010-2011 Splitted-Desktop Systems
 *  Copyright (C) 2012 Intel Corporation
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

/**
 * SECTION:gstvaapiimagepool
 * @short_description: VA image pool
 */

#include "sysdeps.h"
#include "gstvaapiimagepool.h"
#include "gstvaapivideopool_priv.h"

#define DEBUG 1
#include "gstvaapidebug.h"

/**
 * GstVaapiImagePool:
 *
 * A pool of lazily allocated #GstVaapiImage objects.
 */
struct _GstVaapiImagePool {
    /*< private >*/
    GstVaapiVideoPool   parent_instance;

    GstVaapiImageFormat format;
    guint               width;
    guint               height;
};

static gboolean
gst_vaapi_image_pool_set_caps(GstVaapiVideoPool *base_pool, GstCaps *caps)
{
    GstVaapiImagePool * const pool = GST_VAAPI_IMAGE_POOL(base_pool);
    GstVideoInfo vi;

    if (!gst_video_info_from_caps(&vi, caps))
        return FALSE;

    pool->format = gst_vaapi_image_format_from_video(GST_VIDEO_INFO_FORMAT(&vi));
    pool->width  = GST_VIDEO_INFO_WIDTH(&vi);
    pool->height = GST_VIDEO_INFO_HEIGHT(&vi);
    return TRUE;
}

static gpointer
gst_vaapi_image_pool_alloc_object(GstVaapiVideoPool *base_pool)
{
    GstVaapiImagePool * const pool = GST_VAAPI_IMAGE_POOL(base_pool);

    return gst_vaapi_image_new(base_pool->display, pool->format,
        pool->width, pool->height);
}

static inline const GstVaapiMiniObjectClass *
gst_vaapi_image_pool_class(void)
{
    static const GstVaapiVideoPoolClass GstVaapiImagePoolClass = {
        { sizeof(GstVaapiImagePool),
          (GDestroyNotify)gst_vaapi_video_pool_finalize },

        .alloc_object   = gst_vaapi_image_pool_alloc_object
    };
    return GST_VAAPI_MINI_OBJECT_CLASS(&GstVaapiImagePoolClass);
}

/**
 * gst_vaapi_image_pool_new:
 * @display: a #GstVaapiDisplay
 * @caps: a #GstCaps
 *
 * Creates a new #GstVaapiVideoPool of #GstVaapiImage with the
 * specified dimensions in @caps.
 *
 * Return value: the newly allocated #GstVaapiVideoPool
 */
GstVaapiVideoPool *
gst_vaapi_image_pool_new(GstVaapiDisplay *display, GstCaps *caps)
{
    GstVaapiVideoPool *pool;

    g_return_val_if_fail(GST_VAAPI_IS_DISPLAY(display), NULL);
    g_return_val_if_fail(GST_IS_CAPS(caps), NULL);

    pool = (GstVaapiVideoPool *)
        gst_vaapi_mini_object_new(gst_vaapi_image_pool_class());
    if (!pool)
        return NULL;

    gst_vaapi_video_pool_init(pool, display);
    if (!gst_vaapi_image_pool_set_caps(pool, caps))
        goto error;
    return pool;

error:
    gst_vaapi_mini_object_unref(GST_VAAPI_MINI_OBJECT(pool));
    return NULL;
}
