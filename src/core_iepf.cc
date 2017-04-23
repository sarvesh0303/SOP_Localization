#include "../lib/defs.h"

using namespace std;
using namespace Common;

namespace IEPF {

vector<line> iterative_end_point_fit(vector<point> Points,double iepf_threshold) {
	vector<line> result; int j;
	if (Points.size()==0)
		return result;
	else if (Points.size()==1) {
		result.push_back(line_fit(Points[0],Points[0]));
		return result;
	}
	point a = Points.front(); point b = Points.back();
	line l = line_fit(a,b);
	breakpoint d = maximum_dist(Points,l);
	double d_thres = iepf_threshold;
	if (d.value <= d_thres) {
		result.push_back(l);
	}
	else {
		int i = d.point_iter;
		result = iterative_end_point_fit(vector<point>(Points.begin(),Points.begin()+i+1),iepf_threshold);
		vector<line> to_append = iterative_end_point_fit(vector<point>(Points.begin()+i,Points.end()),iepf_threshold);
		result.insert(result.end(),to_append.begin(),to_append.end());
	}
	return result;
}

breakpoint maximum_dist(vector<point> Points, line L) {
	double dist,max_dist;
	int iter;
	dist = max_dist = 0;
	for (int i = 0; i < Points.size(); i++) {
		dist = calc_distance(Points[i],L);
		if (dist > max_dist) {
				max_dist = dist;
				iter = i;
		}
	}
	// breakpoint ans = {iter,max_dist};
	// return ans;
	return {iter,max_dist};
}

double calc_distance(point p, line l) {
	return abs(l.m*p.x-p.y+l.c)/pow(1+pow(l.m,2),0.5);
}

line line_fit(point a, point b) {
	line l;
	if (abs(a.theta-b.theta) > 0.000000001) {
		l.m = (b.y - a.y)/(b.x - a.x);
		l.c = b.y - l.m*b.x;
		l.ends = make_pair(a,b);
	}
	else {
		l.m = 0;
		l.c = a.y;
		l.ends = make_pair(a,a);
	}
	return l;
}
}