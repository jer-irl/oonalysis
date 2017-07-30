#include <string>
#include <vector>
#include <clang-c/Index.h>
#include "db/dbrepo.h"
#include "db/dbtypes.h"

void handle_inclusion_directive(CXCursor cur, CXCursor parent, CXClientData client_data)
{
    CXFile includee = clang_getIncludedFile(cur);
    CXString filename = clang_getFileName(includee);
    std::string includee_name = clang_getCString(filename);

    CXFile includer = clang_getIncludedFile(parent);
    CXString filename2 = clang_getFileName(includer);
    std::string includer_name = clang_getCString(filename2);

    db_cppinclusion inclusion;
    inclusion.id = 0;
    inclusion.includer = includer_name;
    inclusion.includee = includee_name;

    add_dbcppinclusion(inclusion);
}

CXChildVisitResult cursor_visitor(CXCursor cur, CXCursor parent, CXClientData client_data)
{
    if (!clang_Location_isFromMainFile(clang_getCursorLocation(cur))) {
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

void main_clang(std::vector<std::string>& filenames)
{
    CXIndex index = clang_createIndex(1, 1);
    for (std::string filename : filenames) {
        db_file file;
        file.id = 0;
        file.filename = filename;
        add_dbfile(file);

        CXTranslationUnit tu = clang_createTranslationUnit(index, filename.c_str());
        clang_visitChildren(
                clang_getTranslationUnitCursor(tu),
                cursor_visitor,
                0);
    }
}
