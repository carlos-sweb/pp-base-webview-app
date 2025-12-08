import esbuild from 'esbuild'

let min = await esbuild.build({
  entryPoints: ['./dist/index.js'],
  bundle: true,
  minify: true,
  format: 'iife',
  outfile: './js/bundle.js',  
  target: 'es2020',    
  drop: ['debugger','console'],
})