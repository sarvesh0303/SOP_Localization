#include "../lib/defs.h"

using namespace std;
using namespace Common;

namespace Adaptive {

bool comparison_func(point a, point b) {
  return (a.theta < b.theta);
}

void sequence_points(vector<point> unsorted) {
  Load::sequence_points(unsorted);
}

vector<vector<point>> adaptive_result(vector<point> sorted,double c0,double c1) {
  vector<int> breaks = adaptive_detection(sorted,c0,c1);
  vector<vector<point>> result; vector<point> sub_result;
  int j = 0;
  for (int i = 0; i < sorted.size(); i++) {
    sub_result.push_back(sorted[i]);
    if ((j < breaks.size()) && (i == breaks[j])) {
      result.push_back(sub_result);
      sub_result.clear();
      j++;
    }
  }
  result.push_back(sub_result);
  return result;
}

double abd_threshold(point p1, point p2,double c0, double c1) {
  return c0 + c1*abs(p2.r-p1.r)/abs(p2.r+p1.r);
}

vector<int> adaptive_detection(vector<point> sorted,double c0,double c1) {
  vector<int> result;
  for (int i = 0; i < sorted.size()-1; i++) {
    if (calc_distance(sorted[i],sorted[i+1]) > abd_threshold(sorted[i],sorted[i+1],c0,c1))
      result.push_back(i);
  }
  return result;
}


double calc_distance(point a, point b) {
  return pow(pow(a.x-b.x,2)+pow(a.y-b.y,2),0.5);
}

}