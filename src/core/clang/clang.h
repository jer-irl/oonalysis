#ifndef CORE_CLANG_H
#define CORE_CLANG_H

#include <string>
#include <clang-c/Index.h>


namespace oonalysis {
namespace core {
namespace clang {

void main_clang(const std::vector<std::string>& filename);

} // namespace clang
} // namespace core
} // namespace oonalysis

#endif // CORE_CLANG_H
