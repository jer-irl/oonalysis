#include <stdlib.h>
#include "parse.h"
#include "filetype.h"
#include "clang.h"


namespace oonalysis {
namespace core {

void parse_files(const std::vector<std::string>& files)
{
    lang_t project_lang = lang_from_filenames(files);
    for (auto file : files) {
        if (lang_from_filename(file) != project_lang) { continue; }

        switch (project_lang) {
        case C:
        case CPP:
            main_clang(file);
        case HS:
        case PY:
        case UNKNOWN:
        case OTHER:
        case NONE:
        default:
            continue;
        }
    }
    exit(1);
}

} // namespace core
} // namespace oonalysis
