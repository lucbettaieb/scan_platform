/*
 *  stepper_scan.cpp
 *
 *  Copyright (c) 2015, Luc Bettaieb
 *  BSD Licensed
 *
 */

#include <ros/ros.h>
#include <ros_stepper_scan/kinect2_interface.h>
#include <ros/angles.h>

ros::Publisher 

bool scan(ros_stepper_scan::stepper_scan::Request &request,
          ros_stepper_scan::stepper_Scan::Response &response)
{

}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "stepper_scan");
  ros::NodeHandle nh;

  Kinect2Interface kinect;

  bool done = false;
  
  ros::ServiceServer stepper_scan = nh.advertiseService("start_stepper_scan", scan);

  ros::spin();
}
