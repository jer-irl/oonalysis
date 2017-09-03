#include <vector>
#include "util/project.h"
#include "db/file.h"
#include "db/cppinclusion.h"
#include "graph/field.h"
#include "graph/node.h"
#include "ctx.h"
#include "canvas.h"

namespace oonalysis::gui {

void Canvas::display() {
    Ctx* ctx = Ctx::inst();

    std::vector<std::string> impl_files = db::all_project_filenames();
    std::vector<std::string> decl_files;

    // Get impl files
    for (auto fname : impl_files) {
        std::vector<std::string> included = db::get_inclusions_in_file(fname);
        for (auto incl : included) {
            if (util::is_project_filename(incl)) {
                decl_files.push_back(incl);
            }
        }
    }

    // Make nodes
    std::vector<graph::Node> nodes;

    // Make edges

    // Make field and relax
}

} // namespace oonalysis::gui
