//glib-compile-resources --target=src/example.c --generate-source --sourcedir=./ xml/www-gresource1.xml 
//yq -o=json eval gresource.yaml > gresource.json
//echo $(yq -P -o=json eval gresource.yaml) > gresource.json
import { Glob , $ } from "bun";
await $`echo $(yq -P -o=json eval pre-render/gresource.yaml) > pre-render/gresource.json`
await $`echo $(yq -P -o=json eval pre-render/font.yaml) > pre-render/font.json`
import  dirs from "./gresource.json" with { type : "json"} 
import  font from "./font.json" with { type : "json"} 


//import { PugCompiler } from 'zig-pug';
const zigpug = require('zig-pug')
const compiler = new zigpug.PugCompiler()

compiler.set('title', 'ppApp')
compiler.set('links',[
  '/css-utility/dist/normalize.min.css',
  '/css/animate/animate-base.css',
  '/css/animate/fade/fadeIn.css',
  '/css-utility/dist/master.css',
  '/font/index.css',
  '/css/font.css',
  '/css/style.css'
])
const html = compiler.compile(  await Bun.file('www/index.zpug').text()  );
await Bun.write('www/index.html',html)



const path = `./node_modules/${font.dir}`
if( !await Bun.file(path).exists() ){
  await $`if [ ! -d "./node_modules/$ADD_FONT" ]; then 
   bun add $ADD_FONT
  fi
`.env({ADD_FONT: font.dir})
}
dirs.push({ prefix: "/font",path: `node_modules/${font.dir}/*.css` }) 
dirs.push({prefix: "/font/files",path: `node_modules/${font.dir}/files/*.{woff,woff2}` }) 

await Bun.write("www/css/font.css", `body{font-family:${font.fontFamily}}`);

// ==============================================
var xml2js = require('xml2js')
var myXml = {gresources:{}}
myXml["gresources"].gresource=[]
for(var i = 0; i < dirs.length ; i++){
  const dir = dirs[i]
  const paths = Array.isArray(dir.path) ? dir.path : [dir.path]  
  for(const path of paths){
    const glob = new Glob(path)  
    if( myXml["gresources"].gresource[i] == undefined ) myXml["gresources"].gresource[i] = {$:{prefix:dir.prefix},file:[]}
    for await (const file of glob.scan(".")){
      const fileName = file.split("/").pop()      
      myXml["gresources"].gresource[i].file.push({
        $:{
          compressed:"true",
          alias:fileName
        },_:file
      })    
    }      
  }
}
var builder = new xml2js.Builder()
await Bun.write('xml/gresource.xml',builder.buildObject(myXml))

await Bun.build({
  entryPoints: ['www/js/index.js'],
  bundle: true,  
  minify: {
    whitespace: true,
    identifiers: true,
    syntax: true,
  },
  format: 'iife',
  outdir: 'www/dist',
  drop: ['debugger','console'],
})

await $`cmake -S . -B build -G Ninja && ninja -C build  && ./build/base`