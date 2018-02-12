#include "clang.h"

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <clang-c/Index.h>
#include <functional>
#include <tuple>
#include "cursor_dispatch.h"
#include "db/db.h"
#include "db/types.h"


namespace oonalysis::core::clang {

static CXChildVisitResult cursor_visitor(CXCursor cur, CXCursor parent, CXClientData client_data) {
    auto handler = dispatch_cursor(cur);
    return handler(cur, parent, client_data);
}

static void parse_translation_unit(db::Database& db, db::File file, CXTranslationUnit tu) {
    clang_visitChildren(
            clang_getTranslationUnitCursor(tu),
            cursor_visitor,
            new CursorData{db, file});
}

static std::vector<std::tuple<db::File, CXTranslationUnit>> make_translation_units(CXIndex* index, const std::vector<db::File>& files) {
    std::vector<std::tuple<db::File, CXTranslationUnit>> res;

    for (const auto& file : files) {
        CXTranslationUnit tu;
        auto err = clang_parseTranslationUnit2(
                *index,
                file.path.c_str(),
                nullptr,
                0,
                nullptr,
                0,
                CXTranslationUnit_DetailedPreprocessingRecord,
                &tu);

        if (err != CXError_Success) {
            std::cout << "Error in creating translation unit" << std::endl;
            exit(1);
        }
        res.push_back(std::make_tuple(file, tu));
    }
    return res;
}

void main_clang(db::Database& db, const std::vector<db::File>& files) {
    CXIndex index = clang_createIndex(1, 1);
    std::vector<std::tuple<db::File, CXTranslationUnit>> tus =  make_translation_units(&index, files);

    for (auto tu : tus) {
        parse_translation_unit(db, std::get<0>(tu), std::get<1>(tu));
    }
}


} // namespace oonalysis::core::clang
