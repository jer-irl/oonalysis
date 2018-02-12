#include <cstdlib>
#include "parse.h"
#include "filetype.h"
#include "metrics/loc.h"
#include "clang/clang.h"
#include "db/types.h"
extern "C" {
#include "util/log.h"
}


namespace oonalysis::core {

void common_parse(db::Database& db, const std::vector<std::string>& files) {
    for (const auto& file : files) {
        db::File f{-1, file};
        db.insert(f);
    }
}

void parse_files(db::Database& db, const std::vector<std::string>& files) {
    LOG(INFO, "Parsing files");

    common_parse(db, files);

    lang_t project_lang = lang_from_filenames(files);
    std::vector<db::File> to_parse;
    switch (project_lang) {
    case C:
    case CPP:
        for (const db::File& f : db.iterate<db::File>()) {
            if (lang_from_filename(f.path) == C || lang_from_filename(f.path) == CPP) {
                to_parse.push_back(f);
            }
        }
        clang::main_clang(db, to_parse);
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
