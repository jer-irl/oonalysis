#include "list.h"

#include <iostream>
#include <boost/program_options.hpp>
#include "sqlite_orm/sqlite_orm.h"
#include "db/db.h"
#include "db/types.h"
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
    }

    auto storage = db::get_storage(vm["input"].as<std::string>());
    if (vm["command"].as<std::string>() == "functions") {
        auto f = storage.get_all<db::File>();
        std::vector<db::FunctionDecl> funcs = metrics::functions_in_file(storage, f[0]);
        for (const db::FunctionDecl& fd : funcs) {
            std::cout << storage.dump(fd) << std::endl;
        }
    } else if (vm["command"].as<std::string>() == "globals") {
        auto global_vars = storage.get_all<db::VarDecl>(orm::where(orm::is_not_equal(&db::VarDecl::is_global, 0)));
        /*
        for (const db::VarDecl& vd : global_vars) {
            std::cout << storage.dump(vd) << std::endl;
        }
         */
    } else {
        std::cout << "Unrecognized command" << std::endl;
        exit(1);
    }
}

} // namespace oonalysis::cli