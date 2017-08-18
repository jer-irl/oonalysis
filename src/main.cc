#include <string>
#include <vector>
#include "oonalysis.h"
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
    oonalysis::cli::main_cli(argc, argv);
    return 0;
}
