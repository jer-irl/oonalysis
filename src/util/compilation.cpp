#include "compilation.hpp"

#include <boost/algorithm/string.hpp>

namespace oonalysis::util {

std::vector<std::string> clang_default_arguments() {
    std::system("echo | g++ -E -Wp,-v - &> tmp.txt");
    FILE* output = std::fopen("tmp.txt", "r");
    char buf[4096];
    std::fread(buf, sizeof(char), 4096, output);
    buf[4095] = '\0';
    std::string buffer_str(buf);

    std::vector<std::string> lines;
    boost::split(lines, buffer_str, boost::is_any_of("\n"));

    std::vector<std::string> res;
    for (std::string line : lines) {
        if (line[0] != ' ') {
            continue;
        }

        std::vector<std::string> toks;
        boost::split(toks, line, boost::is_any_of(" "));
        res.emplace_back("-I" + toks[1]);
    }

    return res;
}

}