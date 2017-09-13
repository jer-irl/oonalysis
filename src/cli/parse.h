#ifndef CLI_PARSE_H
#define CLI_PARSE_H

#include <string>
#include <vector>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

namespace oonalysis::cli {

typedef enum subcmd_t {
    PARSE, ANALYZE, HELP
} subcmd_t;

void main_cli(int argc, char** argv);
void main_analyze(const std::vector<std::string>& args);
void main_parse(const std::vector<std::string>& args);
void main_help(const std::vector<std::string>& args);

} // namespace oonalysis::cli

#endif // CLI_PARSE_H

