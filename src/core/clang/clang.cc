#include "clang.h"

#include <iostream>
#include <cstdlib>
#include <functional>
#include <tuple>
#include "cursor_dispatch.h"

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

static std::vector<std::tuple<db::File, CXTranslationUnit>>
make_translation_units(CXIndex* index, const std::vector<db::File>& files, const std::vector<std::string>& compilation_arguments) {
    std::vector<std::tuple<db::File, CXTranslationUnit>> res;

    const char* args[compilation_arguments.size()];
    for (int i = 0; i < compilation_arguments.size(); i++) {
        args[i] = compilation_arguments[i].c_str();
    }

    for (const auto& file : files) {
        CXTranslationUnit tu;
        auto err = clang_parseTranslationUnit2(
                *index,
                file.path.c_str(),
                args,
                (int) compilation_arguments.size(),
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

void main_clang(db::Database& db, const std::vector<db::File>& files, const std::vector<std::string>& args) {
    CXIndex index = clang_createIndex(0, 1);
    std::vector<std::tuple<db::File, CXTranslationUnit>> tus =  make_translation_units(&index, files, args);

    for (auto tu : tus) {
        parse_translation_unit(db, std::get<0>(tu), std::get<1>(tu));
    }
}


} // namespace oonalysis::core::clang
