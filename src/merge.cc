#include "../lib/defs.h"
using namespace std;

vector<line> merge(vector<line> raw) {
  vector<line> result;
  for (int i = 0; i < raw.size(); i++) {
    if ((abs(a.m - b.m) < SLOPE_THRESHOLD)&&(calc_distance(a.ends.second,b.ends.first)<DIST_THRESHOLD))
        result.push_back(line_fit(a.ends.first,b.ends.second));
    else {
        result.push_back(a);
        result.push_back(b);
    }
  }
  return result;
}
