#include <clang-c/Index.h>
#include <string>
#include <sqlite_orm/sqlite_orm.h>
#include <iostream>
#include "db/db.h"
#include "clang.h"
#include "handlers.h"
#include "util.hpp"
extern "C" {
#include "util/log.h"
}

namespace oonalysis::core::clang {

CXChildVisitResult handle_inclusion_directive(CXCursor cur, CXCursor parent, CXClientData client_data) {
    (void) parent;

    if (clang_Location_isInSystemHeader(clang_getCursorLocation(cur))) {
        return CXChildVisit_Continue;
    }

    CursorData cd = *(CursorData *) client_data;

    LOG(DEBUG, "Handling inclusion directive");

    CXString spelling = clang_getCursorSpelling(cur);
    std::string str_spelling = clang_getCString(spelling);
    CXFile includee = clang_getIncludedFile(cur);
    if (!includee) {
        LOG(ERROR, "Couldn't get includee");
        log_cursor(cur, client_data);
        return CXChildVisit_Continue;
    }
    CXString filename = clang_getFileName(includee);
    std::string includee_name = clang_getCString(filename);
    clang_disposeString(filename);

    db::File includee_record;
    try{
        includee_record = cd.db.get<db::File>(includee_name);
    } catch (std::system_error&) {
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
        auto fd = db::FunctionDef{name, cd.file.path, return_type};
        cd.db.replace(fd);
    } else {
        auto fd = db::FunctionDecl{name, cd.file.path, return_type};
        cd.db.replace(fd);
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

CXChildVisitResult handle_function_call(CXCursor cur, CXCursor parent, CXClientData client_data) {
    CursorData cd = *(CursorData *) client_data;
    CXSourceLocation loc = clang_getCursorLocation(cur);

    unsigned int line_num;
    clang_getFileLocation(loc, nullptr, &line_num, nullptr, nullptr);

    db::FunctionDef enclosing_func;
    try {
        enclosing_func = get_enclosing_function(cur, client_data);
    } catch (std::runtime_error& ex) {
        // Weird case
        std::cout << "No enclosing function (?)" << std::endl;
        log_cursor(cur, client_data);
        return CXChildVisit_Continue;
    } catch (std::system_error& ex) {
        std::cout << "Parent not in database, function call not input" << std::endl;
        return CXChildVisit_Continue;
    }

    CXString called_name = clang_getCursorSpelling(cur);
    std::string called_str = clang_getCString(called_name);
    clang_disposeString(called_name);

    db::FunctionDef called_func;
    try {
        called_func = cd.db.get<db::FunctionDef>(called_str);
    } catch (std::system_error& ex) {
        called_func.function_name = called_str;
    }

    db::FunctionCall res = { line_num, called_func.function_name, enclosing_func.function_name };
    cd.db.replace(res);

    return CXChildVisit_Continue;
}

CXChildVisitResult handle_other(CXCursor cur, CXCursor parent, CXClientData client_data) {
    return CXChildVisit_Recurse;
}

} // end namespace oonalysis::core::clang
