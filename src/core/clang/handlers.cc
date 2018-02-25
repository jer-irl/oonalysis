#include <clang-c/Index.h>
#include <string>
#include <sqlite_orm/sqlite_orm.h>
#include "db/db.h"
#include "clang.h"
#include "handlers.h"
extern "C" {
#include "util/log.h"
}

namespace oonalysis::core::clang {

CXChildVisitResult handle_inclusion_directive(CXCursor cur, CXCursor parent, CXClientData client_data) {
    (void) parent;
    CursorData cd = *(CursorData *) client_data;

    LOG(DEBUG, "Handling inclusion directive");

    CXFile includee = clang_getIncludedFile(cur);
    if (!includee) {
        LOG(ERROR, "Couldn't get includee");
        return CXChildVisit_Continue;
    }
    CXString filename = clang_getFileName(includee);
    std::string includee_name = clang_getCString(filename);
    clang_disposeString(filename);

    db::File includee_record;
    try{
        includee_record = cd.db.get<db::File>(includee_name);
    } catch (sqlite_orm::not_found_exception) {
        includee_record.path = includee_name;
        cd.db.replace(includee_record);
    }

    auto tu = clang_Cursor_getTranslationUnit(cur);
    CXString filename2 = clang_getTranslationUnitSpelling(tu);
    std::string includer_name = clang_getCString(filename2);
    clang_disposeString(filename2);

    db::CppInclusion incl{includer_name, includee_name};

    cd.db.replace(incl);

    return CXChildVisit_Continue;
}

CXChildVisitResult handle_function_decl(CXCursor cur, CXCursor parent, CXClientData client_data) {
    (void) parent;

    CXString cxname = clang_getCursorSpelling(cur);
    std::string name = clang_getCString(cxname);
    clang_disposeString(cxname);

    CXType cxtype = clang_getCursorResultType(cur);
    CXString cxtypename = clang_getTypeSpelling(cxtype);
    std::string return_type = clang_getCString(cxtypename);
    clang_disposeString(cxtypename);

    CursorData cd = *(CursorData *) client_data;

    if (clang_isCursorDefinition(cur)) {
        auto fd = db::FunctionDef{-1, name, cd.file.path, return_type};
        cd.db.insert(fd);
    } else {
        auto fd = db::FunctionDecl{-1, name, cd.file.path, return_type};
        cd.db.insert(fd);
    }

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
        std::string file_path = cd.file.path;

        cd.db.insert(db::VarDecl{-1, name, type, is_global, file_path});
        return CXChildVisit_Recurse;
    }

    return CXChildVisit_Recurse;
}

CXChildVisitResult handle_other(CXCursor cur, CXCursor parent, CXClientData client_data) {
    return CXChildVisit_Recurse;
}

} // end namespace oonalysis::core::clang
