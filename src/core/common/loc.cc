#include <cstdint>
#include <string>
#include <fstream>
#include "loc.h"

namespace oonalysis::core::common {

uint32_t loc_in_file(const std::string& file)
{
    std::ifstream f(file);
    std::string buf;
    uint32_t res = 0;

    while ((std::getline(f, buf))) {
        res++;
    }

    return res;
}


} // namespace oonalysis::core::common
