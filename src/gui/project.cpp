//
// Created by Jeremy Schroeder on 2/1/18.
//

#include <boost/filesystem.hpp>
#include "project.h"

namespace fs = boost::filesystem;
namespace oonalysis::gui {

Project::Project(fs::path p) {
    p;
    if (fs::exists(p) && fs::is_regular_file(p)) {
        path = p;
        read_in();
    } else if (fs::exists(p) && fs::is_directory(p)) {
        path = p / "project.oonalysis";
        root = p;
    } else {
        path = p;
        root = p.parent_path();
    }
}

} // namespace oonalysis::gui
