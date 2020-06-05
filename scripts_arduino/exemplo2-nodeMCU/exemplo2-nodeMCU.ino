#include <ESP8266WiFi.h>
#include <ros.h>
#include <std_msgs/Empty.h>

const char* ssid     = "Thebook";
const char* password = "Catapimbas06A@";
IPAddress server(192,168,0,107);
const uint16_t serverPort = 11411;

ros::NodeHandle nh;

void pisca_pisca( const std_msgs::Empty& piscar ){
  digitalWrite(5, HIGH-digitalRead(5));
}

ros::Subscriber<std_msgs::Empty> sub("piscar_led", &pisca_pisca );

void setup()
{
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
  
  pinMode(5, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  if (nh.connected()) {
  } else {
    Serial.println("Not Connected");
  }
  nh.spinOnce();
  delay(500);
}
