#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <cmath>

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

vector<line> iterative_end_point_fit(vector<point> Points);
breakpoint maximum_dist(vector<point> Points, line L);
double calc_distance(point p, line l);
line line_fit(point a, point b);
