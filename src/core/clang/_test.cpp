#include <catch.hpp>
#include <iostream>
#include "clang.h"
#include "db/db.h"
#include "db/types.h"

TEST_CASE("C Hello World read correctly") {
    oonalysis::db::Database db = oonalysis::db::get_storage("");
    std::vector<oonalysis::db::File> files;
    oonalysis::db::File file;
    file.path = "test/helloworld.c";
    files.push_back(file);
    std::vector<std::string> args;
    oonalysis::core::clang::main_clang(db, files, args);

    SECTION("functions parsed correctly") {
        auto calls = db.get_all<oonalysis::db::FunctionCall>();
        REQUIRE(calls.size() == 1);
    }

}