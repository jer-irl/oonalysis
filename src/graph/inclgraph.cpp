#include "inclgraph.h"

#include <graphviz/cgraph.h>
#include <string>
#include <map>
#include "db/db.h"
#include "db/types.h"

namespace oonalysis::graph {

Agraph_t* get_inclgraph(db::Database &db) {
    Agraph_t* res = agopen((char *) "theGraph", Agdirected, nullptr);

    std::map<std::string, Agnode_t*> nodes;

    for (const db::File& f : db.get_all<db::File>()) {
        // TODO Memory leak for strdup
        nodes[f.path] = agnode(res, strdup(f.path.c_str()), 1);
    }

    for (const db::CppInclusion& incl : db.get_all<db::CppInclusion>()) {
        agedge(res, nodes[incl.includer_path], nodes[incl.includee_path], nullptr, 1);
    }

    return res;
}

} // namespace oonalysis::graph
