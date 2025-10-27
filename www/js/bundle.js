(() => {
  // www/dist/index.js
  var root = document.getElementById("root");
  var router = new ppRouter(
    // How to use it ?
    {
      "/": {
        controller: function() {
          root.innerHTML = `<h1>Home</h1>`;
        }
      },
      "/route-remove": {
        controller: function() {
          root.innerHTML = `<h1>Route Remove</h1>`;
        }
      }
    }
  );
  router.addRoute(
    "/vegetables/:name(string)/:id(number)",
    {
      controller: function(params) {
        root.innerHTML = `<h1>vegetables ${params.name} : ${params.id} </h1>`;
      }
    }
  );
  router.removeRoute("/route-remove");
  router.redirect("/");
  router.noFound = function(location) {
  };
  router.start();
})();
