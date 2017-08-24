#ifndef CLI_PARSE_H
#define CLI_PARSE_H

#include <string>
#include <vector>


namespace oonalysis::cli {

typedef enum subcmd_t {
    PARSE, SHOW, ANALYZE
} subcmd_t;

void main_cli(int argc, char** argv);
void dispatch_analyze(const std::vector<std::string>& inputs);
void dispatch_parse(const std::vector<std::string>& inputs, const std::string& output);

} // namespace oonalysis::cli

#endif // CLI_PARSE_H

