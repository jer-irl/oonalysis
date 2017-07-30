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
    subcmd_t cmd = determine_cmd(args);
    dispatch_cmd(cmd, args);
    init_db();
#endif


    return 0;
}
