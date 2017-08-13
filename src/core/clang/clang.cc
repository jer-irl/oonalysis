#include <string>
#include <vector>
#include <clang-c/Index.h>
#include <functional>
#include "cursor_dispatch.h"
#include "db/dbrepo.h"
#include "db/dbtypes.h"
extern "C" {
#include "util/log.h"
}


namespace oonalysis {
namespace core {
namespace clang {


CXChildVisitResult cursor_visitor(CXCursor cur, CXCursor parent, CXClientData client_data)
{
    LOG(TRACE, "Cursor visiting");

    if (!clang_Location_isFromMainFile(clang_getCursorLocation(cur))) {
        LOG(TRACE, "Breaking as we're traversing non-main file");
        return CXChildVisit_Break;
    }

    auto handler = dispatch_cursor(cur);
    return handler(cur, parent, client_data);
}


void parse_file(const std::string& filename, CXTranslationUnit* tu)
{
    LOG(INFO, "Parsing clang file: %s", filename.c_str());

    db::db_file file;
    file.id = 0;
    file.filename = filename;
    add_dbfile(file);

    clang_visitChildren(
            clang_getTranslationUnitCursor(*tu),
            cursor_visitor,
            0);
}

void parse_translation_unit(CXTranslationUnit* tu)
{
}

void make_translation_units(CXIndex* index, const std::vector<std::string>& files)
{
}

void main_clang(const std::vector<std::string>& files)
{
    LOG(INFO, "Entering clang main");
    //CXIndex index = clang_createIndex(1, 1);

    //CXTranslationUnit tu = clang_createTranslationUnit(index, filename.c_str());
}


} // namespace clang
} // namespace core
} // namespace oonalysis
