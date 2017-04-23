#include "../lib/sarvesh_fe.h"

using namespace std;
using namespace Common;

Process::Process(char* file_name,double _c0, double _c1) {
    file_string = file_name;
    abd_c0 = _c0; abd_c1 = _c1;
    iepf_th = merge_slope = merge_dist = 0;
}

void Process::get_input() {
    input_list = Load::parse_input(file_string);
    Load::sequence_points(input_list);
}

void Process::do_abd(double c0, double c1) {
    post_abd = Adaptive::adaptive_result(input_list,c0,c1);
}

void Process::do_iepf(double iepf_thres, double m_slope, double m_dist) {
    vector<line> calc;
    for (int i = 0; i < post_abd.size(); i++) {
        calc = Merge::merge(IEPF::iterative_end_point_fit(post_abd[i],iepf_thres),m_slope,m_dist);
        std::copy(calc.begin(),calc.end(),back_inserter(post_iepf));
    }
}

void Process::final_plot() {
    image = cv::Mat::zeros(WIN_SIZE_X,WIN_SIZE_Y,CV_8UC3);
    cv::circle(image,cv::Point(XSHIFT,YSHIFT),2,cv::Scalar(255,100,100));
    for (vector<point>::iterator it = input_list.begin();it!=input_list.end();it++) {
        cv::circle(image,cv::Point(it->x*XSCALE+XSHIFT,it->y*YSCALE+YSHIFT),2,cv::Scalar(100,100,255));
    }
    for (vector<line>::iterator it = post_iepf.begin(); it != post_iepf.end(); it++) {
        point p1 = it->ends.first; point p2 = it->ends.second;
        cv::line(image,cv::Point(p1.x*XSCALE+XSHIFT,p1.y*YSCALE+YSHIFT),cv::Point(p2.x*XSCALE+XSHIFT,p2.y*YSCALE+YSHIFT),cv::Scalar(100,255,100));
    }
    cv::imshow("Window",image);
}

void Process::generate_ui() {
    cv::namedWindow("Parameters",1);
    cv::createTrackbar("iepf_th","Parameters",&s3,200,on_iepf);
    cv::createTrackbar("merge_slope","Parameters",&s4,50,on_iepf);
    cv::createTrackbar("merge_dist","Parameters",&s5,50,on_iepf);
    cv::waitKey(0);
}

void Process::on_iepf(int,void*) {
    post_iepf.clear();
    iepf_th = s3/2000.0; merge_slope = s4/50.0; merge_dist = s5/50.0;
    do_iepf(iepf_th,merge_slope,merge_dist);
}

Sarvesh_FE::Sarvesh_FE(char* file_name) {
    file_string = file_name;
    cout << "Enter abd_c0:" << endl;
    cin >> abd_c0;
    cout << "Enter abd_c1:" << endl;
    cin >> abd_c1;
    proc = new Process(file_string,abd_c0,abd_c1);
}

void Sarvesh_FE::load_data() {
    proc->get_input();    
}

void Sarvesh_FE::pre_processing() {
    proc->do_abd(abd_c0,abd_c1);
}

void Sarvesh_FE::process_barebones() {
    cout << "Enter iepf_threshold: " << endl;
    cin >> iepf_th;
    cout << "Enter merge critical distance: " << endl;
    cin >> merge_dist;
    cout << "Enter merge critical slope: " << endl;
    cin >> merge_slope;
    proc->do_iepf(iepf_th,merge_dist,merge_slope);
}

void Sarvesh_FE::process_full() {
    proc->final_plot();
    proc->generate_ui();
}

void Sarvesh_FE::print_output(string _outfile) {
    ;
}