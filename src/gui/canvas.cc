#include <vector>
#include <memory>
#include "util/project.h"
#include "db/file.h"
#include "db/cppinclusion.h"
#include "graph/field.h"
#include "ctx.h"
#include "guinode.h"
#include "canvas.h"

namespace oonalysis::gui {

std::vector<std::shared_ptr<GuiNode>> make_nodes() {
    // Construct nodes
    std::vector<std::shared_ptr<GuiNode>> nodes;

    std::vector<std::string> impl_files = db::all_project_filenames();
    for (auto fname : impl_files) {
        std::shared_ptr<GuiNode> impl_ptr = std::make_shared<DeclFileNode>();

        std::vector<std::string> included = db::get_inclusions_in_file(fname);
        for (auto incl : included) {
            if (util::is_project_filename(incl)) {
                std::shared_ptr<GuiNode> decl_ptr = std::make_shared<DeclFileNode>();
                std::weak_ptr<graph::Node> ref_ptr = decl_ptr;
                impl_ptr->connections_to.push_back(ref_ptr);

                nodes.push_back(decl_ptr);
            }
        }
        nodes.push_back(impl_ptr);
    }

    return nodes;
}

void Canvas::display() {
    // Make nodes
    std::vector<std::shared_ptr<GuiNode>> nodes = make_nodes();
    std::vector<std::shared_ptr<graph::Node>> as_graph_nodes(nodes.begin(), nodes.end());

    // Make field and relax
    graph::Field field(100, 100, 0, as_graph_nodes);
    field.relax_all(50);

    for (auto node_ptr : nodes) {
        node_ptr->show();
    }
}

} // namespace oonalysis::gui
