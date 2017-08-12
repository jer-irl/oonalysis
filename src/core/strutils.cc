#include <string>
#include <sstream>
#include <vector>
#include "strutils.h"
extern "C" {
#include "util/log.h"
}


namespace oonalysis {
namespace core {

std::vector<std::string> str_split(const std::string& str,
                                   char delim)
{
    std::vector<std::string> res;
    std::stringstream ss(str);
    std::string item;
    while (std::getline(ss, item, delim)) {
        res.push_back(item);
    }
    return res;
}

std::string str_join(const std::vector<std::string>& strings,
                     const std::string& glue)
{
    std::string res = "";
    for (std::string str : strings) {
        res += glue + str;
    }
    return res;
}

char first_nonwhitespace(const std::string& line)
{
    for (int i = 0; line[i] != '\0'; ++i) {
        if (!iswspace(line[i])) {
            return line[i];
        }
    }
    return '\0';
}

std::string to_lower(const std::string& str)
{
    std::string res("");
    for (char c : str) {
        res += std::tolower(c);
    }
    return res;
}

} // namespace core
} // namespace oonalysis
