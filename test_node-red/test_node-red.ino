#include <WiFi.h>
#include<PubSubClient.h>
const char* ssid = "Phòng 6-7G 2.4GHz";
const char* passsword="68686868";
const char* mqtt_server="192.168.1.162";//ip laptop
const uint16_t mqtt_port=1883;
const byte ledpin=2;
WiFiClient espClient ;
PubSubClient client(espClient);
// cambienhc-sr04
const int trig =14;
const int echo =12;
int i;
#define red 4
#define xanh 2
String Str_number1;
char Char_number1[50];

// set up
void setup(){
pinMode (ledpin, OUTPUT);
pinMode (trig,OUTPUT);
pinMode (echo,INPUT);
pinMode(red,OUTPUT);
pinMode(xanh,OUTPUT);
Serial.begin(9600);
setup_wifi();
client.setServer(mqtt_server, mqtt_port);
client.setCallback(callback);
}
void setup_wifi(){
delay(10);

//ketnoi wifi
Serial.println();
Serial.print("connecting to ");
Serial.print(ssid);
WiFi.begin(ssid,passsword);
while (WiFi.status() !=WL_CONNECTED){
delay (500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
Serial.println("WiFi connected");
Serial.println(WiFi.localIP());
}
///============================ket noi wifi=======================
void callback(char* topic, byte* message, unsigned int length) {
Serial.print("Message arrived on topic: ");
Serial.print(topic);
Serial.print(". Message: ");
String messageTemp;
for (int i = 0; i < length; i++) {
Serial.print((char)message[i]);
messageTemp += (char)message[i];
}
Serial.println();
// Feel free to add more if statements to control more GPIOs with MQTT
// If a message is received on the topic esp32/output, you check if the message is
// Changes the output state according to the message
if (String(topic) == "TEST") {
  Serial.print("du me may");
  if (messageTemp == "1") {
    Serial.println("du me may");
    i=1;
    /// kiem tra i=1 i=0 la cai gi
  }
}

if ( String(topic) == "ON" ){
Serial.print("Changing output to ");
if(messageTemp == "1"){
Serial.print("ON_HC-SR04");
i =1;
}
if(messageTemp == "0"){
Serial.print("ON_HC-SR04");
i =0;
}
}
if (String(topic) == "WARNING") {
Serial.print("Changing output to ");
if(messageTemp == "R"){
Serial.print("Đỏ");
digitalWrite(red,HIGH);
digitalWrite(xanh,LOW);
}
if(messageTemp == "X"){
Serial.print("Xanh");
digitalWrite(xanh,HIGH);
digitalWrite(red,LOW);
}
}
}
float hc_sr04(){
unsigned long t ;
int R;
digitalWrite(trig,0);
delayMicroseconds (2);
digitalWrite(trig,1);
delayMicroseconds (5);
digitalWrite(trig,0);
t= pulseIn (echo, HIGH);
R = (t/2/29.412);
return R;
}
void reconect (){
while (!client.connected()){
Serial.print("Attemting MQTT connecting ...");
if (client.connect ("ESP")){
Serial.println("connected");
client.publish("event","hello world");
client.subscribe("even");
client.subscribe("WARNING");

client.subscribe("ON");
}
else{
Serial.print("fail, rc=");
Serial.print(client.state());
Serial.println("try again in 5 seconds");
delay(5000);
}
}
}
void loop(){
if (!client.connected()){
reconect ();
}
client.loop();
if(i==1){
float R=hc_sr04();
Str_number1 = String(R);
Str_number1.toCharArray(Char_number1,Str_number1.length()+1);
client.publish("HC_SR04", Char_number1); //
}
}
