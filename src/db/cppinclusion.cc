#include <string>
#include <vector>
#include "cppinclusion.h"
#include "repo/repo.h"
#include "repo/types.h"

namespace oonalysis::db {

bool add_new_inclusion(const std::string& includer, const std::string& includee)
{
    if (repo::dbcppinclusion_present(includer, includee)) {
        return false;
    }

    repo::db_cppinclusion to_add;
    to_add.includer = includer;
    to_add.includee = includee;

    repo::add_dbcppinclusion(to_add);
    return true;
}

std::vector<std::string> get_inclusions_in_file(const std::string& filename)
{
    std::vector<std::string> res;

    auto incls = repo::get_dbcppinclusions();
    for (auto incl : incls) {
        if (incl->includer == filename) {
            res.push_back(incl->includee);
        }
    }

    return res;
}

std::vector<std::string> get_inclusions_of_file(const std::string& filename)
{
    std::vector<std::string> res;

    auto incls = repo::get_dbcppinclusions();
    for (auto incl : incls) {
        if (incl->includee == filename) {
            res.push_back(incl->includer);
        }
    }

    return res;
}

} // namespace oonalysis::db
