#ifndef GRAPH_INCLGRAPH_H
#define GRAPH_INCLGRAPH_H

#include <graphviz/cgraph.h>
#include <unordered_set>
#include <string>
#include "db/db.h"

namespace oonalysis::graph {

Agraph_t* get_inclgraph(db::Database& db, const std::unordered_set<std::string>& files);

} // namespace oonalysis::graph

#endif // GRAPH_CALLGRAPH_H
