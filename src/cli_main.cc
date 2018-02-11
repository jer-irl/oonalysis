#include "cli/cli.h"
extern "C" {
#include "util/log.h"
}

int main(int argc, char** argv) {
    LOG(INFO, "Welcome to oonalysis");
    oonalysis::cli::main_cli(argc, argv);
    return 0;
}
