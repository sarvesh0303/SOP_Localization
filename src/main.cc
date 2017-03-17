#include "../lib/defs.h"

using namespace std;

vector<point> input_list;
vector<vector<point>> post_abd;
vector<line> post_iepf;

void get_input() {
  vector<point> input_list = parse_input("/home/abc/sarvesh/points.txt");
  sequence_points(point_list);
}

void do_abd() {
  vector<vector<point>> post_abd = adaptive_result(sorted);
}

void do_iepf() {
  vector<line> calc;
  for (int i = 0; i < post_abd.size(); i++) {
    calc = merge(iterative_end_point_fit(post_abd[i]))
    std::copy(calc.begin(),calc.end(),back_inserter(post_iepf));
  }
}

void final_plot() {
  for (int i = 0; i < sorted.size(); i++)
    plot_point(sorted[i]);

  for (int i = 0; i < post_iepf.size(); i++)
    plot_line(post_iepf[i]);

}

int main() {
}
