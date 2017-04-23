#include "defs.h"
#include "cvdefs.h"
#include "feature_extract.h"

using namespace std;

class Process {
    private:
        cv::Mat image;
        char* file_string;
        vector<point> input_list;
        vector<vector<point>> post_abd;
        vector<line> post_iepf;
        int s3,s4,s5;
    public:
        double abd_c0,abd_c1,iepf_th,merge_dist,merge_slope;

        Process(char* file_name,double abd_c0, double abd_c1);
        void get_input();
        void do_abd(double c0,double c1);
        void do_iepf(double iepf_thres,double m_slope, double m_dist);
        void final_plot();
        void generate_ui();
        static void on_iepf(int,void*);
        void on_abd(int,void*);
        void print_output(string,string);
};

class Sarvesh_FE {

    public:
        char* file_string;
        Process* proc;
                
        Sarvesh_FE(char* file_name);
        void load_data();
        void pre_processing();
        void process_barebones();
        void process_full();
        void print_output(string,string);
};


void on_iepf(int, void* proc);