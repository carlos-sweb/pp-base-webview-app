const std = @import("std");
const gtk = @cImport({
    @cInclude("gtk/gtk.h");
    @cInclude("webkit/webkit.h");
});

// ---------------------------------------------------------------------------
// on_title_changed
// ---------------------------------------------------------------------------
fn onTitleChanged(
    web_view: ?*gtk.WebKitWebView,
    _: ?*gtk.GParamSpec,
    user_data: gtk.gpointer,
) callconv(.c) void {
    const window: *gtk.GtkWindow = @ptrCast(@alignCast(user_data));
    const title = gtk.webkit_web_view_get_title(web_view);
    if (title != null) {
        gtk.gtk_window_set_title(window, title);
    }
}

// ---------------------------------------------------------------------------
// on_load_changed
// ---------------------------------------------------------------------------
fn onLoadChanged(
    web_view: ?*gtk.WebKitWebView,
    load_event: gtk.WebKitLoadEvent,
    _: gtk.gpointer,
) callconv(.c) void {
    if (load_event == gtk.WEBKIT_LOAD_FINISHED) {
        const title = gtk.webkit_web_view_get_title(web_view);
        if (title != null) {
            std.debug.print("Load finished. Current page title: {s}\n", .{title});
        } else {
            std.debug.print("Load finished. No title available.\n", .{});
        }
    }
}

// ---------------------------------------------------------------------------
// on_ready  — oculta el webview hasta que JS dispare "ready"
// ---------------------------------------------------------------------------
fn onReady(
    _: ?*gtk.WebKitUserContentManager,
    _: ?*gtk.JSCValue,
    user_data: gtk.gpointer,
) callconv(.c) void {
    const webview: *gtk.WebKitWebView = @ptrCast(@alignCast(user_data));

    if (gtk.gtk_widget_get_visible(@ptrCast(webview)) == 0) {
        gtk.gtk_widget_set_visible(@ptrCast(webview), 1);
    }

    // Desconectar el handler para que solo se llame una vez
    //_ = gtk.g_signal_handlers_disconnect_by_func(
    // self,
    // @as(gtk.gpointer, @ptrCast(@constCast(&onReady))),
    // user_data,
    //);
}

// ---------------------------------------------------------------------------
// on_ready_show
// ---------------------------------------------------------------------------
fn onReadyShow(_: ?*gtk.WebKitWebView) callconv(.c) void {
    std.debug.print("on_ready_show\n", .{});
}

// ---------------------------------------------------------------------------
// custom_scheme_handler  — sirve archivos desde GResources con esquema "app://"
// ---------------------------------------------------------------------------
fn customSchemeHandler(
    request: ?*gtk.WebKitURISchemeRequest,
    _: gtk.gpointer,
) callconv(.c) void {
    const uri = gtk.webkit_uri_scheme_request_get_uri(request);
    const uri_base = "app://index.html";

    // Calcular el path relativo dentro del esquema
    const offset: usize = if (gtk.g_str_equal(uri, uri_base) != 0)
        "app://".len
    else
        "app://index.html/".len;

    const path = uri + offset;

    // Construir ruta GResource: "/path"
    const resource_path = gtk.g_strdup_printf("/%s", path);
    defer gtk.g_free(resource_path);
    std.debug.print("url : {s}\n", .{resource_path});

    const data = gtk.g_resources_lookup_data(
        resource_path,
        gtk.G_RESOURCE_LOOKUP_FLAGS_NONE,
        null,
    );

    if (data == null) {
        std.debug.print("404 {s}\n", .{path});
        const err = gtk.g_error_new_literal(
            gtk.g_quark_from_static_string("app"),
            0,
            "Archivo no encontrado",
        );
        gtk.webkit_uri_scheme_request_finish_error(request, err);
        return;
    }
    defer gtk.g_bytes_unref(data);

    var size: gtk.gsize = 0;
    const contents = gtk.g_bytes_get_data(data, &size);

    // Detectar MIME type por extensión
    const mime_type: [*:0]const u8 =
        if (gtk.g_str_has_suffix(uri, ".html") != 0) "text/html" else if (gtk.g_str_has_suffix(uri, ".css") != 0) "text/css" else if (gtk.g_str_has_suffix(uri, ".js") != 0) "application/javascript" else if (gtk.g_str_has_suffix(uri, ".svg") != 0) "image/svg+xml" else if (gtk.g_str_has_suffix(uri, ".webp") != 0) "image/webp" else if (gtk.g_str_has_suffix(uri, ".png") != 0) "image/png" else if (gtk.g_str_has_suffix(uri, ".jpg") != 0) "image/jpeg" else if (gtk.g_str_has_suffix(uri, ".jpeg") != 0) "image/jpeg" else if (gtk.g_str_has_suffix(uri, ".woff") != 0) "font/woff" else if (gtk.g_str_has_suffix(uri, ".woff2") != 0) "font/woff2" else if (gtk.g_str_has_suffix(uri, ".ttf") != 0) "font/ttf" else if (gtk.g_str_has_suffix(uri, ".eot") != 0) "font/eot" else "text/html";

    const stream = gtk.g_memory_input_stream_new_from_data(contents, @intCast(size), null);
    defer gtk.g_object_unref(stream);

    gtk.webkit_uri_scheme_request_finish(request, stream, @intCast(size), mime_type);
}

// ---------------------------------------------------------------------------
// activate
// ---------------------------------------------------------------------------
fn activate(app: ?*gtk.GtkApplication, _: gtk.gpointer) callconv(.c) void {
    // Ventana
    const window = gtk.gtk_application_window_new(app);
    gtk.gtk_window_maximize(@ptrCast(window));
    gtk.gtk_window_set_title(@ptrCast(window), "");
    gtk.gtk_window_set_default_size(@ptrCast(window), 967, 600);

    // UserContentManager + handler JS "ready"
    const manager = gtk.webkit_user_content_manager_new();
    _ = gtk.webkit_user_content_manager_register_script_message_handler(manager, "ready", null);

    // WebContext + custom scheme "app://"
    const context = gtk.webkit_web_context_new();
    gtk.webkit_web_context_register_uri_scheme(
        context,
        "app",
        customSchemeHandler,
        null,
        null,
    );

    // Settings
    const settings = gtk.webkit_settings_new();
    gtk.webkit_settings_set_enable_developer_extras(settings, 1);
    gtk.webkit_settings_set_enable_write_console_messages_to_stdout(settings, 1);
    gtk.webkit_settings_set_javascript_can_access_clipboard(settings, 1);

    // WebView construido con g_object_new para pasar las tres propiedades
    const web_view: *gtk.WebKitWebView = @ptrCast(@alignCast(gtk.g_object_new(
        gtk.webkit_web_view_get_type(),
        "user-content-manager",
        manager,
        "web-context",
        context,
        "settings",
        settings,
        @as(?*anyopaque, null), // centinela NULL
    )));

    // Señales
    _ = gtk.g_signal_connect_data(
        web_view,
        "notify::title",
        @ptrCast(&onTitleChanged),
        window,
        null,
        0,
    );

    _ = gtk.g_signal_connect_data(
        manager,
        "script-message-received::ready",
        @ptrCast(&onReady),
        web_view,
        null,
        0,
    );

    _ = gtk.g_signal_connect_data(
        web_view,
        "ready-to-show",
        @ptrCast(&onReadyShow),
        null,
        null,
        0,
    );

    // Inspector (descomentá la segunda línea para abrirlo al inicio)
    _ = gtk.webkit_web_view_get_inspector(web_view);
    // gtk.webkit_web_inspector_show(inspector);

    // Ocultar webview hasta que JS dispare "ready"
    gtk.gtk_widget_set_visible(@ptrCast(web_view), 0);
    gtk.gtk_window_set_child(@ptrCast(window), @ptrCast(web_view));

    gtk.webkit_web_view_load_uri(web_view, "app://index.html");
    gtk.gtk_window_present(@ptrCast(window));
}

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------
pub fn main() u8 {
    const app = gtk.gtk_application_new(
        "ide.pp.cillesca",
        gtk.G_APPLICATION_DEFAULT_FLAGS,
    );
    defer gtk.g_object_unref(app);

    _ = gtk.g_signal_connect_data(
        app,
        "activate",
        @ptrCast(&activate),
        null,
        null,
        0,
    );

    return @intCast(gtk.g_application_run(@ptrCast(app), 0, null));
}
