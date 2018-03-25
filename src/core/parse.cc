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

static void common_parse(db::Database& db, const std::vector<std::string>& files) {
    for (const auto& file : files) {
        db::File f{file};
        db.replace(f);
    }
}

void parse_file(db::Database& db, const std::string& file, const std::vector<std::string>& args) {
    std::vector<std::string> vec;
    vec.push_back(file);
    parse_files(db, vec, args);
}

void parse_files(db::Database& db, const std::vector<std::string>& files, const std::vector<std::string>& args) {
    LOG(INFO, "Parsing files");

    common_parse(db, files);

    lang_t project_lang = lang_from_filenames(files);
    std::vector<db::File> to_parse;
    switch (project_lang) {
    case C:
    case CPP:
        for (const std::string& filename : files) {
            db::File f = db.get<db::File>(filename);
            if (lang_from_filename(f.path) == C || lang_from_filename(f.path) == CPP) {
                to_parse.push_back(f);
            }
        }
        clang::main_clang(db, to_parse, args);
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
