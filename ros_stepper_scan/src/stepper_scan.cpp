/*
 *  stepper_scan.cpp
 *
 *  Copyright (c) 2016, Luc Bettaieb
 *  BSD Licensed
 */

#include <ros/ros.h>
#include <ros_stepper_scan/kinect2_interface.h>
#include <angles/angles.h>
#include <boost/shared_ptr.hpp>
#include <std_msgs/Float64.h>

#include "ros_stepper_scan/stepper_scan.h"

ros::Publisher scan_increment_pub;
boost::shared_ptr<Kinect2Interface> kinect;

double g_increment_degrees, g_increment_radians;
int g_n_snaps;

bool scan(ros_stepper_scan::stepper_scan::Request &request,
          ros_stepper_scan::stepper_scan::Response &response)
{
  for (double ang = 0; ang < 2*M_PI; ang += g_increment_radians)
  {
    scan_increment_pub.publish(g_increment_degrees);
    for (size_t i = 0; i < g_n_snaps; i++)
      kinect->snapshot(request.model_name, i, ang);
  }
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "stepper_scan");
  ros::NodeHandle nh;

  kinect.reset(new Kinect2Interface(nh));

  if (!nh.getParam("ros_stepper_scan/increment_degrees", g_increment_degrees))
    g_increment_degrees = 10.0;  // Default value
  if (!nh.getParam("ros_stepper_scan/snaps_per_increment", g_n_snaps))
    g_n_snaps = 1;  // Default value


  g_increment_radians = angles::from_degrees(g_increment_radians);


  ros::ServiceServer stepper_scan = nh.advertiseService("start_stepper_scan", scan);
  scan_increment_pub = nh.advertise<std_msgs::Float64>("scan_increment", 10);


  ros::spin();
}
