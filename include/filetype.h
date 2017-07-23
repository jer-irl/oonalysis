#ifndef FILETYPE_H
#define FILETYPE_H

#include <vector>
#include <string>
#include "oonalysis.h"


namespace oonalysis {

Lang lang_from_filenames(std::vector<std::string> filenames);
Lang lang_from_filename(std::string filename);

} // namespace oonalysis

#endif // FILETYPE_H
