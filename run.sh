#!/bin/bash
echo $(yq -P -o=json eval pre-render/gresource.yaml) > pre-render/gresource.json
bun run pre-render/render.ts
cd www
bun run esbuild.js
cd ..
cmake -S . -B build -G Ninja && ninja -C build  && ./build/base
