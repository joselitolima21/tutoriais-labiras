#include <Ultrasonic.h>
#include <ros.h>
#include <std_msgs/Float64.h>

#define pino_trigger 4
#define pino_echo 5

Ultrasonic ultrasonic(pino_trigger, pino_echo);

ros::NodeHandle nh;

std_msgs::Float64 distance;

ros::Publisher pub("distance", &distance);

void setup()
{
  Serial.begin(115200);
  nh.initNode();
  nh.advertise(pub);
}

void loop()
{
  float cmMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  Serial.print("Distancia em cm: ");
  Serial.println(cmMsec);
  distance.data = cmMsec;
  pub.publish( &distance );
  nh.spinOnce();
  delay(500);
}
