#ifndef UTIL_FILES_H
#define UTIL_FILES_H

#include <string>

namespace oonalysis::util {

std::vector<std::string> glob(const std::string& filename);
std::string path_from_partial(const std::string& partial);

} // namespace oonalysis::util

#endif // UTIL_FILES_H
