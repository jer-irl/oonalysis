#include <string>
#include <vector>
#include <SQLiteCpp.h>
#include "oonalysis.h"
#include "db/io.h"
#include "db/init.h"
#include "cli/parse.h"

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
    std::vector<std::string> args = args_to_vector(argc, argv);
    subcmd_t cmd = determine_cmd(args);
    dispatch_cmd(cmd, args);

    SQLite::Database db(":memory:", SQLite::OPEN_CREATE);
    init_db(db);

    return 0;
}
