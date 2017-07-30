#include <vector>
#include <string>
#include <exception>
#include <tuple>
#include "parse.h"
#include "core/parse.h"
#include "db/db.h"

extern char DB_NAME[256];

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
        dispatch_parse(args);
        break;
    case SHOW:
        dispatch_show(args);
        break;
    case ANALYZE:
        dispatch_analyze(args);
        break;
    default:
        throw std::invalid_argument("bad subcommand");
        break;
    }
}

void dispatch_parse(const std::vector<std::string>& args)
{
    std::vector<std::string> filenames;
    std::string output = ":memory:";
    for (auto iter = args.begin() + 2; iter != args.end(); iter++) {
        // Output option
        if (*iter == "-o") {
            iter++;
            output = *iter;
            continue;
        }

        // Positional filenames
        filenames.push_back(*iter);
    }

    strncpy(DB_NAME, output.c_str(), 256);
    parse_files(filenames);
}
