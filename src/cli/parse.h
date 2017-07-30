#ifndef CLI_PARSE_H
#define CLI_PARSE_H

#include <string>
#include <vector>

typedef enum subcmd_t {
    PARSE, SHOW, ANALYZE
} subcmd_t;

void dispatch_cmd(subcmd_t cmd, const std::vector<std::string>& args);
subcmd_t determine_cmd(const std::vector<std::string>& args);

#endif // CLI_PARSE_H
