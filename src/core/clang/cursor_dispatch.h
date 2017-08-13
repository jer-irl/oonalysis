#ifndef CORE_CLANG_CURSOR_DISPATCH_H
#define CORE_CLANG_CURSOR_DISPATCH_H

#include <functional>
#include <clang-c/Index.h>

namespace oonalysis::core::clang {

std::function<CXChildVisitResult(CXCursor, CXCursor, CXClientData)> dispatch_cursor(CXCursor cur);

} // end namespace

#endif // CORE_CLANG_CURSOR_DISPATCH_H
