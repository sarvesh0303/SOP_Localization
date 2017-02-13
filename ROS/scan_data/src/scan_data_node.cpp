#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "../include/storage.h"
#include <cstdio>

using namespace std;

vector<pair<double,double> > PointStore::_points;

void PointStore::print_points(int count) {
  for (int i = 0; i < count; i++)
    printf("Point %d: %lf, %lf\n",i,PointStore::_points[i].first,PointStore::_points[i].second);
}

void detection_callback(const sensor_msgs::LaserScan::ConstPtr& msg) {
  const vector<float> input = msg->ranges;
  PointStore::_points.clear();
  for (int i = 0, j = msg->angle_min; i < input.size(); i++, j+= msg->angle_increment) {
    if (input[i] > msg->range_max)
      ;
    else
      PointStore::_points.push_back(std::make_pair(input[i],j));
  }
  PointStore::print_points(2);
}

int main(int argc, char** argv) {
  ros::init(argc,argv,"scan_data_node");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("/scan",1000,detection_callback);

  ros::spin();
}
