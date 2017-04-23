#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <utility>
#include <cmath>
#include <string>

#ifndef DEFS_H
#define DEFS_H

using namespace std;

struct point {
  double r;
  double theta;
  double x;
  double y;
};


struct line {
	double m;
	double c;
	pair<point,point> ends;
};

struct breakpoint {
	int point_iter;
	double value;
};


struct line_alt {
	double d;
	double theta;
};

namespace IEPF {
	vector<line> iterative_end_point_fit(vector<point>, double iepf_threshold);
	double calc_distance(point, line);
	line line_fit(point, point);
	breakpoint maximum_dist(vector<point>, line);
};

namespace Merge {
	vector<line> merge(vector<line>,double,double);
	line line_fit(point,point);
	double calc_distance(point,point);
};

namespace Adaptive {
	bool comparison_func(point,point);
	void sequence_points(vector<point>);
	vector<vector<point>> adaptive_result(vector<point>,double c0, double c1);
	double abd_threshold(point,point,double c0,double c1);
	vector<int> adaptive_detection(vector<point>,double,double);
	double calc_distance(point,point);
};

namespace Load {
	void sequence_points(vector<point>);
	vector<point> parse_input(string filename);
	point make_point(double r, double theta);
};

namespace Common {

};

#endif