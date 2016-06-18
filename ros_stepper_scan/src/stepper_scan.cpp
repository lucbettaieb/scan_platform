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

ros::Publisher scan_increment_pub;
Kinect2Interface kinect;

double g_increment_radians, g_increment_radians;

uint n_snaps;

bool scan(ros_stepper_scan::stepper_scan::Request &request,
          ros_stepper_scan::stepper_Scan::Response &response)
{
  for (double ang = 0; ang < 2*M_PI; ang += g_increment_radians)
  {
    for (size_t i = 0; i < n_snaps; i++)
      kinect.snapshot(request.model_name, n_snaps, ang);
  }
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "stepper_scan");
  ros::NodeHandle nh;
  
  if (!nh.getParam("ros_stepper_scan/increment_degrees", g_increment_degrees))
    g_increment_degrees = 10.0;  // Default value

  g_increment_radians = angles::from_degrees(g_increment_radians)

  n_snaps = 0;

  ros::ServiceServer stepper_scan = nh.advertiseService("start_stepper_scan", scan);
  scan_increment_pub = nh.advertise<std_msgs::Float64>("scan_increment", 10);

  ros::spin();
}
