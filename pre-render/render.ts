//  glib-compile-resources --target=src/example.c --generate-source --sourcedir=./ xml/www-gresource1.xml 
//yq -o=json eval gresource.yaml > gresource.json
 //echo $(yq -P -o=json eval gresource.yaml) > gresource.json
import { Glob } from "bun";
import  dirs from "./gresource.json" with { type : "json"} 
var xml2js = require('xml2js');
var myXml = {gresources:{}}

myXml["gresources"].gresource=[]
for(var i = 0; i < dirs.length ; i++){
  const dir = dirs[i]
  const glob = new Glob(dir.path)  
   myXml["gresources"].gresource[i] = {$:{prefix:dir.prefix},file:[]}
  for await (const file of glob.scan(".")){
    myXml["gresources"].gresource[i].file.push({
      $:{
        compressed:"true",
        alias:file.split("/").pop()
      },_:file
    })    
  }  
}
var builder = new xml2js.Builder();

await Bun.write('xml/gresource.xml',builder.buildObject(myXml))




