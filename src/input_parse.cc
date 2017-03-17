#include "../lib/defs.h"

using namespace std;

point make_point(double r,double theta) {
  point ans;
  ans.r = r;
  ans.theta = theta;
  ans.x = r*cos(theta);
  ans.y = r*sin(theta);
  return ans;
}

vector<point> parse_input(string filename) {
  vector<point> result;
  FILE* fp = fopen(filename.c_str(),"r");
  double theta,r;
  while(1) {
    if (feof(fp))
      break;
    fscanf(fp,"%lf, %lf\n",&theta,&r);
    result.push_back(make_point(r,theta));
  }
  return result;
}
