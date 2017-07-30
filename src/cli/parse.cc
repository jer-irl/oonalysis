#include <vector>
#include <string>
#include <exception>
#include "parse.h"

subcmd_t determine_cmd(const std::vector<std::string>& args)
{
    const std::string cmd = args[1];
    if (cmd == "parse") {
        return PARSE;
    } else if (cmd == "show") {
        return SHOW;
    } else if (cmd == "analyze") {
        return ANALYZE;
    } else {
        throw std::invalid_argument("bad subcommand");
    }
}

void dispatch_cmd(subcmd_t cmd, const std::vector<std::string>& args)
{
    switch (cmd) {
    case PARSE:
    case SHOW:
    case ANALYZE:
    default:
        throw std::invalid_argument("bad subcommand");
        break;
    }
}
