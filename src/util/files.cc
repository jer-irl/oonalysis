#include <string>
#include <vector>
#include <boost/filesystem.hpp>
extern "C" {
#include "log.h"
}
#include "files.h"

namespace fs = boost::filesystem;

namespace oonalysis::util {

std::string path_from_partial(const std::string& partial){
    fs::path p = fs::absolute(partial, fs::current_path());
    return p.string();
}

std::vector<std::string> glob(const std::string& filename) {
    LOG(TRACE, "Globbing filenames");
    std::vector<std::string> res;
    fs::path p = filename;

    if (!fs::is_directory(p)) {
        res.push_back(p.native());
        return res;
    }

    for (const auto& iter : fs::recursive_directory_iterator(p)) {
        if (fs::is_regular_file(iter)) {
            res.push_back(iter.path().native());
        }
    }

    return res;
}


} // namespace oonalysis::util
