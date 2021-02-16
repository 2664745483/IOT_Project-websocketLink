/*
	Esp8266 Websockets Client

*/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h>
#include <Hash.h>
#include <Arduino_JSON.h>
#include "DHT.h"  
#include<Servo.h>


const char* ssid = "TP-LINK_27BE"; //Enter SSID
const char* password = "sucaiqin.."; //Enter Password

const char* websockets_server_host = "192.168.0.108"; //输入服务器地址
const uint16_t websockets_server_port = 8888; //输入服务器端口
const char* websockets_server_path = "/websocket/2"; //输入服务器端口

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;

#define espSerial Serial
String bufClient;
int delayTime = 0;

//用户自定义区 用户灯亮
#define LED_liangDu   4
//开关
#define LED_Bool      5
//温湿度1
#define DHTPIN_1      10 
//温湿度2
#define DHTPIN_2      0 
//定义类型，DHT11或者其它
#define DHTTYPE DHT11
//进行初始设置 
DHT dht1(DHTPIN_1, DHTTYPE);
DHT dht2(DHTPIN_2, DHTTYPE);
//光控输入开关
#define BUTTON_1      16 
//输出继电器开关
#define CONTROLLER_1  2
int buttonState = 0;
int previousButtonState = 0;

//声波探测器
#define EchoPin     13           // D1引脚连接Echo
#define TrigPin     12          //  D2引脚连接Tric
int delayTimeShengBo =  0;              //每两次之间的测量时间间隔
unsigned long Time_Echo_us = 0;         //发出和反射总时间
unsigned long Len_mm  = 0;                //探测距离，单位mm
//声波范围探测器
#define DUOJI  14
int DUOJI_jiaoDu = 30;
int DUOJI_zhengFan = 1;
Servo myservo;


//json解析
JSONVar getJSONValue(uint8_t * input){
  
  JSONVar myObject = JSON.parse((char *)input);
  int inits = 0;
  // JSON.typeof(jsonVar) can be used to get the type of the var
  if (JSON.typeof(myObject) == "undefined") {
    espSerial.println("Parsing input failed!");
    return myObject;
  }
//  if (myObject.hasOwnProperty("value")) {
//    espSerial.print("myObject[\"value\"] = ");espSerial.println((int) myObject["value"]);
//  }
   return    myObject; //(int) myObject["value"];
}
//--------------------function websocket event
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  
  switch(type) {
    case WStype_DISCONNECTED:
      espSerial.printf("[WSc] Disconnected!\n");
      break;
    case WStype_CONNECTED: {
      espSerial.printf("[WSc] Connected to url: %s\n", payload);
      // send login json to server when Connected
//      webSocket.sendTXT(login);
    }
    break;
    case WStype_TEXT:
//      espSerial.printf("[WSc] get text: %s\n", payload);
        
//        espSerial.println(getJSONValue(  payload  ));
        sendTypeFunction(payload);
//       espSerial.println( getJSONValue(  payload  ) / 100.0 * 255);
       
      break;
    case WStype_BIN:
      espSerial.printf("[WSc] get binary length: %u\n", length);
      hexdump(payload, length);
      break;
  }
}
//声波探测器返回的是距离
unsigned long FunShengBo(){
    digitalWrite(TrigPin, LOW);     //发出11us的触发脉冲，大于10s即可
    digitalWrite(TrigPin, HIGH);              
    delayMicroseconds(11);                    
    digitalWrite(TrigPin, LOW);               
    
    Time_Echo_us = pulseIn(EchoPin, HIGH);               //获取传播总时间
    if((Time_Echo_us < 60000) && (Time_Echo_us > 1))     //有效传播时间之内，2-400cm，大约为1-60000us
    {
      Len_mm = (Time_Echo_us*34/100)/2;      //计算距离 Len_mm = (Time_Echo_us * 0.34mm/us) / 2 (mm)
//      Serial.print("Present Distance is: ");  //输出结果到串口监视器
//      Serial.print(Len_mm, DEC);            
//      Serial.println("mm");     
                  
    }
    else  //超出测量范围或者测量范围太小
    {
      Serial.println("Error! Too long or too short!!!");  
    }
    if(delayTimeShengBo >= 1){
      delay(delayTimeShengBo); 
    }
    return Len_mm;       
}


//用户自定初始化
void userInit(){
  //灯为高电平
  pinMode(LED_liangDu,OUTPUT);
  //灯的亮灭
  pinMode(LED_Bool,OUTPUT);
  digitalWrite(LED_Bool, HIGH);
  //dh开始工作
  dht1.begin(); //DHT开始工作
  dht2.begin(); //DHT开始工作
  
  //光控输入开关
  pinMode(BUTTON_1,INPUT);
  //继电器开关
  pinMode(CONTROLLER_1,OUTPUT);
  //声波舵机
  myservo.attach(DUOJI);            
  pinMode(EchoPin, INPUT);                    
  pinMode(TrigPin, OUTPUT);    
}

//根据发送过来的数据判断执行哪一种类型
void sendTypeFunction(uint8_t * input){
  JSONVar myObject = getJSONValue(input);
  if (JSON.typeof(myObject) == "undefined") {
    espSerial.println("Parsing input failed!");
    return;
  }
  const char * typeData = (const char * ) myObject["type"];
  
  espSerial.printf("json: %s  ,%s \n",input,typeData);
//  myObject
  //根据类型执行当前作用域-范围
  if(  strcmp(typeData, "range") == 0){
    
    espSerial.print("range    ");
    espSerial.println(strcmp(typeData, "range"));
    analogWrite(  LED_liangDu , (int) myObject["value"] / 100.0 * 255);
  }
  //获取当前开关灯的值
  if( strcmp(typeData, "bool") == 0){
    
    espSerial.println("bool   ");
    espSerial.println((bool) myObject["value"]);
    if((bool) myObject["value"] == 1){
      digitalWrite(LED_Bool, HIGH);
    }else{
      digitalWrite(LED_Bool, LOW);
    }
  }
  //获取当前是否接触的值bool//获取当前开关灯的值
  if( strcmp(typeData, "bool1") == 0){
    
    espSerial.println("bool1   ");
    espSerial.println((bool) myObject["value"]);
    if((bool) myObject["value"] == 1){
      digitalWrite(CONTROLLER_1, HIGH);
    }else{
      digitalWrite(CONTROLLER_1, LOW);
    }
  }
  //
}

void setup() {
  espSerial.begin(115200);
  espSerial.setDebugOutput(true);
  espSerial.println();
  espSerial.println();
  espSerial.println();
  for(uint8_t t = 4; t > 0; t--) {
    espSerial.printf("[SETUP] BOOT WAIT %d...\n", t);
    espSerial.flush();
    delay(1000);
  }

  WiFiMulti.addAP(ssid, password);
  //WiFi.disconnect();
  while(WiFiMulti.run() != WL_CONNECTED) {
    delay(100);
  }
  
  webSocket.begin(websockets_server_host, websockets_server_port, websockets_server_path);  //server, port, url
  webSocket.onEvent(webSocketEvent);    //catch event
  webSocket.setReconnectInterval(5000); //reconnect every 5 second

  //用户自定初始化
  userInit();
}

void loop() {
  webSocket.loop();
  if (Serial.available()) {
    bufClient = "";
    while (Serial.available()) {
      bufClient += Serial.readString();       
    }
  }
  if (bufClient != ""){
    bufClient.trim();
    webSocket.sendTXT("{\"to\":\"1\",\"type\":\"range\",\"value\":"+String(bufClient)+"}"   );
    bufClient = "";
  }
  
  //------sending random value every half second

    //间隔500ms
    if(delayTime%1000 == 0){
      webSocket.sendTXT("{\"to\":\"1\",\"type\":\"wenShiDu1\",\"value\":["+String(dht1.readTemperature())+","+String(dht1.readHumidity())+"]}");
      webSocket.sendTXT("{\"to\":\"1\",\"type\":\"wenShiDu2\",\"value\":["+String(dht2.readTemperature())+","+String(dht2.readHumidity())+"]}");
    
    
    }

    //判断当前是否按下并且不可重复发送
    buttonState = digitalRead(BUTTON_1);
    if(buttonState !=previousButtonState){
      previousButtonState = buttonState;
      espSerial.println(buttonState);
      if(buttonState != HIGH){
        webSocket.sendTXT("{\"to\":\"1\",\"type\":\"getBool\",\"value\":true}");
      }else{
        webSocket.sendTXT("{\"to\":\"1\",\"type\":\"getBool\",\"value\":false}");
      }
    }
    //声波范围探测器200毫秒谈一次
    if(delayTime%10 == 0){
      myservo.write(DUOJI_jiaoDu);
      if(DUOJI_jiaoDu >= 90){
        DUOJI_zhengFan = 0;
      }
      if(DUOJI_jiaoDu <= 1){
        DUOJI_zhengFan = 1;
      }
      if(DUOJI_zhengFan == 1){
        DUOJI_jiaoDu = DUOJI_jiaoDu+1;
      }else{
        DUOJI_jiaoDu = DUOJI_jiaoDu-1;
      }
//      判断当前是否是一个探测角度的点
      if(DUOJI_jiaoDu%10 == 0){
//        espSerial.printf("探测角度!:%d  距离:%d  \n",DUOJI_jiaoDu,FunShengBo());
        webSocket.sendTXT("{\"to\":\"1\",\"type\":\"leiDa\",\"value\":["+String(DUOJI_jiaoDu)+","+String(FunShengBo())+"]}" );
//        webSocket.sendTXT("{\"to\":\"1\",\"type\":\"leiDa\",\"value\":"+String(DUOJI_jiaoDu)+","+String(FunShengBo())+"}"   );
      }
    
    }


    
  //------sending random value every half second
  
  if(delayTime >= 10000){
    delayTime = 1;
  }else{
    delayTime = delayTime + 1;
  }
  delay(1);
}
