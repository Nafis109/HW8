// This program publishes randomly-generated velocity
// messages for turtlesim.
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>  // For geometry_msgs::Twist
#include <stdlib.h> // For rand() and RAND_MAX

double pi = 3.1415926535897;
int i = 0;
int main(int argc, char **argv) {
  // Initialize the ROS system and become a node.
  ros::init(argc, argv, "publish_velocity");
  ros::NodeHandle nh;

  // Create a publisher object.
  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>(
    "turtle1/cmd_vel", 1000); //links publisher to the node

  // Seed the random number generator.
  srand(time(0));

  // Loop at 2Hz until the node is shut down.
  ros::Rate rate(2);
  while(ros::ok()) {
    // Create and fill in the message.  The other four
    // fields, which are ignored by turtlesim, default to 0.

    geometry_msgs::Twist msg; //Object msgs
    if (i <10) {
      msg.angular.z = -pi/8;
    }
    if ((i >= 10) && (i<20)) {
      msg.linear.x = 1;
    }
    if ((i >= 20) && (i<30)) {
      msg.angular.z = pi/8;
    }
    if ((i >= 30) && (i<35)) {
      msg.linear.x = 1;
    }
    if (i>35) {
      msg.linear.x = 0;
    }
    // Publish the message.
    i+=1;
    pub.publish(msg);

    // Send a message to rosout with the details.
    ROS_INFO_STREAM("Sending random velocity command:"
      << " linear=" << msg.linear.x
      << " angular=" << msg.angular.z);

    // Wait until it's time for another iteration.
    rate.sleep();
  }
}
