#ifndef FILETYPE_H
#define FILETYPE_H

#include <vector>
#include <string>
#include "oonalysis.h"


namespace oonalysis {
namespace core {

Lang lang_from_filenames(std::vector<std::string> filenames);
Lang lang_from_filename(std::string filename);

} // namespace core
} // namespace oonalysis

#endif // FILETYPE_H
