#include <string>
#include <sstream>
#include <catch.hpp>
#include "loc.h"

TEST_CASE("lines of code are read from stream") {
    std::string str1 =
        "Line 1\n"
        "\n"
        " \n"
        "Line 4";
    std::istringstream in1(str1);
    REQUIRE(oonalysis::core::common::loc_in_stream(in1) == 4);

    std::string str2 =
        "asdgasdg\n"
        "\n";
    std::istringstream in2(str2);
    REQUIRE(oonalysis::core::common::loc_in_stream(in2) == 2);

    std::string str3 = "";
    std::istringstream in3(str3);
    REQUIRE(oonalysis::core::common::loc_in_stream(in3) == 0);
}
