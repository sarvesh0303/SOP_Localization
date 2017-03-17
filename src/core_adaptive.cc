#include "../libs/defs.h"

using namespace std;

bool comparison_func(point a, point b) {
  return (a.theta < b.theta);
}

void sequence_points(vector<point> unsorted) {
  std::sort(unsorted.begin(),unsorted.end(),comparison_func);
}

vector<vector<point>> adaptive_result(vector<point> sorted) {
  vector<int> breaks = adaptive_detection(sorted);
  vector<vector<point>> result; vector<point> sub_result;
  int j = 0;
  for (int i = 0; i < sorted.size(); i++) {
    sub_result.push_back(sorted[i]);
    if (i == breaks[j]) {
      result.push_back(sub_result);
      sub_result.clear();
      j++;
    }
  }
  result.push_back(sub_result);
  return result;
}

vector<int> adaptive_detection(vector<point> sorted) {
  vector<point> result;
  for (int i = 0; i < sorted.size()-1; i++) {
    if (calc_distance(sorted[i],sorted[i+1]) > abd_threshold(sorted[i],sorted[i+1]))
      result.push_back(i);
  }
  return result;
}

double calc_distance(point a, point b) {
  return pow(pow(a.x-b.x,2)+pow(a.y-b.y,2),0.5);
}
