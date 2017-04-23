#include "../lib/sarvesh_fe.h"

using namespace std;
using namespace Common;


Process::Process(char* file_name,double _c0, double _c1) {
    file_string = file_name;
    abd_c0 = _c0; abd_c1 = _c1;
    iepf_th = merge_slope = merge_dist = 0;
    cout << file_string << endl;
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
    cv::waitKey(0);
}

void Process::generate_ui() {
    cv::namedWindow("Parameters",1);
    cv::createTrackbar("iepf_th","Parameters",&s3,200,on_iepf,(void *) this);
    cv::createTrackbar("merge_slope","Parameters",&s4,50,on_iepf,(void *) this);
    cv::createTrackbar("merge_dist","Parameters",&s5,50,on_iepf,(void *) this);
    cv::waitKey(0);
}

void Process::on_iepf(int,void*) {
    // post_iepf.clear();
    // iepf_th = s3/2000.0; merge_slope = s4/50.0; merge_dist = s5/50.0;
    // do_iepf(iepf_th,merge_slope,merge_dist);
}

void Process::print_output(string _outfile, string _jpgpath) {
    FILE* fp = fopen(_outfile.c_str(),"w");
    fprintf(fp,"The lines generated are: \n");
    line temp; point start,end;
    for (int i = 0; i < post_iepf.size(); i++) {
        temp = post_iepf[i];
        start = temp.ends.first;
        end = temp.ends.second;
        fprintf(fp,"Line %d: \n m = %lf, c = %lf\n a = (%lf,%lf), b = (%lf,%lf)\n",i,temp.m,temp.c,start.x,start.y,end.x,end.y);
    }
    cv::imwrite(_jpgpath,image);
}

Sarvesh_FE::Sarvesh_FE(char* file_name) {
    file_string = file_name;
    double abd_c0,abd_c1;
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
    proc->do_abd(proc->abd_c0,proc->abd_c1);
}

void Sarvesh_FE::process_barebones() {
    cout << "Enter iepf_threshold: " << endl;
    cin >> proc->iepf_th;
    cout << "Enter merge critical distance: " << endl;
    cin >> proc->merge_dist;
    cout << "Enter merge critical slope: " << endl;
    cin >> proc->merge_slope;
    proc->do_iepf(proc->iepf_th,proc->merge_dist,proc->merge_slope);
    proc->final_plot();
}

void Sarvesh_FE::process_full() {
    proc->final_plot();
    proc->generate_ui();
}

void Sarvesh_FE::print_output(string _outfile,string _jpg) {
    proc->print_output(_outfile,_jpg);
}

void on_iepf(int d,void* proc) {
    Process* proc1 = (Process *) proc;
    proc1->iepf_th = d;
    cout << proc1->iepf_th << endl;
    //Then use Sarvesh_FE->proc = proc1
}