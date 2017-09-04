#include "project.h"

namespace oonalysis::util {

bool is_project_filename(std::string filename) {
    return filename[0] != '/';
}

} // namespace oonalysis::util
