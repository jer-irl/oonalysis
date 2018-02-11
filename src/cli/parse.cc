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

po::options_description parse_options_desc() {
    po::options_description desc("Parse options");
    desc.add_options()
        ("help,h", "Produce a help message")
        ("output,o", po::value<std::string>(), "The database filename to use")
        ("input,i", po::value<std::vector<std::string>>(), "The input files")
        ;
    return desc;
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

    db::Database db = db::get_storage(vm["output"].as<std::string>());
    core::parse_files(db, filenames);
}

} // namespace oonalysis::cli

