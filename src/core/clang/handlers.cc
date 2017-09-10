#include <clang-c/Index.h>
#include "handlers.h"
#include "db/cppinclusion.h"
extern "C" {
#include "util/log.h"
}

namespace oonalysis::core::clang {

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wall"

CXChildVisitResult handle_inclusion_directive(CXCursor cur, CXCursor parent, CXClientData client_data) {
    LOG(DEBUG, "Handling inclusion directive");

    CXFile includee = clang_getIncludedFile(cur);
    if (!includee) {
        LOG(ERROR, "Couldn't get includee");
        return CXChildVisit_Continue;
    }
    CXString filename = clang_getFileName(includee);
    std::string includee_name = clang_getCString(filename);

    auto tu = clang_Cursor_getTranslationUnit(cur);
    CXString filename2 = clang_getTranslationUnitSpelling(tu);
    std::string includer_name = clang_getCString(filename2);

    db::add_new_inclusion(includer_name, includee_name);

    return CXChildVisit_Continue;
}

CXChildVisitResult handle_function_decl(CXCursor cur, CXCursor parent, CXClientData client_data) {
    return CXChildVisit_Recurse;
}

CXChildVisitResult handle_other(CXCursor cur, CXCursor parent, CXClientData client_data) {
    return CXChildVisit_Recurse;
}

#pragma clang diagnostic pop

} // end namespace oonalysis::core::clang
