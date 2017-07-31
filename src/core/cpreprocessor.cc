#include <sstream>
#include <vector>
#include <string>

#include "cpreprocessor.h"
#include "strutils.h"

namespace oonalysis {
namespace core {

std::string pprocess_str(std::string input)
{
    std::vector<std::string> lines;
    std::istringstream iss(input);
    char buf[1024];

    while (iss.getline(buf, 1024)) {
        lines.push_back(std::string(buf));
    }

    std::string res("");
    for (std::string line : lines) {
        if (first_nonwhitespace(line) != '#') { continue; }
        // TODO
    }

    return res;
}

} // namespace core
} // namespace oonalysis
