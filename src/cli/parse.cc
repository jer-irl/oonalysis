#include <vector>
#include <string>
#include <exception>
#include <tuple>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include "parse.h"
#include "core/parse.h"
#include "db/init.h"
#include "metrics/metrics.h"
extern "C" {
#include "util/log.h"
}

namespace fs = boost::filesystem;
namespace {

static std::vector<std::string> glob(const std::string& filename)
{
    LOG(TRACE, "Globbing filenames");
    std::vector<std::string> res;
    fs::path p = filename;

    if (!fs::is_directory(p)) {
        res.push_back(p.native());
        return res;
    }

    for (auto iter : fs::recursive_directory_iterator(p)) {
        if (fs::is_regular_file(iter)) {
            res.push_back(iter.path().native());
        }
    }

    return res;
}

} // anon namespace

namespace po = boost::program_options;
namespace oonalysis::cli {

subcmd_t determine_cmd(const std::string& cmd)
{
    LOG(DEBUG, "Determining subcommand");

    if (cmd == "parse") {
        return PARSE;
    } else if (cmd == "show") {
        return SHOW;
    } else if (cmd == "analyze") {
        return ANALYZE;
    } else if (cmd == "") {
        LOG(ERROR, "Subcommand required");
        throw std::invalid_argument("No subcommand");
    } else {
        throw std::invalid_argument("bad subcommand");
    }
}

void dispatch_cmd(subcmd_t cmd, const std::vector<std::string>& inputs, const std::string& output)
{
    switch (cmd) {
    case PARSE:
        dispatch_parse(inputs, output);
        break;
    case ANALYZE:
        dispatch_analyze(inputs);
        break;
    case SHOW:
    default:
        throw std::invalid_argument("bad subcommand");
        break;
    }
}

void dispatch_analyze(const std::vector<std::string>& inputs)
{
    LOG(TRACE, "Dispatching analyze");

    if (inputs.size() > 2) {
        LOG(ERROR, "Cannot have multiple inputs to analyze");
        exit(1);
    } else if (inputs.size() < 2) {
        LOG(ERROR, "Need an input and a command");
        exit(1);
    }

    db::set_db_name(inputs[1]);
    metrics::main_metrics(inputs[0]);
}

void dispatch_parse(const std::vector<std::string>& inputs, const std::string& output)
{
    LOG(TRACE, "Dispatching parse");

    std::vector<std::string> filenames;

    for (auto iter = inputs.begin(); iter != inputs.end(); iter++) {
        // Positional filenames
        std::vector<std::string> globbed = glob(*iter);
        filenames.insert(filenames.end(), globbed.begin(), globbed.end());
    }

    db::set_db_name(output);
    db::init_db();
    core::parse_files(filenames);
}

void main_cli(int argc, char** argv)
{
    // Describe
    po::options_description desc("Allowed options");
    desc.add_options()
        ("subcommand", po::value<std::string>(), "analyze or parse")
        ("input,i", po::value<std::vector<std::string>>(), "input file")
        ("output,o", po::value<std::string>(), "output file")
    ;

    po::positional_options_description pd;
    pd.add("subcommand", 1);
    pd.add("input", -1);

    // Parse
    po::variables_map vm;
    po::store(
            po::command_line_parser(argc, argv).options(desc).positional(pd).run(),
            vm);
    po::notify(vm);

    // Use options
    subcmd_t cmd;
    if (!vm.count("subcommand")) {
        LOG(ERROR, "No subcommand");
        std::cout << "Subcommand required" << std::endl;
        exit(1);
    } else {
        cmd = determine_cmd(vm["subcommand"].as<std::string>());
    }

    std::vector<std::string> inputs;
    if (vm.count("input")) {
        inputs = vm["input"].as<std::vector<std::string>>();
    }

    std::string output;
    if (vm.count("output")) {
        output = vm["output"].as<std::string>();
    }

    dispatch_cmd(cmd, inputs, output);
}

} // namespace oonalysis::cli

