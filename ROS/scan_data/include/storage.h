#include <sstream>
#include <vector>
#include <utility>
#include "sensor_msgs/LaserScan.h"

using namespace std;

class PointStore {
public:
  static vector< pair<double,double> > _points;
  // static void update();
  // static void detection_callback(sensor_msgs::LaserScan::ConstPtr& a);
  static void print_points(int count,char*);
};
