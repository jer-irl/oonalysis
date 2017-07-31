#include <string>
#include <vector>
#include <SQLiteCpp.h>
#include "oonalysis.h"
#include "db/init.h"

#ifdef WITH_CLI
#include "cli/parse.h"
#endif


std::vector<std::string> args_to_vector(int argc, char** argv)
{
    auto res = std::vector<std::string>();
    for (int i = 0; i < argc; i++) {
        res.push_back(std::string(argv[i]));
    }
    return res;
}

int main(int argc, char** argv)
{
#ifdef WITH_CLI
    std::vector<std::string> args = args_to_vector(argc, argv);
    oonalysis::cli::subcmd_t cmd = oonalysis::cli::determine_cmd(args);
    dispatch_cmd(cmd, args);
    oonalysis::db::init_db();
#endif


    return 0;
}
