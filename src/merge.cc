#include "../lib/defs.h"

using namespace std;
using namespace Common;

namespace Merge {

vector<line> merge(vector<line> raw,double slope, double dist) {
  vector<line> result;
  if (raw.size()<2) {
    return raw;
  }
  for (int i = 0; i < raw.size()-1; i++) {
    line a = raw[i];
    line b = raw[i+1];
    if ((abs(a.m - b.m) < slope)&&(calc_distance(a.ends.second,b.ends.first)<dist))
        result.push_back(line_fit(a.ends.first,b.ends.second));
    else {
        result.push_back(a);
        result.push_back(b);
    }
  }
  return result;
}

line line_fit(point a, point b) {
  return IEPF::line_fit(a,b);
}

double calc_distance(point a,point b) {
  return Adaptive::calc_distance(a,b);
}

}
