#include "inclgraph.h"

namespace oonalysis::graph {

Agraph_t* get_inclgraph(db::Database &db, const std::unordered_set<std::string>& files) {
    Agraph_t* res = agopen((char *) "theGraph", Agdirected, nullptr);

    std::map<std::string, Agnode_t*> nodes;

    for (const db::File& f : db.get_all<db::File>()) {
        if (files.count(f.path) == 0) {
            continue;
        }

        // TODO Memory leak for strdup
        nodes[f.path] = agnode(res, strdup(f.path.c_str()), 1);
    }

    for (const db::CppInclusion& incl : db.get_all<db::CppInclusion>()) {
        if (nodes[incl.includee_path] && nodes[incl.includer_path]) {
            agedge(res, nodes[incl.includee_path], nodes[incl.includer_path], nullptr, 1);
        }
    }

    return res;
}

} // namespace oonalysis::graph
