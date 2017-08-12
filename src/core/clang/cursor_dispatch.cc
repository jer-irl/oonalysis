#include <functional>
#include <clang-c/Index.h>
#include "cursor_dispatch.h"

std::function<void(CXCursor, CXCursor, CXClientData)> dispatch_cursor(CXCursor cur, CXCursor parent, CXClientData client_data)
{
}
