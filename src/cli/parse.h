#ifndef CLI_PARSE_H
#define CLI_PARSE_H

#include <string>
#include <vector>


namespace oonalysis {
namespace cli {

typedef enum subcmd_t {
    PARSE, SHOW, ANALYZE
} subcmd_t;

void dispatch_cmd(subcmd_t cmd, const std::vector<std::string>& args);
subcmd_t determine_cmd(const std::vector<std::string>& args);
std::string dbname_from_args(std::vector<std::string> args);

void dispatch_parse(const std::vector<std::string>& args);
void dispatch_show(const std::vector<std::string>& args);
void dispatch_analyze(const std::vector<std::string>& args);

} // namespace cli
} // namespace oonalysis

#endif // CLI_PARSE_H

