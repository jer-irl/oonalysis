#ifndef GRAPH_INCLGRAPH_H
#define GRAPH_INCLGRAPH_H

#include <graphviz/cgraph.h>
#include "db/db.h"

namespace oonalysis::graph {

Agraph_t* get_inclgraph(db::Database& db);

} // namespace oonalysis::graph

#endif // GRAPH_CALLGRAPH_H
