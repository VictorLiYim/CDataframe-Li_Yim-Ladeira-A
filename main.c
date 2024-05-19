#include "cdataframe.h"
int main() {
    CDataframe * cDataframe;
    cDataframe = create_CDataframe(2);
    read_cdataframe_hardway(cDataframe);
    print_CDataframe(cDataframe);
    print_name(cDataframe);
    print_num_raw(cDataframe);
    print_num_col(cDataframe);
    return 0;
}
