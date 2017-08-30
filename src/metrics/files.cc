#include <iostream>
#include <SQLiteCpp.h>
#include "files.h"
#include "db/file.h"

namespace oonalysis::metrics {

uint32_t num_files() {
    return db::get_num_files();
}

void main_files() {
    std::cout << "Printing file statistics:" << std::endl;
    std::cout << "Number of files: " << num_files() << std::endl;
}

} // namespace oonalysis::metrics
