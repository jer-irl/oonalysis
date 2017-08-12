#ifndef CORE_CLANG_CURSOR_DISPATCH_H
#define CORE_CLANG_CURSOR_DISPATCH_H

#include <functional>
#include <clang-c/Index.h>

namespace oonalysis::core::clang {

std::function<void(CXCursor, CXCursor, CXClientData)> dispatch_cursor(CXCursor cur, CXCursor parent, CXClientData client_data);

} // end namespace

#endif // CORE_CLANG_CURSOR_DISPATCH_H
