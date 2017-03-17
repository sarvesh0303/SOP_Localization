#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

struct point {
  double r;
  double theta;
  double x;
  double y;
}
typedef point breakpoint;

void sequence_points(vector<point> unsorted);
vector<int> adaptive_detection(vector<point> sorted);
vector<vector<point>> adaptive_result(vector<point>);
bool comparison_func(point a, point b);
double calc_distance(point a, point b);
double iepf_threshold(point a, point b);

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
double calc_distance(point p, line l);
breakpoint maximum_dist(vector<point> Points, line L);
line line_fit(point a, point b);
double DIST_THRESHOLD;
double SLOPE_THRESHOLD;
double abd_threshold(point,point);
vector<line> merge(vector<line> raw);

vector<point> parse_input(char* filename);
