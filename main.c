#include "cdataframe.h"
int main() {
    CDataframe * cDataframe;
    cDataframe = create_CDataframe(2);
    read_CDataframe(cDataframe);
    print_CDataframe(cDataframe);
    print_CDataframe_limited_raw(cDataframe);
    print_CDataframe_limited_columns(cDataframe);
    add_raw(cDataframe);
    add_column(cDataframe);
    delete_raw(cDataframe);
    delete_columncdf(cDataframe);
    print_CDataframe(cDataframe);
    return 0;
}
