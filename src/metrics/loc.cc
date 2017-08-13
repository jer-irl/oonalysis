#include <fstream>
#include "stdio.h"
#include "loc.h"

namespace oonalysis::metrics {

uint32_t loc_in_file(std::ifstream file)
{
    uint32_t res = 0;
    char c;

    while ((c = file.get())) {
        if (c == '\n') { ++res; }
    }

    return res;
}

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
