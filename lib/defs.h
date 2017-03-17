#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <utility>
#include <cmath>
#include <string>

using namespace std;

struct point {
  double r;
  double theta;
  double x;
  double y;
};

void sequence_points(vector<point> unsorted);
vector<int> adaptive_detection(vector<point> sorted,double,double);
vector<vector<point>> adaptive_result(vector<point>,double,double);
bool comparison_func(point a, point b);
double calc_distance(point a, point b);

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

vector<line> iterative_end_point_fit(vector<point> Points,double);
double calc_distance(point p, line l);
breakpoint maximum_dist(vector<point> Points, line L);
line line_fit(point a, point b);
double abd_threshold(point,point,double,double);
vector<line> merge(vector<line> raw,double,double);

vector<point> parse_input(string filename);
