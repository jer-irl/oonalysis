#include <cstdint>
#include <string>
#include <fstream>
#include "loc.h"

namespace oonalysis::core::common {

uint32_t loc_in_stream(std::istream& file)
{
    std::string buf;
    uint32_t res = 0;

    while ((std::getline(file, buf))) {
        res++;
    }

    return res;
}

uint32_t loc_in_file(const std::string& file)
{
    std::ifstream f(file);
    return loc_in_stream(f);
}


} // namespace oonalysis::core::common
