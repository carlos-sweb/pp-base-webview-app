#!/bin/bash
echo $(yq -P -o=json eval pre-render/gresource.yaml) > pre-render/gresource.json
bun run pre-render/render.ts
esbuild www/dist/index.js --bundle --outfile=www/js/bundle.js --platform=browser --format=iife
# --minify
cmake -S . -B build -G Ninja && ninja -C build  && ./build/base
