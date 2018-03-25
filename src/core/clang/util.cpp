#include "util.hpp"

#include <iostream>
#include "clang.h"

namespace oonalysis::core::clang {

db::FunctionDef get_enclosing_function(CXCursor cur, CXClientData client_data) {
    CursorData cd = *(CursorData *) client_data;

    std::string parent_name = enclosing_function_name(cur, client_data);
    if (parent_name == "[none]") {
        throw std::runtime_error("No enclosing parent");
    }
    return cd.db.get<db::FunctionDef>(parent_name);
}

std::string enclosing_function_name(CXCursor cur, CXClientData client_data) {
    CXCursor parent = enclosing_function_cursor(cur, client_data);

    if (clang_Cursor_isNull(parent)) {
        return "[none]";
    } else {
        CXString parent_name = clang_getCursorSpelling(parent);
        std::string parent_str = clang_getCString(parent_name);
        clang_disposeString(parent_name);

        return parent_str;
    }
}

void log_cursor(CXCursor cur, CXClientData client_data) {
    using std::cout;
    using std::endl;

    cout << "Logging cursor:" << endl;
    cout << "\t" << "Cursor spelling: " << clang_getCString(clang_getCursorSpelling(cur)) << endl;
    cout << "\t" << "Cursor kind: " << clang_getCString(clang_getCursorKindSpelling(clang_getCursorKind(cur))) << endl;
    cout << "\t" << "Cursor file: " << get_enclosing_filename(cur, client_data) << endl;
    cout << "\t" << "Line number: " << line_number(cur, client_data) << endl;
    cout << "\t" << "Column number: " << column_number(cur, client_data) << endl;
    cout << "\t" << "Cursor enclosing function: " << enclosing_function_name(cur, client_data) << endl;
    cout << "\t" << "Enclosing namespace: " << qualified_namespace(cur, client_data) << endl;
}

unsigned int column_number(CXCursor cur, CXClientData client_data) {
    (void) client_data;

    CXSourceLocation loc = clang_getCursorLocation(cur);
    unsigned int res;
    clang_getSpellingLocation(loc, nullptr, nullptr, &res, nullptr);
    return res;
}

unsigned int line_number(CXCursor cur, CXClientData client_data) {
    (void) client_data;

    CXSourceLocation loc = clang_getCursorLocation(cur);
    unsigned int res;
    clang_getSpellingLocation(loc, nullptr, &res, nullptr, nullptr);
    return res;
}

CXCursor enclosing_function_cursor(CXCursor cur, CXClientData client_data) {
    CXCursor parent = clang_getCursorLexicalParent(cur);
    while (!cursor_is_toplevel(parent, client_data)) {
        if (clang_getCursorKind(parent) == CXCursor_FunctionDecl && clang_isCursorDefinition(parent)) {
            return parent;
        }
        parent = clang_getCursorLexicalParent(parent);
    }
    return clang_getNullCursor();
}

CXCursor enclosing_namespace_cursor(CXCursor cur, CXClientData client_data) {
    CXCursor parent = clang_getCursorLexicalParent(cur);
    while (!cursor_is_toplevel(parent, client_data)) {
        if (clang_getCursorKind(parent) == CXCursor_Namespace) {
            return parent;
        }
        parent = clang_getCursorLexicalParent(parent);
    }
    return clang_getNullCursor();
}

std::string qualified_namespace(CXCursor cur, CXClientData client_data) {
    std::string res;
    CXCursor namespace_cur = cur;
    while (!clang_Cursor_isNull(namespace_cur = enclosing_namespace_cursor(namespace_cur, client_data))) {
        res = std::string(clang_getCString(clang_getCursorSpelling(namespace_cur))) + "::" + res;
    }
    res = "::" + res;
    return res;
}

std::string get_enclosing_filename(CXCursor cur, CXClientData client_data) {
    (void) client_data;
    CXFile file;
    CXSourceLocation loc = clang_getCursorLocation(cur);
    clang_getFileLocation(loc, &file, nullptr, nullptr, nullptr);

    return clang_getCString(clang_getFileName(file));
}

bool cursor_is_toplevel(CXCursor cur, CXClientData client_data) {
    (void) client_data;
    if (clang_Cursor_isNull(cur)) {
        return true;
    }

    CXCursorKind kind = clang_getCursorKind(cur);

    switch (kind) {
        case CXCursor_TranslationUnit:
        case CXCursor_FirstInvalid:
            return true;
        default:
            return false;
    }
}

} // namespace oonalysis::core::clang