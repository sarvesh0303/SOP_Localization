#include "../lib/defs.h"

using namespace std;

double calc_threshold(vector<point>,line) {
	return 0.2;
}

vector<line> iterative_end_point_fit(vector<point> Points) {
	vector<line> result; int j;
	point a = Points.front(); point b = Points.back();
	line l = line_fit(a,b);
	breakpoint d = maximum_dist(Points,l);
	double d_thres = calc_threshold(Points,l);
	if (d.value < d_thres)
		result.push_back(l);
	else {
		int i = d.point_iter;
		result = iterative_end_point_fit(vector<point>(Points.begin(),Points.begin()+i));
		vector<line> to_append = iterative_end_point_fit(vector<point>(Points.begin()+i,Points.end()));
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
	l.m = (b.y - a.y)/(b.x - a.x);
	l.c = b.y - l.m*b.x;
	l.ends = make_pair(a,b);
	return l;
}

main() {
	cout<<"this works, for now"<<endl;
	return 0;
}
