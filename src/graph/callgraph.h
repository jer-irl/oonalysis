#ifndef GRAPH_CALLGRAPH_H
#define GRAPH_CALLGRAPH_H

#include <graphviz/cgraph.h>
#include "db/db.h"

namespace oonalysis::graph {

Agraph_t* get_callgraph(db::Database& db);

} // namespace oonalysis::graph

#endif // GRAPH_CALLGRAPH_H