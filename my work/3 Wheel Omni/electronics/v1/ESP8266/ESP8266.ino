#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"
#include "file.h"
 
ESP8266WebServer server(80);

String coord_matrix[32]={"WK10","King","Queen","Bishop","Knight","Rook","pawn"};//holds board coodinates for each piece.// chess board

IPAddress serverIP(0,0,0,0);

void setup() {
  Serial.begin(115200);
  WiFi.begin("black", "pyrad007");  //Connect to the WiFi network
  while (WiFi.status() != WL_CONNECTED) {  //Wait for connection
    delay(500);
    Serial.println(".");
  }
  serverIP=WiFi.localIP();
  serverIP[3]=50;//set as the IP;
  IPAddress gateway=serverIP;
  gateway[3]=1;
  WiFi.config(serverIP, gateway, IPAddress(255,255,255,0), IPAddress(8,8,8,8), IPAddress(8,8,4,4));
  Serial.println(WiFi.localIP());  
 
  server.on("/", handleRootPath);    //Associate the handler function to the path
  server.on("/get",handleGetReq);
  server.on("/forPiece",handlePiece);
  server.begin();                    //Start the server
  pinMode(LED_BUILTIN,OUTPUT);
}

void loop() {
   server.handleClient();         //Handling of incoming requests
}
 
void handleRootPath() {            //Handler for the rooth path
  server.send(200, "text/html", index_html);
}

void handleGetReq() { //Handler
  Serial.println("recieved request");
  String message = "WK1";
  for (int i = 0; i < server.args(); i++) {
      message += server.arg(i);              //Get the value of the parameter
      coord_matrix[0]=message; //set the value of the paramter as the new coordinate...use key value here BK1-a6
}  
server.send(200, "text/html", index_html);       //Response to the HTTP request
}

void handlePiece(){
  for(int i=0;i<1;i++){
  String values="";
  values+=coord_matrix[i]+"\n";
  server.send(200,"text/plain",values);
  }
}
