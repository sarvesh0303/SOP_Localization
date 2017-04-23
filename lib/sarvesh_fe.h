#include "defs.h"
#include "cvdefs.h"

using namespace std;
using namespace Common;

class Sarvesh_FE : public FE {

    public:
        char* file_string;
        Process* proc;
                
        Sarvesh(char* file_name);
        void load_data();
        void pre_processing();
        void process_barebones();
        void process_full();
        void print_output(string _outfile);
}

class Process {
    private:
        cv::Mat image;
        char* file_string;
        vector<point> input_list;
        vector<point<point>> post_abd;
        vector<line> post_iepf;
        double abd_c0,abd_c1,iepf_th,merge_dist,merge_slope;
    public:
        Process(char* file_name,double abd_c0, double abd_c1);
        void get_input();
        void do_abd(double c0,double c1);
        void do_iepf(double iepf_thres,double m_slope, double m_dist);
        void final_plot();
        void generate_ui();
        void on_iepf(int,void*);
        void on_abd(int,void*);
}