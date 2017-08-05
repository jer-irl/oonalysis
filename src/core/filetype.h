#ifndef FILETYPE_H
#define FILETYPE_H

#include <vector>
#include <string>
#include "oonalysis.h"


namespace oonalysis {
namespace core {

lang_t lang_from_filenames(const std::vector<std::string>& filenames);
lang_t lang_from_filename(const std::string& filename);

} // namespace core
} // namespace oonalysis

#endif // FILETYPE_H
