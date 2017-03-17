#include "../lib/defs.h"
#include "../lib/cvdefs.h"

using namespace std;
cv::Mat image;
vector<point> input_list;
vector<vector<point>> post_abd;
vector<line> post_iepf;
int s1,s2,s3,s4,s5;
double abd_c0,abd_c1,iepf_th,merge_slope,merge_dist;

void get_input() {
  input_list = parse_input("/home/abc/sarvesh/points.txt");
  sequence_points(input_list);
}

void do_abd(double c0,double c1) {
  post_abd = adaptive_result(input_list,c0,c1);
}

void do_iepf(double iepf_thres,double m_slope,double m_dist) {
  vector<line> calc;
  for (int i = 0; i < post_abd.size(); i++) {
    calc = merge(iterative_end_point_fit(post_abd[i],iepf_thres),m_slope,m_dist);
    std::copy(calc.begin(),calc.end(),back_inserter(post_iepf));
  }
}

void final_plot() {
  image = cv::Mat::zeros(WIN_SIZE_X,WIN_SIZE_Y,CV_8UC3);
  for (vector<point>::iterator it = input_list.begin();it!=input_list.end();it++) {
    cv::circle(image,cv::Point(it->x*XSCALE+XSHIFT,it->y*YSCALE+YSHIFT),2,cv::Scalar(100,100,255));
  }
  for (vector<line>::iterator it = post_iepf.begin(); it != post_iepf.end(); it++) {
    point p1 = it->ends.first; point p2 = it->ends.second;
    cout << p1.x << '\t' <<p1.y << '\t'<<p2.x<<'\t'<<p2.y<<endl;
    cv::line(image,cv::Point(p1.x*XSCALE+XSHIFT,p1.y*YSCALE+YSHIFT),cv::Point(p2.x*XSCALE+XSHIFT,p2.y*YSCALE+YSHIFT),cv::Scalar(100,255,100));
  }
  cv::imshow("Window",image);
}

void on_abd(int,void*) {
  post_abd.clear(); post_iepf.clear();
  abd_c0 = s1/50.0;  abd_c1 = s2;
  iepf_th = s3/20.0;  merge_slope = s4/50.0;  merge_dist = s5/50.0;
  do_abd(abd_c0,abd_c1);
  do_iepf(iepf_th,merge_slope,merge_dist);
  final_plot();
}

void on_iepf(int,void*) {
  // cv::destroyWindow("Window");
  post_iepf.clear();
  iepf_th = s3/2000.0; merge_slope = s4/50.0; merge_dist = s5/500.0;
  do_iepf(iepf_th,merge_slope,merge_dist);
  final_plot();
}

int main() {
  cout << "Enter abd_c0:" << endl;
  cin >> abd_c0;
  cout << "Enter abd_c1:"<< endl;
  cin >> abd_c1;
  iepf_th = merge_dist = merge_slope = 0;
  get_input();
  cout << input_list.size() <<endl;
  do_abd(abd_c0,abd_c1);
  cout << post_abd.size() << endl;
  do_iepf(iepf_th,merge_slope,merge_dist);
  cout << post_iepf.size() << endl;
  final_plot();
  cv::namedWindow("Parameters",1);
  // cv::createTrackbar("abd_c0","Parameters",&s1,50,on_abd);//0-1:50
  // cv::createTrackbar("abd_c1","Parameters",&s2,50,on_abd);//0-50
  cv::createTrackbar("iepf_th","Parameters",&s3,200,on_iepf);
  cv::createTrackbar("merge_slope","Parameters",&s4,50,on_iepf);
  cv::createTrackbar("merge_dist","Parameters",&s5,50,on_iepf);
  cv::waitKey(0);
}
