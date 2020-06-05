#!/usr/bin/env python
import rospy
from std_msgs.msg import String,Float64

def callback(data):
    print("Valor",data.data)
    if(data.data<8):
        pub = rospy.Publisher('piscar_led', String, queue_size=10)
        pub.publish('liga')

def listener():
    rospy.init_node('controller', anonymous=True)
    rospy.Subscriber('distance', Float64, callback)
    rospy.spin()

def talker():
    pub = rospy.Publisher('chatter', String, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(1)
    while not rospy.is_shutdown():
        hello_str = "Enviei %s" % rospy.get_time()
        rospy.loginfo(hello_str)
        pub.publish(hello_str)
        rospy.Subscriber("chatter", String, callback)
        rate.sleep()


if __name__ == '__main__':
    try:
        listener()
    except rospy.ROSInterruptException:
        pass



