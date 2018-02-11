#include "parse.h"

#include <vector>
#include <string>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include "core/parse.h"
#include "db/db.h"
#include "list.h"
#include "metrics/metrics.h"
extern "C" {
#include "util/log.h"
}
#include "util/files.h"

namespace po = boost::program_options;

namespace oonalysis::cli {

typedef enum subcmd_t {
    PARSE, LIST, HELP
} subcmd_t;


std::tuple<po::options_description, po::positional_options_description> help_options_desc() {
    po::options_description desc("Help pages available");
    desc.add_options()
        ("command", "subcommand to hear about")
        ;

    po::positional_options_description pd;
    pd.add("command", 1);

    return std::make_tuple(desc, pd);
}

po::options_description parse_options_desc() {
    po::options_description desc("Parse options");
    desc.add_options()
        ("help,h", "Produce a help message")
        ("output,o", po::value<std::string>(), "The database filename to use")
        ("input,i", po::value<std::vector<std::string>>(), "The input files")
        ;
    return desc;
}

po::options_description analyze_options_desc() {
    po::options_description desc("Analyze options");
    desc.add_options()
        ("help,h", "Produce a help message")
        ("input,i", po::value<std::string>(), "The input database")
        ;
    return desc;
}

subcmd_t determine_cmd(const std::string& cmd) {
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

void dispatch_cmd(subcmd_t cmd, const std::vector<std::string>& args) throw() {
    switch (cmd) {
    case PARSE:
        main_parse(args);
        break;
    case LIST:
        list_main(args);
        break;
    case HELP:
        main_help(args);
        break;
    default:
        throw std::invalid_argument("bad subcommand");
        break;
    }
}

void main_help(const std::vector<std::string>& args) {
    auto pair = help_options_desc();

    po::variables_map vm;
    po::parsed_options parsed = po::command_line_parser(args)
        .options(std::get<0>(pair))
        .positional(std::get<1>(pair))
        .run();
    po::store(parsed, vm);
    po::notify(vm);

    if (!vm.count("command")) {
        std::cout << std::get<0>(pair);
        exit(0);
    }

    subcmd_t cmd = determine_cmd(vm["command"].as<std::string>());
    switch (cmd) {
    case PARSE:
        std::cout << parse_options_desc();
        break;
    case ANALYZE:
        std::cout << analyze_options_desc();
        break;
    case HELP:
        std::cout << std::get<0>(pair);
        break;
    default:
        throw std::invalid_argument("bad subcommand");
        break;
    }
    exit(0);
}


void main_parse(const std::vector<std::string>& args) {
    LOG(TRACE, "Dispatching parse");

    po::options_description desc = parse_options_desc();

    po::variables_map vm;
    po::parsed_options parsed = po::command_line_parser(args).options(desc).run();
    po::store(parsed, vm);
    po::notify(vm);

    if (!vm.count("input")) {
        LOG(ERROR, "Inputs required");
        exit(1);
    }

    std::vector<std::string> filenames;

    std::vector<std::string> inputs = vm["input"].as<std::vector<std::string>>();

    for (auto iter = inputs.begin(); iter != inputs.end(); iter++) {
        std::vector<std::string> globbed = util::glob(*iter);
        filenames.insert(filenames.end(), globbed.begin(), globbed.end());
    }

    db::set_db_name(vm["output"].as<std::string>());
    db::init_db();
    core::parse_files(filenames);
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
        std::cout << desc;
        exit(0);
    }

    // Use options
    subcmd_t cmd;
    try {
        cmd = determine_cmd(vm["command"].as<std::string>());
    } catch (std::invalid_argument& ex) {
        LOG(CRITICAL, "Invalid command");
        exit(1);
    }

    auto args = po::collect_unrecognized(parsed.options, po::include_positional);
    args.erase(args.begin());
    dispatch_cmd(cmd, args);
}

} // namespace oonalysis::cli

