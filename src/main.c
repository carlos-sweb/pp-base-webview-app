#include <gtk/gtk.h>
#include <webkit/webkit.h>




static void close_app( WebKitUserContentManager* self, 
                     JSCValue* value, gpointer user_data){
    

      g_print("Closeseses\n");

}

 
static void on_title_changed(WebKitWebView *web_view, GParamSpec *pspec, gpointer user_data) {
    GtkWindow *window = GTK_WINDOW(user_data);
    const gchar *title = webkit_web_view_get_title(web_view);
    if(title){
        gtk_window_set_title(window, title);        
    }
}

static void on_load_changed(WebKitWebView *web_view, WebKitLoadEvent load_event, gpointer user_data) {
    if (load_event == WEBKIT_LOAD_FINISHED) {
        const gchar *title = webkit_web_view_get_title(web_view);
        if (title) {
            g_print("Load finished. Current page title: %s\n", title);
        } else {
            g_print("Load finished. No title available.\n");
        }
    }

}
static void on_ready( WebKitUserContentManager* self, 
                     JSCValue* value, gpointer user_data){
    
    WebKitWebView *webview = WEBKIT_WEB_VIEW(user_data);
    if( !gtk_widget_get_visible(GTK_WIDGET(webview)) ){
      g_print("Works\n");
      gtk_widget_set_visible(GTK_WIDGET(webview), TRUE);    
    }
        
    g_signal_handlers_disconnect_by_func(self,G_CALLBACK(on_ready),user_data);

}

static void on_ready_show( WebKitWebView * self){
      g_print("on_ready_show\n");
}

static void custom_scheme_handler(WebKitURISchemeRequest *request, gpointer user_data) {
    gsize size;
    GInputStream *stream;
    const gchar *mime_type;
    const gchar *uri = webkit_uri_scheme_request_get_uri(request);
    const gchar *uri_base = "app://index.html";
    const gchar *path = g_str_equal(uri, uri_base)
        ? uri + strlen("app://")
        : uri + strlen("app://index.html/");

    gchar *resource_path = g_strdup_printf("/%s", path);
    g_print("url : %s\n", resource_path);

    GBytes *data = g_resources_lookup_data(resource_path, G_RESOURCE_LOOKUP_FLAGS_NONE, NULL);
    g_free(resource_path);

    if (!data) {
        g_print("404 %s\n", path);
        webkit_uri_scheme_request_finish_error(
            request,
            g_error_new_literal(g_quark_from_static_string("app"), 0, "Archivo no encontrado")
        );
        return;
    }

    size = g_bytes_get_size(data);

    // MIME type
    mime_type = "text/html";
    if (g_str_has_suffix(uri, ".html"))  mime_type = "text/html";
    else if (g_str_has_suffix(uri, ".css"))  mime_type = "text/css";
    else if (g_str_has_suffix(uri, ".js"))   mime_type = "application/javascript";
    else if (g_str_has_suffix(uri, ".svg"))  mime_type = "image/svg+xml";
    else if (g_str_has_suffix(uri, ".webp")) mime_type = "image/webp";
    else if (g_str_has_suffix(uri, ".png"))  mime_type = "image/png";
    else if (g_str_has_suffix(uri, ".jpg"))  mime_type = "image/jpeg";
    else if (g_str_has_suffix(uri, ".jpeg")) mime_type = "image/jpeg";
    else if (g_str_has_suffix(uri, ".woff")) mime_type = "font/woff";
    else if (g_str_has_suffix(uri, ".woff2")) mime_type = "font/woff2";
    else if (g_str_has_suffix(uri, ".ttf"))  mime_type = "font/ttf";
    else if (g_str_has_suffix(uri, ".eot"))  mime_type = "font/eot";

    g_print("  -> serving %s (%zu bytes, mime: %s)\n", uri, size, mime_type);

    // g_memory_input_stream_new_from_bytes takes ownership of the GBytes.
    // WebKit takes ownership of the stream via webkit_uri_scheme_request_finish.
    // No manual unref needed for either.
    stream = g_memory_input_stream_new_from_bytes(data);
    webkit_uri_scheme_request_finish(request, stream, size, mime_type);
    g_object_unref(stream);
}

static void activate(GtkApplication *app,gpointer user_data){

  WebKitWebView                     *web_view;
  WebKitWebContext          *web_view_context; 
  WebKitUserContentManager  *web_view_manager;
  WebKitSettings           *web_view_settings;
  GtkWidget                           *window;
  window=gtk_application_window_new(app);
  gtk_window_maximize(GTK_WINDOW(window));  
  gtk_window_set_title(GTK_WINDOW(window),"");
  gtk_window_set_default_size(GTK_WINDOW(window),967,600);
  
  // create webview
  web_view_manager = webkit_user_content_manager_new();    
  
  webkit_user_content_manager_register_script_message_handler( 
    web_view_manager,
    "ready",
    NULL
    );

  web_view_context = webkit_web_context_new();
  
  webkit_web_context_register_uri_scheme(
      web_view_context,
      "app",
      custom_scheme_handler,
      NULL, NULL
  );
  
  // Crear settings para habilitar el inspector
  web_view_settings = webkit_settings_new();
  webkit_settings_set_enable_developer_extras(web_view_settings, TRUE);
  
  web_view = WEBKIT_WEB_VIEW(
      g_object_new(
          WEBKIT_TYPE_WEB_VIEW,
          "user-content-manager",web_view_manager,
          "web-context",web_view_context,
          "settings",web_view_settings,
          NULL
      )
  );

  // Connect to the notify::title signal to get title changes
  g_signal_connect(web_view, "notify::title", G_CALLBACK(on_title_changed), window );

  // Connect to the load-changed signal to get the title after a page loads
  // g_signal_connect(web_view, "load-changed", G_CALLBACK(on_load_changed), NULL);


  WebKitWebInspector *inspector = webkit_web_view_get_inspector(web_view);
  webkit_web_inspector_show(inspector);

  webkit_settings_set_enable_write_console_messages_to_stdout(web_view_settings, TRUE);
  webkit_settings_set_javascript_can_access_clipboard(web_view_settings, TRUE);
  
    g_signal_connect(
    web_view_manager,
    "script-message-received::ready",
    G_CALLBACK(on_ready),web_view);

    g_signal_connect(
    web_view_manager,
    "script-message-received::close",
    G_CALLBACK(close_app),web_view);

    g_signal_connect(web_view,"ready-to-show",G_CALLBACK(on_ready_show),web_view);

    gtk_window_set_child(GTK_WINDOW(window),GTK_WIDGET(web_view));
    gtk_widget_set_visible(GTK_WIDGET(web_view),FALSE);
    webkit_web_view_load_uri(web_view,"app://index.html");
    gtk_window_present(GTK_WINDOW(window));
}



int main (int argc,char **argv){
  GtkApplication *app;
  int status;
  app = gtk_application_new( "ide.pp.cillesca" , G_APPLICATION_DEFAULT_FLAGS );
  g_signal_connect( app , "activate" , G_CALLBACK( activate ) , NULL );
  status = g_application_run( G_APPLICATION( app ), argc , argv );
  g_object_unref( app );
  return status;
}
