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

void parse_translation_unit(CXTranslationUnit tu)
{
    LOG(INFO, "Parsing clang file");

    // Get file and add to db
    CXString cxname = clang_getTranslationUnitSpelling(tu);
    db::db_file file;
    file.id = 0;
    file.filename = clang_getCString(cxname);
    add_dbfile(file);
    clang_disposeString(cxname);

    clang_visitChildren(
            clang_getTranslationUnitCursor(tu),
            cursor_visitor,
            0);
}

std::vector<CXTranslationUnit> make_translation_units(CXIndex* index, const std::vector<std::string>& files)
{
    std::vector<CXTranslationUnit> res;

    for (auto file : files) {
        CXTranslationUnit tu;
        auto err = clang_parseTranslationUnit2(
                *index,
                file.c_str(),
                nullptr,
                0,
                nullptr,
                0,
                CXTranslationUnit_None,
                &tu);

        if (err != CXError_Success) {
            LOG(ERROR, "Error in creating translation unit");
            exit(1);
        }
        res.push_back(tu);
    }
    return res;
}

void main_clang(const std::vector<std::string>& files)
{
    LOG(INFO, "Entering clang main");
    CXIndex index = clang_createIndex(1, 1);
    std::vector<CXTranslationUnit> tus =  make_translation_units(&index, files);

    for (auto tu : tus) {
        parse_translation_unit(tu);
    }
}


} // namespace clang
} // namespace core
} // namespace oonalysis
