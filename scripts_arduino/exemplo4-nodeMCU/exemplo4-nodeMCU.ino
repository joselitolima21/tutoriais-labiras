#include <ESP8266WiFi.h>
#include <Ultrasonic.h>
#include <ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>


const char* ssid     = "Thebook";
const char* password = "Catapimbas06A@";
IPAddress server(192,168,0,107);
const uint16_t serverPort = 11411;

#define pino_led 14
#define pino_trigger 4
#define pino_echo 5

Ultrasonic ultrasonic(pino_trigger, pino_echo);

ros::NodeHandle nh;

std_msgs::Float64 distance;

ros::Publisher pub("distance", &distance);

void pisca_pisca(const std_msgs::String& piscar){
  if(piscar.data == "liga"){
    digitalWrite(pino_led, HIGH);  
    Serial.println(piscar.data);
  } else {
    digitalWrite(pino_led, LOW);
  }
}

ros::Subscriber<std_msgs::String> sub("piscar_led", &pisca_pisca );

void setup()
{  
  pinMode(pino_led,OUTPUT);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());

  nh.getHardware()->setConnection(server, serverPort);
  nh.initNode();
  nh.advertise(pub);
  nh.subscribe(sub);
}

void loop()
{
  float cmMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  Serial.print("Distancia em cm: ");
  Serial.println(cmMsec);
  
  if (nh.connected()) {
    distance.data = cmMsec;
    pub.publish( &distance );
  } else {
    Serial.println("Not Connected");
  }
  nh.spinOnce();
  delay(500);
}
