#!/bin/bash
esbuild www/dist/index.js --bundle --outfile=www/js/bundle.js --platform=browser --format=iife
# --minify
cmake -S . -B build -G Ninja && ninja -C build run
