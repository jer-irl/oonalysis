#ifndef CORE_CLANG_HANDLERS_H
#define CORE_CLANG_HANDLERS_H

#include <clang-c/Index.h>

namespace oonalysis::core::clang {

CXChildVisitResult handle_inclusion_directive(CXCursor cur, CXCursor parent, CXClientData client_data);
CXChildVisitResult handle_other(CXCursor cur, CXCursor parent, CXClientData client_data);

} // namespace oonalysis::core::clang

#endif // CORE_CLANG_HANDLERS_H
