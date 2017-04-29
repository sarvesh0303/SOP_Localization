#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "../include/storage.h"
#include <cstdio>
#include <iostream>

using namespace std;
int flag;
vector<pair<double,double> > PointStore::_points;
char *file_name;

void PointStore::print_points(int count,char* file_name) {
	cout << "I read buffer size as: " << PointStore::_points.size() << endl;
	FILE* fp = fopen(file_name,"w");
	for (int i = 0; i < PointStore::_points.size(); i++)
    fprintf(fp,"%lf, %lf\n",PointStore::_points[i].first,PointStore::_points[i].second);	
  fclose(fp);
}

void detection_callback(const sensor_msgs::LaserScan::ConstPtr& msg) {
  if (flag) {
    flag = 0;
    const vector<float> input = msg->ranges;
    PointStore::_points.clear();
    double j = msg->angle_min;
    cout << msg->angle_max<<endl;
    cout << (int) ((msg->angle_max - msg->angle_min)/msg->angle_increment) <<input.size()<< endl;
    for (int i = 0; i < input.size(); i++) {
      if ((input[i] > msg->range_max)||(input[i] < msg->range_min))
	     ;
      else {
        PointStore::_points.push_back(std::make_pair(input[i],j));
      }
      j+=msg->angle_increment;
    };
	cout << endl << input.size() << endl; 
    PointStore::print_points(511,file_name);
    cout << j<<'\t'<<"Finished\n";
  }
  else
    ;
}

int main(int argc, char** argv) {

  file_name = (char *)malloc(255*sizeof(char));

  ros::init(argc,argv,"scan_data_node");
  
  flag = 1;

  if (argc<2) 
    printf("!!!WARNING: Expected file name!!!\n");
  else 
    // file_name = argv[1];
    cout << argv[1] << endl;

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("/scan",1000,detection_callback);

  ros::spin();
}
