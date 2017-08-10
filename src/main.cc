#include <string>
#include <vector>
#include <SQLiteCpp.h>
#include "oonalysis.h"
#include "db/init.h"
#include "cli/parse.h"
extern "C" {
#include "util/log.h"
}


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
    LOG(INFO, "Welcome to oonalysis");

    std::vector<std::string> args = args_to_vector(argc, argv);
    oonalysis::cli::subcmd_t cmd = oonalysis::cli::determine_cmd(args);
    dispatch_cmd(cmd, args);

    return 0;
}
