import {isArray} from "pp-is"
import events from "pp-events"

const myEvent = events({
	"myCustom":function(msg){
		console.log("mensaje ....",isArray(msg));
	}
});


myEvent.emit("myCustom","aaaa");
