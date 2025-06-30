document.addEventListener("DOMContentLoaded",function(){
	window.webkit.messageHandlers.ready.postMessage("ready");
	document.getElementById("text").innerText= "Text from JS";
});