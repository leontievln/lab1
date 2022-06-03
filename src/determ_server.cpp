#include "ros/ros.h"
#include "lab1/quad_eq.h"
#include "std_msgs/Float32MultiArray.h"

ros::ServiceServer quad_service;
ros::Publisher quad_pub;
ros::Subscriber quad_sub;

bool calcCallback(lab1::quad_eq::Request  &req,
         lab1::quad_eq::Response &res)
{
  std_msgs::Float32MultiArray msg;
  double disc = req.b * req.b - 4 * req.a * req.c;
  if (disc > 0) 
  {
    
    float x1 = ((-req.b) + sqrt(disc)) / (2 * req.a);
    
    double x2 = ((-req.b) - sqrt(disc)) / (2 * req.a);
    
    ROS_INFO("res = %f, %f", x1, x2);
    msg.data.push_back(x1);
    msg.data.push_back(x2);
    res.data = msg.data;
  }
  if (disc == 0)
  {
    float x1 = -(req.b / (2 * req.a));
    msg.data.push_back(x1);
    ROS_INFO("res = %f", x1);
    res.data = msg.data;

  }
  if (disc < 0) {
    ROS_INFO("no solutions");
  }
  
  quad_pub.publish(msg);
  return true;
}

void quadCallback(const std_msgs::Float32MultiArray::ConstPtr& msg){
  switch (msg.get()->data.size())
  {
  case 2:
    ROS_INFO("x1= %f, x2= %f",msg.get()->data[0],msg.get()->data[0]);
    break;
  case 1:
    ROS_INFO("x1= %f",msg.get()->data[0]);
    break;
  case 0:
    ROS_INFO("no solutions");
    break;  
  default:

    break;
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "quadratic_equation_server");
  ros::NodeHandle n;

  quad_service = n.advertiseService("quadratic_equation", calcCallback);
  quad_pub = n.advertise<std_msgs::Float32MultiArray>("quadratic_equation", 1000);
  quad_sub = n.subscribe("quadratic_equation", 1000, quadCallback);

  ROS_INFO("Ready to calc quadratic_equation.");
  ros::spin();

  return 0;
}