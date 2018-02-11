#include "help.h"

#include <iostream>
#include <boost/program_options.hpp>
extern "C" {
#include "util/log.h"
};

namespace po = boost::program_options;
namespace oonalysis::cli {

typedef enum subcmd_t {
    PARSE, LIST, HELP
} subcmd_t;

static subcmd_t determine_cmd(const std::string& cmd) {
    LOG(DEBUG, "Determining subcommand");

    if (cmd == "parse") {
        return PARSE;
    } else if (cmd == "help") {
        return HELP;
    } else if (cmd == "analyze") {
        return LIST;
    } else if (cmd == "") {
        LOG(ERROR, "Subcommand required");
        throw std::invalid_argument("No subcommand");
    } else {
        throw std::invalid_argument("bad subcommand");
    }
}

void help_main(const std::vector<std::string> &args) {

    po::options_description desc("Help pages available");
    desc.add_options()
            ("command", "subcommand to hear about");

    po::positional_options_description pd;
    pd.add("command", 1);

    po::variables_map vm;
    po::parsed_options parsed = po::command_line_parser(args)
            .options(desc)
            .positional(pd)
            .run();
    po::store(parsed, vm);
    po::notify(vm);

    if (!vm.count("command")) {
        std::cout << desc;
        exit(0);
    }

    subcmd_t cmd = determine_cmd(vm["command"].as<std::string>());
    switch (cmd) {
        case PARSE:
            std::cout << "Fill in help";
            break;
        case LIST:
            std::cout << "TODO fill in help";
            break;
        case HELP:
            std::cout << desc;
            break;
        default:
            throw std::invalid_argument("bad subcommand");
    }
    exit(0);
}

} // namespace oonalysis::cli
