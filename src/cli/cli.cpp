#include "cli.h"

#include <iostream>
#include <boost/program_options.hpp>
#include "help.h"
#include "list.h"
#include "parse.h"

namespace po = boost::program_options;
namespace oonalysis::cli {

typedef enum subcmd_t {
    PARSE, LIST, HELP
} subcmd_t;

static void print_usage() {
    std::cout <<
              "Welcome to oonalysis.  The program is broken into subprograms\n"
              "similarly to git.\n"
              "\n"
              "Usage: oonalysis-cli command [args...]\n"
              "\n"
              "Available commands:\n"
              "     list\n"
              "     parse\n"
              "     help\n" << std::endl;
}

static subcmd_t determine_cmd(const std::string& cmd) {
    if (cmd == "parse") {
        return PARSE;
    } else if (cmd == "help") {
        return HELP;
    } else if (cmd == "list") {
        return LIST;
    } else if (cmd.empty()) {
        throw std::invalid_argument("No subcommand");
    } else {
        throw std::invalid_argument("bad subcommand");
    }
}

static void dispatch_cmd(subcmd_t cmd, const std::vector<std::string>& args) throw() {
    switch (cmd) {
        case PARSE:
            main_parse(args);
            break;
        case LIST:
            list_main(args);
            break;
        case HELP:
            help_main(args);
            break;
        default:
            throw std::invalid_argument("bad subcommand");
    }
}

void main_cli(int argc, char** argv) {
    // Describe
    po::options_description desc("Allowed options");
    desc.add_options()
            ("command", po::value<std::string>(), "parse, list, help")
            ("subargs", po::value<std::vector<std::string>>(), "Arguments for command")
            ;

    po::positional_options_description pd;
    pd.add("command", 1).add("subargs", -1);

    // Parse
    po::variables_map vm;
    po::parsed_options parsed = po::command_line_parser(argc, argv).options(desc).positional(pd).allow_unregistered().run();
    po::store(parsed, vm);
    po::notify(vm);

    // Global options
    if (!vm.count("command")) {
        print_usage();
        exit(0);
    }

    // Use options
    subcmd_t cmd;
    try {
        cmd = determine_cmd(vm["command"].as<std::string>());
    } catch (std::invalid_argument& ex) {
        exit(1);
    }

    auto args = po::collect_unrecognized(parsed.options, po::include_positional);
    args.erase(args.begin());
    dispatch_cmd(cmd, args);
}

} // namespace oonalysis::cli