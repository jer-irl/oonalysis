#include <string>
#include <vector>
#include <clang-c/Index.h>
#include "db/dbrepo.h"
#include "db/dbtypes.h"
extern "C" {
#include "util/log.h"
}


namespace oonalysis {
namespace core {

void handle_inclusion_directive(CXCursor cur, CXCursor parent, CXClientData client_data)
{
    LOG(DEBUG, "Handling inclusion directive");

    CXFile includee = clang_getIncludedFile(cur);
    CXString filename = clang_getFileName(includee);
    std::string includee_name = clang_getCString(filename);

    CXFile includer = clang_getIncludedFile(parent);
    CXString filename2 = clang_getFileName(includer);
    std::string includer_name = clang_getCString(filename2);

    db::db_cppinclusion inclusion;
    inclusion.id = 0;
    inclusion.includer = includer_name;
    inclusion.includee = includee_name;

    add_dbcppinclusion(inclusion);
}

CXChildVisitResult cursor_visitor(CXCursor cur, CXCursor parent, CXClientData client_data)
{
    LOG(TRACE, "Cursor visiting");

    if (!clang_Location_isFromMainFile(clang_getCursorLocation(cur))) {
        LOG(TRACE, "Breaking as we're traversing non-main file");
        return CXChildVisit_Break;
    }

    switch (parent.kind) {
    default:
        break;
    }

    switch (cur.kind) {
    case CXCursor_InclusionDirective:
        handle_inclusion_directive(cur, parent, client_data);
        return CXChildVisit_Continue;
        break;
    case CXCursor_PreprocessingDirective:
    default:
        return CXChildVisit_Break;
    }
}

void main_clang(const std::string& filename)
{
    LOG(INFO, "Entering clang main");
    CXIndex index = clang_createIndex(1, 1);
    db::db_file file;
    file.id = 0;
    file.filename = filename;
    add_dbfile(file);

    CXTranslationUnit tu = clang_createTranslationUnit(index, filename.c_str());
    clang_visitChildren(
            clang_getTranslationUnitCursor(tu),
            cursor_visitor,
            0);
}


} // namespace core
} // namespace oonalysis
