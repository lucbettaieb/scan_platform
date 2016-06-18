/*
 * kinect2_interface
 *
 * Copyright (c) 2015, Luc Bettaieb
 * BSD Licensed
 */

#include "ros_stepper_scan/kinect2_interface.h"

ros::Subscriber g_getPointCloud;

std::string g_prev_obj_name;
std::string g_scan_topic;

std::string home = "~/.ros";

Kinect2Interface::Kinect2Interface(ros::NodeHandle &nh):p_pclKinect(new pcl::PointCloud<pcl::PointXYZRGB>)
{
  nh_ = nh;
  // g_snapshot_number = 0;
  // get topic for kinect2 PointCloud2
  // get PCD directory from config

  if (!nh.getParam("ros_stepper_scan/scan_topic", g_scan_topic))
    g_scan_topic = "/kinect2/qhd/points";  // Default behavior

  g_getPointCloud = nh.subscribe<sensor_msgs::PointCloud2> (g_scan_topic, 1, &Kinect2Interface::kinectCB, this);
}

Kinect2Interface::~Kinect2Interface()
{
  // Do I need to delete things here?
}

void Kinect2Interface::kinectCB(const sensor_msgs::PointCloud2ConstPtr &cloud)
{
  pcl::fromROSMsg(*cloud, *p_pclKinect);
  // ROS_INFO("kinectCB %d * %d points", (int) g_pclKinect->width, (int) g_pclKinect->height);
}

void Kinect2Interface::snapshot(std::string obj_name, uint snapshot_num, double snapshot_angle)
{
  ros::spinOnce();
  std::string file_name;

  file_name = obj_name + boost::to_string(snapshot_angle) + "-" + boost::to_string(snapshot_num);

  pcl::io::savePCDFileASCII(file_name + ".pcd", *p_pclKinect);
}
