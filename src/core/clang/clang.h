#ifndef CORE_CLANG_H
#define CORE_CLANG_H

#include <string>
#include <clang-c/Index.h>


namespace oonalysis::core::clang {

void main_clang(const std::vector<std::string>& filename);

} // namespace oonalysis::core::clang

#endif // CORE_CLANG_H
