//glib-compile-resources --target=src/example.c --generate-source --sourcedir=./ xml/www-gresource1.xml 
//yq -o=json eval gresource.yaml > gresource.json
//echo $(yq -P -o=json eval gresource.yaml) > gresource.json
import { Glob , $ } from "bun";
await $`echo $(yq -P -o=json eval pre-render/gresource.yaml) > pre-render/gresource.json`
import  dirs from "./gresource.json" with { type : "json"}

await Bun.write('www/index.html',  await Bun.file('dist-playground/index.html').text() )



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


await $`cmake -S . -B build -G Ninja && ninja -C build  && ./build/base`