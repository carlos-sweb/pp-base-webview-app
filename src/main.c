#include <gtk/gtk.h>
#include <webkit/webkit.h>

static void on_ready(WebKitUserContentManager* self, JSCValue* value, gpointer user_data){
    WebKitWebView *webview = WEBKIT_WEB_VIEW(user_data);    
    if( !gtk_widget_get_visible(GTK_WIDGET(webview)) ){
      gtk_widget_set_visible(GTK_WIDGET(webview), TRUE);    
    }
    
}

static void custom_scheme_handler(WebKitURISchemeRequest *request, gpointer user_data) {
    gsize size;
    GInputStream *stream;
    const gchar *mime_type;
    const void *contents;
    const gchar *uri = webkit_uri_scheme_request_get_uri(request);  // ej: "app://index.html"
    const gchar * uri_base = "app://index.html";
    const gchar *path = g_str_equal(uri,uri_base) ?  uri + strlen("app://") : uri + strlen("app://index.html/");
              
    // Ruta en GResource
    gchar *resource_path = g_strdup_printf("/%s", path);
    
    GBytes *data = g_resources_lookup_data(resource_path, G_RESOURCE_LOOKUP_FLAGS_NONE, NULL);

    g_free(resource_path);

    if (!data) {
        // Si no lo encuentra, devuelve error 404
        webkit_uri_scheme_request_finish_error(
            request,
            g_error_new_literal(g_quark_from_static_string("app"), 0, "Archivo no encontrado")
        );
        return;
    }

    
    contents = g_bytes_get_data(data, &size);

    // MIME TYPE básico (mejor si lo detectas bien)
    mime_type = "text/html";
    if (g_str_has_suffix(uri, ".html")) mime_type = "text/html";
    else if (g_str_has_suffix(uri, ".css")) mime_type = "text/css";
    else if (g_str_has_suffix(uri, ".js")) mime_type = "application/javascript";
    else if (g_str_has_suffix(uri, ".svg")) mime_type = "image/svg+xml";
    else if (g_str_has_suffix(uri, ".webp")) mime_type = "image/webp";
    else if (g_str_has_suffix(uri, ".png")) mime_type = "image/png";
    else if (g_str_has_suffix(uri, ".jpg")) mime_type = "image/jpeg";
    else if (g_str_has_suffix(uri, ".jpeg")) mime_type = "image/jpeg";
    else if (g_str_has_suffix(uri, ".woff")) mime_type = "font/woff";
    else if (g_str_has_suffix(uri, ".woff2")) mime_type = "font/woff2";

    stream = g_memory_input_stream_new_from_data(contents, size, NULL);
    webkit_uri_scheme_request_finish(request, stream, size, mime_type);

    g_object_unref(stream);
    g_bytes_unref(data);
}



// declaración previa
gboolean on_context_menu(WebKitWebView* self,WebKitContextMenu* context_menu,WebKitHitTestResult* hit_test_result,gpointer user_data);
// Implementación

gboolean on_context_menu(WebKitWebView* self,WebKitContextMenu* context_menu,WebKitHitTestResult* hit_test_result,gpointer user_data){
  return TRUE;
}

static void print_hello (GtkWidget *widget, gpointer   data){
  g_print ("Hello World\n");
}

static void activate (GtkApplication *app,gpointer user_data){
  WebKitWebView                    *web_view;
  WebKitWebContext        * web_view_context; 
  WebKitUserContentManager *web_view_manager;

  GtkWidget                          *window;

  window=gtk_application_window_new(app);
  gtk_window_maximize(GTK_WINDOW(window));  
  gtk_window_set_title(GTK_WINDOW(window),"");
  //removemos el title bar de gtk
  //gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
  //gtk_window_set_titlebar(GTK_WINDOW(window), NULL);
  //removemos el title bar de gtk
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
      "app", // este es el "esquema"
      custom_scheme_handler, // tu función para manejarlo
      NULL, NULL
  );
  
  web_view = WEBKIT_WEB_VIEW(
      g_object_new(
          WEBKIT_TYPE_WEB_VIEW,
          "user-content-manager",web_view_manager,
          "web-context",web_view_context,
          NULL
      )
  );
  g_signal_connect(
    web_view_manager,
    "script-message-received::ready",
    G_CALLBACK(on_ready),
    web_view
  );


  gtk_window_set_child(GTK_WINDOW(window),GTK_WIDGET(web_view));
  gtk_widget_set_visible(GTK_WIDGET(web_view),FALSE);
  webkit_web_view_load_uri(web_view,"app://index.html");
  gtk_window_present(GTK_WINDOW(window));
}

int main (int argc,char **argv){
  GtkApplication *app;
  int status;
  app=gtk_application_new("ide.pp.cillesca",G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app,"activate",G_CALLBACK(activate),NULL);
  status=g_application_run(G_APPLICATION(app),argc,argv);
  g_object_unref(app);
  return status;
}
