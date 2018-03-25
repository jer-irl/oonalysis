#ifndef CORE_CLANG_UTIL_H
#define CORE_CLANG_UTIL_H

#include <clang-c/Index.h>
#include <string>
#include "db/types.h"

namespace oonalysis::core::clang {

void log_cursor(CXCursor cur, CXClientData client_data);
db::FunctionDef get_enclosing_function(CXCursor cur, CXClientData client_data);
std::string enclosing_function_name(CXCursor cur, CXClientData client_data);
CXCursor enclosing_function_cursor(CXCursor cur, CXClientData client_data);
CXCursor enclosing_namespace_cursor(CXCursor cur, CXClientData client_data);
std::string qualified_namespace(CXCursor cur, CXClientData client_data);
unsigned int line_number(CXCursor cur, CXClientData client_data);
unsigned int column_number(CXCursor cur, CXClientData client_data);
std::string get_enclosing_filename(CXCursor cur, CXClientData client_data);

} // namespace oonalysis::core::clang

#endif // CORE_CLANG_UTIL_H