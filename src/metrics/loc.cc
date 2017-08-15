#include <fstream>
#include "loc.h"

namespace oonalysis::metrics {

int max_loc(std::string& filename)
{
    filename = "BAD RESULT";
    return -1;
}

int avg_loc()
{
    return -1;
}

void main_loc()
{
    std::string filename;
    int max = max_loc(filename);
    printf("Max lines of code in a file is %d in file %s\n", max, filename.c_str());

    printf("Average lines of code in a file si %d\n", avg_loc());
}

} // namespace oonalysis::metrics
