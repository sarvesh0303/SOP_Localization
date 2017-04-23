#include "../lib/defs.h"

using namespace std;
using namespace Common;

namespace Load {

point make_point(double r,double theta) {
  point ans;
  ans.r = r;
  ans.theta = theta;
  ans.x = r*cos(theta);
  ans.y = r*sin(theta);
  return ans;
}

void sequence_points(vector<point> unsorted) {
  std::sort(unsorted.begin(),unsorted.end(),comparison_func);
}

vector<point> parse_input(string filename) {
  vector<point> result;
  FILE* fp = fopen(filename.c_str(),"r");
  double theta,r;
  while(1) {
    if (feof(fp))
      break;
    fscanf(fp,"%lf, %lf\n",&r,&theta);
    result.push_back(make_point(r,theta));
  }
  return result;
}

}