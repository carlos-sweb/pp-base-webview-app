document.addEventListener('contextmenu', (e) => e.preventDefault() );

import ppRouter from 'pp-router.js'
const routeInfo = document.getElementById('route-info');
    const router = new ppRouter({
            '/': {
                controller: (params) => {
                    routeInfo.textContent = `Route: Home\nParams: ${JSON.stringify(params, null, 2)}`;
                }
            },
            '/about': {
                controller: (params) => {
                    routeInfo.textContent = `Route: About Us\nParams: ${JSON.stringify(params, null, 2)}`;
                }
            },
            '/users/:id(number)': {
                controller: (params) => {
                    routeInfo.textContent = `Route: User Profile\nID: ${params.id}\nParams: ${JSON.stringify(params, null, 2)}`;
                }
            },
            '/products/:name(string)': {
                controller: (params) => {
                    routeInfo.textContent = `Route: Product Detail\nName: ${params.name}\nParams: ${JSON.stringify(params, null, 2)}`;
                }
            },
            '/files/:dir(any)/:path(any)': {
                controller: (params) => {
                    routeInfo.textContent = `Route: File Viewer\nDir: ${params.dir}\nPath: ${params.path}\nParams: ${JSON.stringify(params, null, 2)}`;
                }
            }
        });

        router.setNoFound((location) => {
            routeInfo.textContent = `Route: 404 Not Found\nLocation: ${location.hash}`;
        });

    // Optional: Redirect to home if a non-existent route is hit
    // router.setRedirect('/')

    router.start()