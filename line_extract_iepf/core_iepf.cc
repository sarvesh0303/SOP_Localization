#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct line {
	double m;
	double c;
}

struct line_alt {
	double d;
	double theta;
}

struct point {
	double r;
	double theta;
}

vector<line> iterative_end_point_fit(vector<point> Points) {
	point a = Points.front; point b = Points.back;
	line l = line_fit(a,b);
	double d = maximum_dist(Points,l);
	double d_thres = calc_threshold(Points,l);
}

double maximum_dist(vector<point> Points, line L) {
	
}
