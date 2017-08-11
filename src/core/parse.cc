#include <stdlib.h>
#include "parse.h"
#include "filetype.h"
#include "clang.h"
extern "C" {
#include "util/log.h"
}


namespace oonalysis {
namespace core {

void parse_files(const std::vector<std::string>& files)
{
    LOG(INFO, "Parsing files");
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
}

} // namespace core
} // namespace oonalysis
