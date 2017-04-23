#include "defs.h"

class FE {

    public:
        virtual void load_data(string _infile);
        virtual void pre_processing();
        virtual void process_bareboness();
        virtual void process_full();
        virtual void print_output(string _outfile)
       
};