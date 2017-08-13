#include <clang-c/Index.h>
#include "handlers.h"
#include "db/dbrepo.h"
extern "C" {
#include "util/log.h"
}

namespace oonalysis::core::clang {

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wall"

CXChildVisitResult handle_inclusion_directive(CXCursor cur, CXCursor parent, CXClientData client_data)
{
    LOG(DEBUG, "Handling inclusion directive");

    CXFile includee = clang_getIncludedFile(cur);
    CXString filename = clang_getFileName(includee);
    std::string includee_name = clang_getCString(filename);

    CXFile includer = clang_getIncludedFile(parent);
    CXString filename2 = clang_getFileName(includer);
    std::string includer_name = clang_getCString(filename2);

    db::db_cppinclusion inclusion;
    inclusion.id = 0;
    inclusion.includer = includer_name;
    inclusion.includee = includee_name;

    add_dbcppinclusion(inclusion);
    return CXChildVisit_Continue;
}

CXChildVisitResult handle_other(CXCursor cur, CXCursor parent, CXClientData client_data)
{
    return CXChildVisit_Recurse;
}

#pragma clang diagnostic pop

} // end namespace oonalysis::core::clang
