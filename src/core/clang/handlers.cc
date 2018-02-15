#include <clang-c/Index.h>
#include <string>
#include "db/db.h"
#include "clang.h"
#include "handlers.h"
extern "C" {
#include "util/log.h"
}

namespace oonalysis::core::clang {

CXChildVisitResult handle_inclusion_directive(CXCursor cur, CXCursor parent, CXClientData client_data) {
    (void) parent;
    (void) client_data;

    LOG(DEBUG, "Handling inclusion directive");

    CXFile includee = clang_getIncludedFile(cur);
    if (!includee) {
        LOG(ERROR, "Couldn't get includee");
        return CXChildVisit_Continue;
    }
    CXString filename = clang_getFileName(includee);
    std::string includee_name = clang_getCString(filename);
    clang_disposeString(filename);

    auto tu = clang_Cursor_getTranslationUnit(cur);
    CXString filename2 = clang_getTranslationUnitSpelling(tu);
    std::string includer_name = clang_getCString(filename2);
    clang_disposeString(filename2);

    // TODO
    // db::add_new_inclusion(includer_name, includee_name);

    return CXChildVisit_Continue;
}

CXChildVisitResult handle_function_decl(CXCursor cur, CXCursor parent, CXClientData client_data) {
    (void) parent;

    CXSourceLocation loc = clang_getCursorLocation(cur);
    if (!clang_Location_isFromMainFile(loc)) {
        return CXChildVisit_Recurse;
    }

    CXString cxname = clang_getCursorSpelling(cur);
    std::string name = clang_getCString(cxname);
    clang_disposeString(cxname);

    CXType cxtype = clang_getCursorResultType(cur);
    CXString cxtypename = clang_getTypeSpelling(cxtype);
    std::string return_type = clang_getCString(cxtypename);
    clang_disposeString(cxtypename);


    CursorData cd = *(CursorData *) client_data;

    auto fd = db::FunctionDecl{-1, name, cd.file.id, return_type};
    cd.db.insert(fd);

    return CXChildVisit_Recurse;
}

CXChildVisitResult handle_var_decl(CXCursor cur, CXCursor parent, CXClientData client_data) {
    CursorData cd = *(CursorData *) client_data;
    CXSourceLocation loc = clang_getCursorLocation(cur);

    if (!clang_Location_isFromMainFile(loc)) {
        return CXChildVisit_Recurse;
    }

    // Top level variable declaration
    if (clang_isTranslationUnit(clang_getCursorKind(parent))) {
        CXString cxname = clang_getCursorSpelling(cur);
        std::string name = clang_getCString(cxname);
        clang_disposeString(cxname);

        CXString cxtype = clang_getTypeSpelling(clang_getCursorType(cur));
        std::string type = clang_getCString(cxtype);
        clang_disposeString(cxtype);

        int is_global = 1;
        int file_id = cd.file.id;

        cd.db.insert(db::VarDecl{-1, name, type, is_global, file_id});
        return CXChildVisit_Recurse;
    }

    return CXChildVisit_Recurse;
}

CXChildVisitResult handle_other(CXCursor cur, CXCursor parent, CXClientData client_data) {
    return CXChildVisit_Recurse;
}

} // end namespace oonalysis::core::clang
