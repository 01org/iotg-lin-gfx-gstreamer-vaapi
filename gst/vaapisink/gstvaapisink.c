/*
 *  gstvaapisink.c - VA-API video sink
 *
 *  gstreamer-vaapi (C) 2010 Splitted-Desktop Systems
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

/**
 * SECTION:gstvaapisink
 * @short_description: A VA-API based videosink
 *
 * vaapisink renders video frames to a drawable (X #Window) on a local
 * display using the Video Acceleration (VA) API. The element will
 * create its own internal window and render into it.
 */

#include "config.h"
#include <gst/gst.h>
#include <gst/video/video.h>
#include <gst/vaapi/gstvaapivideobuffer.h>
#include <gst/vaapi/gstvaapivideosink.h>
#include <gst/vaapi/gstvaapidisplay_x11.h>
#include <gst/vaapi/gstvaapiwindow_x11.h>
#if USE_VAAPISINK_GLX
#include <gst/vaapi/gstvaapidisplay_glx.h>
#include <gst/vaapi/gstvaapiwindow_glx.h>
#endif
#include "gstvaapisink.h"

#define GST_PLUGIN_NAME "vaapisink"
#define GST_PLUGIN_DESC "A VA-API based videosink"

GST_DEBUG_CATEGORY_STATIC(gst_debug_vaapisink);
#define GST_CAT_DEFAULT gst_debug_vaapisink

/* ElementFactory information */
static const GstElementDetails gst_vaapisink_details =
    GST_ELEMENT_DETAILS(
        "VA-API sink",
        "Sink/Video",
        GST_PLUGIN_DESC,
        "Gwenole Beauchesne <gbeauchesne@splitted-desktop.com>");

/* Default template */
static GstStaticPadTemplate gst_vaapisink_sink_factory =
    GST_STATIC_PAD_TEMPLATE(
        "sink",
        GST_PAD_SINK,
        GST_PAD_ALWAYS,
        GST_STATIC_CAPS(GST_VAAPI_SURFACE_CAPS));

static void gst_vaapisink_iface_init(GType type);

GST_BOILERPLATE_FULL(
    GstVaapiSink,
    gst_vaapisink,
    GstVideoSink,
    GST_TYPE_VIDEO_SINK,
    gst_vaapisink_iface_init);

enum {
    PROP_0,

    PROP_USE_GLX,
    PROP_DISPLAY,
    PROP_FULLSCREEN,
    PROP_SYNCHRONOUS,
    PROP_USE_REFLECTION
};

static GstVaapiDisplay *
gst_vaapisink_get_display(GstVaapiSink *sink);

static GstVaapiDisplay *
gst_vaapi_video_sink_do_get_display(GstVaapiVideoSink *sink)
{
    return gst_vaapisink_get_display(GST_VAAPISINK(sink));
}

static void gst_vaapi_video_sink_iface_init(GstVaapiVideoSinkInterface *iface)
{
    iface->get_display = gst_vaapi_video_sink_do_get_display;
}

static void gst_vaapisink_iface_init(GType type)
{
    const GType g_define_type_id = type;

    G_IMPLEMENT_INTERFACE(GST_VAAPI_TYPE_VIDEO_SINK,
                          gst_vaapi_video_sink_iface_init);
}

static void
gst_vaapisink_destroy(GstVaapiSink *sink)
{
    if (sink->display) {
        g_object_unref(sink->display);
        sink->display = NULL;
    }

    if (sink->display_name) {
        g_free(sink->display_name);
        sink->display_name = NULL;
    }
}

static inline gboolean
gst_vaapisink_ensure_window(GstVaapiSink *sink, guint width, guint height)
{
    GstVaapiDisplay * const display = sink->display;

    if (!sink->window) {
#if USE_VAAPISINK_GLX
        if (sink->use_glx)
            sink->window = gst_vaapi_window_glx_new(display, width, height);
        else
#endif
            sink->window = gst_vaapi_window_x11_new(display, width, height);
    }
    return sink->window != NULL;
}

static inline gboolean
gst_vaapisink_ensure_display(GstVaapiSink *sink)
{
    if (!sink->display) {
#if USE_VAAPISINK_GLX
        if (sink->use_glx)
            sink->display = gst_vaapi_display_glx_new(sink->display_name);
        else
#endif
            sink->display = gst_vaapi_display_x11_new(sink->display_name);
        if (!sink->display || !gst_vaapi_display_get_display(sink->display))
            return FALSE;
        g_object_set(sink, "synchronous", sink->synchronous, NULL);
    }
    return sink->display != NULL;
}

static gboolean
gst_vaapisink_start(GstBaseSink *base_sink)
{
    GstVaapiSink * const sink = GST_VAAPISINK(base_sink);

    if (!gst_vaapisink_ensure_display(sink))
        return FALSE;
    return TRUE;
}

static gboolean
gst_vaapisink_stop(GstBaseSink *base_sink)
{
    GstVaapiSink * const sink = GST_VAAPISINK(base_sink);

    if (sink->window) {
        g_object_unref(sink->window);
        sink->window = NULL;
    }

    if (sink->display) {
        g_object_unref(sink->display);
        sink->display = NULL;
    }
    return TRUE;
}

static gboolean
gst_vaapisink_set_caps(GstBaseSink *base_sink, GstCaps *caps)
{
    GstVaapiSink * const sink = GST_VAAPISINK(base_sink);
    GstStructure * const structure = gst_caps_get_structure(caps, 0);
    GstVaapiRectangle * const disp_rect = &sink->display_rect;
    guint num, den;
    guint win_width, win_height;
    guint display_width, display_height, display_par_n, display_par_d;
    gint video_width, video_height, video_par_n = 1, video_par_d = 1;
    gdouble win_ratio;

    if (!structure)
        return FALSE;
    if (!gst_structure_get_int(structure, "width",  &video_width))
        return FALSE;
    if (!gst_structure_get_int(structure, "height", &video_height))
        return FALSE;
    sink->video_width  = video_width;
    sink->video_height = video_height;

    gst_video_parse_caps_pixel_aspect_ratio(caps, &video_par_n, &video_par_d);
    gst_vaapi_display_get_size(sink->display, &display_width, &display_height);
    gst_vaapi_display_get_pixel_aspect_ratio(
        sink->display,
        &display_par_n, &display_par_d
    );

    if (!gst_video_calculate_display_ratio(&num, &den,
                                           video_width, video_height,
                                           video_par_n, video_par_d,
                                           display_par_n, display_par_d))
        return FALSE;
    GST_DEBUG("video size %dx%d, calculated display ratio %d/%d",
              video_width, video_height, num, den);

    if ((video_height % den) == 0) {
        GST_DEBUG("keeping video height");
        win_width  = gst_util_uint64_scale_int(video_height, num, den);
        win_height = video_height;
    }
    else if ((video_width % num) == 0) {
        GST_DEBUG("keeping video width");
        win_width  = video_width;
        win_height = gst_util_uint64_scale_int(video_width, den, num);
    }
    else {
        GST_DEBUG("approximating while keeping video height");
        win_width  = gst_util_uint64_scale_int (video_height, num, den);
        win_height = video_height;
    }
    win_ratio = (gdouble)win_width / win_height;
    GST_DEBUG("scaling to %ux%u", win_width, win_height);

    if (sink->fullscreen ||
        win_width > display_width || win_height > display_height) {
        if (video_width > video_height) {
            win_width  = display_width;
            win_height = display_width / win_ratio;
        }
        else {
            win_width  = display_height * win_ratio;
            win_height = display_height;
        }
    }
    GST_DEBUG("window size %ux%u", win_width, win_height);

    if (sink->fullscreen) {
        disp_rect->x  = (display_width - win_width) / 2;
        disp_rect->y  = (display_height - win_height) / 2;
    }
    else {
        disp_rect->x  = 0;
        disp_rect->y  = 0;
    }
    disp_rect->width  = win_width;
    disp_rect->height = win_height;

    if (sink->window)
        gst_vaapi_window_set_size(sink->window, win_width, win_height);
    else {
        if (sink->fullscreen) {
            win_width  = display_width;
            win_height = display_height;
        }
        if (!gst_vaapisink_ensure_window(sink, win_width, win_height))
            return FALSE;
        gst_vaapi_window_set_fullscreen(sink->window, sink->fullscreen);
        gst_vaapi_window_show(sink->window);
    }
    sink->window_width  = win_width;
    sink->window_height = win_height;
    return TRUE;
}

static GstFlowReturn
gst_vaapisink_buffer_alloc(
    GstBaseSink *base_sink,
    guint64      offset,
    guint        size,
    GstCaps     *caps,
    GstBuffer  **pout_buffer
)
{
    GstVaapiSink * const sink = GST_VAAPISINK(base_sink);
    GstBuffer *buffer;
    GstCaps *sink_caps;

    sink_caps = gst_static_pad_template_get_caps(&gst_vaapisink_sink_factory);
    if (!sink_caps)
        goto error_no_sink_caps;

    if (!gst_caps_is_always_compatible(caps, sink_caps))
        goto error_invalid_caps;

    buffer = gst_vaapi_video_buffer_new(sink->display);
    if (!buffer)
        goto error_create_buffer;

    gst_buffer_set_caps(buffer, caps);
    gst_caps_unref(sink_caps);
    *pout_buffer = buffer;
    return GST_FLOW_OK;

    /* ERRORS */
error_no_sink_caps:
    {
        GST_DEBUG("failed to get static sink caps");
        return GST_FLOW_UNEXPECTED;
    }
error_invalid_caps:
    {
        GST_DEBUG("failed to validate input caps");
        gst_caps_unref(sink_caps);
        return GST_FLOW_UNEXPECTED;
    }
error_create_buffer:
    {
        GST_DEBUG("failed to create video buffer");
        gst_caps_unref(sink_caps);
        return GST_FLOW_UNEXPECTED;
    }
}

#if USE_VAAPISINK_GLX
static void
render_background(GstVaapiSink *sink)
{
    /* Original code from Mirco Muller (MacSlow):
       <http://cgit.freedesktop.org/~macslow/gl-gst-player/> */
    GLfloat fStartX = 0.0f;
    GLfloat fStartY = 0.0f;
    GLfloat fWidth  = (GLfloat)sink->window_width;
    GLfloat fHeight = (GLfloat)sink->window_height;

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    {
        /* top third, darker grey to white */
        glColor3f(0.85f, 0.85f, 0.85f);
        glVertex3f(fStartX, fStartY, 0.0f);
        glColor3f(0.85f, 0.85f, 0.85f);
        glVertex3f(fStartX + fWidth, fStartY, 0.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(fStartX + fWidth, fStartY + fHeight / 3.0f, 0.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(fStartX, fStartY + fHeight / 3.0f, 0.0f);

        /* middle third, just plain white */
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(fStartX, fStartY + fHeight / 3.0f, 0.0f);
        glVertex3f(fStartX + fWidth, fStartY + fHeight / 3.0f, 0.0f);
        glVertex3f(fStartX + fWidth, fStartY + 2.0f * fHeight / 3.0f, 0.0f);
        glVertex3f(fStartX, fStartY + 2.0f * fHeight / 3.0f, 0.0f);

        /* bottom third, white to lighter grey */
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(fStartX, fStartY + 2.0f * fHeight / 3.0f, 0.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(fStartX + fWidth, fStartY + 2.0f * fHeight / 3.0f, 0.0f);
        glColor3f(0.62f, 0.66f, 0.69f);
        glVertex3f(fStartX + fWidth, fStartY + fHeight, 0.0f);
        glColor3f(0.62f, 0.66f, 0.69f);
        glVertex3f(fStartX, fStartY + fHeight, 0.0f);
    }
    glEnd();
}

static void
render_frame(GstVaapiSink *sink)
{
    const guint x1 = sink->display_rect.x;
    const guint x2 = sink->display_rect.x + sink->display_rect.width;
    const guint y1 = sink->display_rect.y;
    const guint y2 = sink->display_rect.y + sink->display_rect.height;

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    {
        glTexCoord2f(0.0f, 0.0f); glVertex2i(x1, y1);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(x1, y2);
        glTexCoord2f(1.0f, 1.0f); glVertex2i(x2, y2);
        glTexCoord2f(1.0f, 0.0f); glVertex2i(x2, y1);
    }
    glEnd();
}

static void
render_reflection(GstVaapiSink *sink)
{
    const guint x1 = sink->display_rect.x;
    const guint x2 = sink->display_rect.x + sink->display_rect.width;
    const guint y1 = sink->display_rect.y;
    const guint rh = sink->display_rect.height / 5;
    GLfloat     ry = 1.0f - (GLfloat)rh / (GLfloat)sink->display_rect.height;

    glBegin(GL_QUADS);
    {
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(x1, y1);
        glTexCoord2f(1.0f, 1.0f); glVertex2i(x2, y1);

        glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
        glTexCoord2f(1.0f, ry); glVertex2i(x2, y1 + rh);
        glTexCoord2f(0.0f, ry); glVertex2i(x1, y1 + rh);
    }
    glEnd();
}

static gboolean
gst_vaapisink_show_frame_glx(GstVaapiSink *sink)
{
    GstVaapiWindowGLX * const window = GST_VAAPI_WINDOW_GLX(sink->window);
    GLenum target;
    GLuint texture;

    if (!sink->use_reflection)
        return gst_vaapi_window_glx_put_texture(window, sink->texture,
                                                NULL, &sink->display_rect);

    target  = gst_vaapi_texture_get_target(sink->texture);
    texture = gst_vaapi_texture_get_id(sink->texture);
    if (target != GL_TEXTURE_2D || !texture)
        return FALSE;

    render_background(sink);

    glEnable(target);
    glBindTexture(target, texture);
    {
        glPushMatrix();
        glRotatef(20.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(50.0f, 0.0f, 0.0f);
        render_frame(sink);
        glPushMatrix();
        glTranslatef(0.0, (GLfloat)sink->display_rect.height + 5.0f, 0.0f);
        render_reflection(sink);
        glPopMatrix();
        glPopMatrix();
    }
    glBindTexture(target, 0);
    glDisable(target);
    return TRUE;
}
#endif

static GstFlowReturn
gst_vaapisink_show_frame(GstBaseSink *base_sink, GstBuffer *buffer)
{
    GstVaapiSink * const sink = GST_VAAPISINK(base_sink);
    GstVaapiVideoBuffer * const vbuffer = GST_VAAPI_VIDEO_BUFFER(buffer);
    GstVaapiSurface *surface;
    guint flags;

    if (!sink->window)
        return GST_FLOW_UNEXPECTED;

    surface = gst_vaapi_video_buffer_get_surface(vbuffer);
    if (!surface)
        return GST_FLOW_UNEXPECTED;

    flags = GST_VAAPI_PICTURE_STRUCTURE_FRAME;

#if USE_VAAPISINK_GLX
    if (sink->use_glx) {
        GstVaapiWindowGLX * const window = GST_VAAPI_WINDOW_GLX(sink->window);
        gst_vaapi_window_glx_make_current(window);
        if (!sink->texture) {
            sink->texture = gst_vaapi_texture_new(
                sink->display,
                GL_TEXTURE_2D,
                GL_BGRA,
                sink->video_width,
                sink->video_height
            );
            if (!sink->texture) {
                GST_DEBUG("could not create VA/GLX texture");
                return GST_FLOW_UNEXPECTED;
            }
        }
        if (!gst_vaapi_texture_put_surface(sink->texture, surface, flags)) {
            GST_DEBUG("could not transfer VA surface to texture");
            return GST_FLOW_UNEXPECTED;
        }
        if (!gst_vaapisink_show_frame_glx(sink)) {
            GST_DEBUG("could not render VA/GLX texture");
            return GST_FLOW_UNEXPECTED;
        }
        gst_vaapi_window_glx_swap_buffers(window);
        return GST_FLOW_OK;
    }
#endif

    if (!gst_vaapi_window_put_surface(sink->window, surface,
                                      NULL, &sink->display_rect, flags)) {
        GST_DEBUG("could not render VA surface");
        return GST_FLOW_UNEXPECTED;
    }
    return GST_FLOW_OK;
}

static void
gst_vaapisink_finalize(GObject *object)
{
    gst_vaapisink_destroy(GST_VAAPISINK(object));

    G_OBJECT_CLASS(parent_class)->finalize(object);
}

static void
gst_vaapisink_set_property(
    GObject      *object,
    guint         prop_id,
    const GValue *value,
    GParamSpec   *pspec
)
{
    GstVaapiSink * const sink = GST_VAAPISINK(object);

    switch (prop_id) {
    case PROP_USE_GLX:
        sink->use_glx = g_value_get_boolean(value);
        break;
    case PROP_DISPLAY:
        g_free(sink->display_name);
        sink->display_name = g_strdup(g_value_get_string(value));
        break;
    case PROP_FULLSCREEN:
        sink->fullscreen = g_value_get_boolean(value);
        break;
    case PROP_SYNCHRONOUS:
        sink->synchronous = g_value_get_boolean(value);
        break;
    case PROP_USE_REFLECTION:
        sink->use_reflection = g_value_get_boolean(value);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}

static void
gst_vaapisink_get_property(
    GObject    *object,
    guint       prop_id,
    GValue     *value,
    GParamSpec *pspec
)
{
    GstVaapiSink * const sink = GST_VAAPISINK(object);

    switch (prop_id) {
    case PROP_USE_GLX:
        g_value_set_boolean(value, sink->use_glx);
        break;
    case PROP_DISPLAY:
        g_value_set_string(value, sink->display_name);
        break;
    case PROP_FULLSCREEN:
        g_value_set_boolean(value, sink->fullscreen);
        break;
    case PROP_SYNCHRONOUS:
        g_value_set_boolean(value, sink->synchronous);
        break;
    case PROP_USE_REFLECTION:
        g_value_set_boolean(value, sink->use_reflection);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}

static void gst_vaapisink_base_init(gpointer klass)
{
    GstElementClass * const element_class = GST_ELEMENT_CLASS(klass);

    gst_element_class_set_details(element_class, &gst_vaapisink_details);

    gst_element_class_add_pad_template(
        element_class,
        gst_static_pad_template_get(&gst_vaapisink_sink_factory)
    );
}

static void gst_vaapisink_class_init(GstVaapiSinkClass *klass)
{
    GObjectClass * const     object_class   = G_OBJECT_CLASS(klass);
    GstBaseSinkClass * const basesink_class = GST_BASE_SINK_CLASS(klass);

    object_class->finalize       = gst_vaapisink_finalize;
    object_class->set_property   = gst_vaapisink_set_property;
    object_class->get_property   = gst_vaapisink_get_property;

    basesink_class->start        = gst_vaapisink_start;
    basesink_class->stop         = gst_vaapisink_stop;
    basesink_class->set_caps     = gst_vaapisink_set_caps;
    basesink_class->buffer_alloc = gst_vaapisink_buffer_alloc;
    basesink_class->preroll      = gst_vaapisink_show_frame;
    basesink_class->render       = gst_vaapisink_show_frame;

#if USE_VAAPISINK_GLX
    g_object_class_install_property
        (object_class,
         PROP_USE_GLX,
         g_param_spec_boolean("use-glx",
                              "GLX rendering",
                              "Enables GLX rendering",
                              TRUE,
                              G_PARAM_READWRITE));

    g_object_class_install_property
        (object_class,
         PROP_USE_REFLECTION,
         g_param_spec_boolean("use-reflection",
                              "Reflection effect",
                              "Enables OpenGL reflection effect",
                              FALSE,
                              G_PARAM_READWRITE));
#endif

    g_object_class_install_property
        (object_class,
         PROP_DISPLAY,
         g_param_spec_string("display",
                             "X11 display name",
                             "X11 display name",
                             "",
                             G_PARAM_READWRITE));

    g_object_class_install_property
        (object_class,
         PROP_FULLSCREEN,
         g_param_spec_boolean("fullscreen",
                              "Fullscreen",
                              "Requests window in fullscreen state",
                              FALSE,
                              G_PARAM_READWRITE));

    /**
     * GstVaapiSink:synchronous:
     *
     * When enabled, runs the X display in synchronous mode. Note that
     * this is used only for debugging.
     */
    g_object_class_install_property
        (object_class,
         PROP_SYNCHRONOUS,
         g_param_spec_boolean("synchronous",
                              "Synchronous mode",
                              "Toggles X display synchronous mode",
                              FALSE,
                              G_PARAM_READWRITE));
}

static void gst_vaapisink_init(GstVaapiSink *sink, GstVaapiSinkClass *klass)
{
    sink->display_name   = NULL;
    sink->display        = NULL;
    sink->window         = NULL;
    sink->window_width   = 0;
    sink->window_height  = 0;
    sink->texture        = NULL;
    sink->video_width    = 0;
    sink->video_height   = 0;
    sink->fullscreen     = FALSE;
    sink->synchronous    = FALSE;
    sink->use_glx        = USE_VAAPISINK_GLX;
    sink->use_reflection = FALSE;
}

GstVaapiDisplay *
gst_vaapisink_get_display(GstVaapiSink *sink)
{
    if (!gst_vaapisink_ensure_display(sink))
        return NULL;
    return sink->display;
}

static gboolean plugin_init(GstPlugin *plugin)
{
    GST_DEBUG_CATEGORY_INIT(gst_debug_vaapisink,
                            GST_PLUGIN_NAME, 0, GST_PLUGIN_DESC);

    return gst_element_register(plugin,
                                GST_PLUGIN_NAME,
                                GST_RANK_NONE,
                                GST_TYPE_VAAPISINK);
}

GST_PLUGIN_DEFINE(
    GST_VERSION_MAJOR, GST_VERSION_MINOR,
    GST_PLUGIN_NAME,
    GST_PLUGIN_DESC,
    plugin_init,
    PACKAGE_VERSION,
    "GPL",
    PACKAGE,
    PACKAGE_BUGREPORT);
