#include "list.h"

#include <iostream>
#include <boost/program_options.hpp>
#include "sqlite_orm/sqlite_orm.h"
#include "db/db.h"
#include "metrics/files.h"
extern "C" {
#include "util/log.h"
};

namespace po = boost::program_options;
namespace orm = sqlite_orm;
namespace oonalysis::cli {

void list_main(const std::vector<std::string>& args) {
    LOG(TRACE, "Dispatching analyze");

    po::options_description desc("Analyze options");
    desc.add_options()
            ("command", po::value<std::string>(), "The thing to list (functions)")
            ("file", po::value<std::string>(), "The file to list")
            ("input,i", po::value<std::string>(), "The input database")
            ;

    po::positional_options_description pd;
    pd.add("command", 1).add("file", 1);

    po::variables_map vm;
    po::parsed_options parsed = po::command_line_parser(args).options(desc).positional(pd).run();
    po::store(parsed, vm);
    po::notify(vm);

    if (!vm.count("input")) {
        LOG(ERROR, "Need to give input database");
        exit(1);
    } else if (!vm.count("command")) {
        std::cout << "No listing type given" << std::endl;
        exit(1);
    } else if (!vm.count("file")) {
        std::cout << "No files given" << std::endl;
        exit(1);
    } else if (vm["command"].as<std::string>() != "functions") {
        std::cout << "Unsupported list type" << std::endl;
        exit(1);
    }

    auto storage = db::get_storage(vm["input"].as<std::string>());
    auto f = storage.get_all<db::File>();
    std::vector<db::FunctionDecl> funcs = metrics::functions_in_file(storage, f[0]);
    for (const db::FunctionDecl& fd : funcs) {
        std::cout << fd.function_name << std::endl;
    }
}

} // namespace oonalysis::cli