#include <string>
#include <vector>

#include "strutils.h"


namespace oonalysis {

std::vector<std::string> str_split(const std::string& str,
                                   const std::string& delim)
{
    std::vector<std::string> res;
    int pos = 0;
    int prev_pos = 0;
    int count = 0;
    while ((pos = str.substr(prev_pos).find(delim, pos)) != -1) {
        res.push_back(str.substr(prev_pos, pos));
        prev_pos = pos + delim.length();
        count++;
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

} // namespace oonalysis
