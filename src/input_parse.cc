#include "../libs/defs.h"

using namespace std;

point make_point(r,theta) {
  point ans;
  ans.r = r;
  ans.theta = theta;
  ans.x = r*cos(theta);
  ans.y = r*sin(theta);
  return ans;
}

vector<point> parse_input(char* filename) {
  vector<point> result;
  FILE* fp = fopen(filename,"r");
  double theta,r;
  while (fp!=EOF) {
    fscanf(fp,"%lf, %lf\n",&theta,&r);
    result.push_back(make_point(r,theta));
  }
  return result;
}
