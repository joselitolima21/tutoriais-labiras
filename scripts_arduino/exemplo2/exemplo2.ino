#include <ros.h>
#include <std_msgs/Empty.h>

ros::NodeHandle nh;

const std_msgs::Empty& piscar_led

void pisca_pisca( const std_msgs::Empty& piscar ){
  digitalWrite(5, HIGH-digitalRead(5));
}

ros::Subscriber<std_msgs::Empty> sub("piscar_led", &pisca_pisca );

void setup()
{
  pinMode(5, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  delay(1);
}
