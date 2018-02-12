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
#include "util/files.h"

namespace po = boost::program_options;

namespace oonalysis::cli {

void main_parse(const std::vector<std::string>& args) {
    po::options_description desc("Parse options");
    desc.add_options()
            ("help,h", "Produce a help message")
            ("output,o", po::value<std::string>(), "The database filename to use")
            ("input,i", po::value<std::vector<std::string>>(), "The input files")
            ;

    po::positional_options_description pd;
    pd.add("input", -1);

    po::variables_map vm;
    po::parsed_options parsed = po::command_line_parser(args).options(desc).positional(pd).run();
    po::store(parsed, vm);
    po::notify(vm);

    if (!vm.count("input")) {
        std::cout << desc;
        exit(1);
    }

    std::vector<std::string> inputs = vm["input"].as<std::vector<std::string>>();
    db::Database db = db::get_storage(vm["output"].as<std::string>());
    db.remove_all<db::FunctionDecl>();
    db.remove_all<db::File>();
    core::parse_files(db, inputs);
}

} // namespace oonalysis::cli

