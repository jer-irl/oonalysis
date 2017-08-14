#include <stdlib.h>
#include "parse.h"
#include "filetype.h"
#include "metrics/loc.h"
#include "clang/clang.h"
#include "db/dbtypes.h"
#include "db/dbrepo.h"
extern "C" {
#include "util/log.h"
}


namespace oonalysis::core {

void universal_parse(const std::vector<std::string>& files)
{
    for (auto file : files) {
        db::db_file dbfile;
        dbfile.filename = file;

        int loc = metrics::loc_in_file(file);
        dbfile.loc = loc;

        db::add_dbfile(dbfile);
    }
}

void parse_files(const std::vector<std::string>& files)
{
    LOG(INFO, "Parsing files");

    universal_parse(files);

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
