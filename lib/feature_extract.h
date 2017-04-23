#include "defs.h"

class FE {

    public:
        FE(char* file_name){};
        virtual void load_data(){;};
        virtual void pre_processing(){;};
        virtual void process_barebones(){;};
        virtual void process_full(){;};
        virtual void print_output(string _outfile){;};
       
};