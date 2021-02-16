
console.log("helloWorldUtil");
	
			
var websocket = null;
if('WebSocket' in window){
	websocket = new WebSocket("ws://127.0.0.1:8888/websocket/1");
}else{
	alert("您的浏览器不支持websocket");
}
websocket.onerror = function(){
	setMessageInHtml("send error！");
}
websocket.onopen = function(){
	setMessageInHtml("{\"to\":"+"1"+",\"type\":\"" + "null"+ "\",\"value\":\"" + "连接成功"+ "\"}")
}
websocket.onmessage  = function(event){
	setMessageInHtml(event.data);
}
websocket.onclose = function(){
	setMessageInHtml("{\"to\":"+"1"+",\"type\":\"" + "null"+ "\",\"value\":\"" + "关闭连接"+ "\"}")
}
window.onbeforeunload = function(){
	clos();
}

//接收到的内容并发送信息;
var readMessageList = [
	// {
	// 	type:"range",
	// 	fun:function(data)
	// }
];
//添加返回方法数据
function addReadMessageLine(type , fun){
	let readMessageTemplate = {
		type:type,
		fun:fun
	};
	readMessageList.push(readMessageTemplate);
}
function setMessageInHtml(message){
	// console.log("[接收服务器发送过来的数据]"+message);
	let parseDate = JSON.parse(message);
	// document.getElementById('message').innerHTML += message;
	
	//返回相应的数据里面
	for (let readMessage of readMessageList) {
		if(readMessage.type == parseDate.type){
			readMessage.fun(parseDate.value);
		}
	}
}
function clos(){
	websocket.close(3000,"强制关闭");
}
function send(to , type , value){
	// var msg = "{\"to\":"+"2"+",\"type\":\"" + "range"+ "\",\"value\":\"" + "1111111"+ "\"}";
	var msg = {
		to:to,   //到那个硬件
		type:type,  //发送到那个硬件的类型
		value:value   //发送到那个硬件的值
	};
	websocket.send(JSON.stringify(msg));
}



export default function(Vue) {
    //添加全局API
    // Vue.prototype.$yuns = {
    //     format
    // }
	Vue.prototype.sendSocket = send;   //发送消息
	Vue.prototype.addReadMessageLine = addReadMessageLine;
	
}
