#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct line {
	double m;
	double c;
};

struct line_alt {
	double d;
	double theta;
};

struct point {
	double r;
	double theta;
};

struct breakpoint {
	int point_iter;
	double value;
}
	
vector<line> iterative_end_point_fit(vector<point> Points) {
	vector<line> result; int j;
	point a = Points.front; point b = Points.back;
	line l = line_fit(a,b);
	double d = maximum_dist(Points,l).value;
	double d_thres = calc_threshold(Points,l);
	if (d < d_thres)
		result.push_back(l);
	else {
		//split step
	}
	return result;
}

breakpoint maximum_dist(vector<point> Points, line L) {
	double dist,max_dist;
	int iter;
	dist = max_dist = 0;
	for (int i = 0; i < Points.size; i++) {
		//calculation of distance and storing of corresponding iter here
	}
}
