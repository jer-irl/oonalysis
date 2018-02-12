#ifndef CORE_CLANG_H
#define CORE_CLANG_H

#include <string>
#include <clang-c/Index.h>
#include <vector>
#include "db/db.h"
#include "db/types.h"


namespace oonalysis::core::clang {

struct CursorData {
    db::Database& db;
    db::File& file;
};

void main_clang(db::Database&, const std::vector<db::File>& files);

} // namespace oonalysis::core::clang

#endif // CORE_CLANG_H
