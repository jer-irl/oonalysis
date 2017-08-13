#include <stdlib.h>
#include "parse.h"
#include "filetype.h"
#include "clang/clang.h"
extern "C" {
#include "util/log.h"
}


namespace oonalysis::core {

void parse_files(const std::vector<std::string>& files)
{
    LOG(INFO, "Parsing files");
    lang_t project_lang = lang_from_filenames(files);

    switch (project_lang) {
    case C:
    case CPP:
        clang::main_clang(files);
        break;
    case HS:
    case PY:
    case UNKNOWN:
    case OTHER:
    case NONE:
    default:
        LOG(ERROR, "Unsupported project type");
        exit(1);
    }

    LOG(INFO, "Done parsing");
}

} // namespace oonalysis::core
