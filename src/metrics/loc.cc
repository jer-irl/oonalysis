#include <fstream>
#include "loc.h"

uint32_t loc_in_file(std::ifstream file)
{
    uint32_t res = 0;
    char c;

    while ((c = file.get())) {
        if (c == '\n') { ++res; }
    }

    return res;
}
