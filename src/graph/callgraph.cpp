#include "callgraph.h"

#include <unordered_map>

namespace orm = sqlite_orm;

namespace oonalysis::graph {

Agraph_t* get_callgraph(db::Database& db, const std::unordered_set<std::string> files) {

    Agraph_t* res = agopen((char *) "theGraph", Agdirected, nullptr);

    std::unordered_map<std::string, Agnode_t*> nodes;


    // SELECT call.called_function_name, call.parent_function_name, called.file_path, parent.file_path
    // FROM func_calls AS call
    // INNER JOIN func_defs AS called ON call.called_function_name = called.function_name
    // INNER JOIN func_defs AS parent ON call.parent_function_name = parent.function_name;
    using called = orm::alias_b<db::FunctionDef>;
    using parent = orm::alias_c<db::FunctionDef>;

    auto rows = db.select(
            orm::columns(
                    &db::FunctionCall::called_function_name,
                    &db::FunctionCall::parent_function_name,
                    orm::alias_column<called>(&db::FunctionDef::file_path),
                    orm::alias_column<parent>(&db::FunctionDef::file_path)
            ),
            orm::inner_join<called>(orm::on(orm::c(&db::FunctionCall::called_function_name) == orm::alias_column<called>(&db::FunctionDef::function_name))),
            orm::inner_join<parent>(orm::on(orm::c(&db::FunctionCall::parent_function_name) == orm::alias_column<parent>(&db::FunctionDef::function_name)))
    );

    /*
    auto rows = db.select(
            orm::columns(
                    &db::FunctionCall::called_function_name,
                    &db::FunctionCall::parent_function_name,
                    orm::alias_column<called>(&db::FunctionDef::file_path),
                    orm::alias_column<parent>(&db::FunctionDef::file_path)
            ),
            orm::where(
                    orm::is_equal(orm::c(&db::FunctionCall::called_function_name), orm::alias_column<called>(&db::FunctionDef::function_name))
                    and
                    orm::is_equal(orm::c(&db::FunctionCall::parent_function_name), orm::alias_column<parent>(&db::FunctionDef::function_name))
            )
    );
     */

    for (auto row : rows) {
        if (!files.count(std::get<2>(row)) || !files.count(std::get<3>(row))) {
            continue;
        }

        std::string called_key = std::get<2>(row) + ":" + std::get<0>(row);
        std::string parent_key = std::get<3>(row) + ":" + std::get<1>(row);

        // Make nodes
        if (!nodes[called_key]) {
            nodes[called_key] = agnode(res, strdup(called_key.c_str()), 1);
        }
        if (!nodes[parent_key]) {
            nodes[parent_key] = agnode(res, strdup(parent_key.c_str()), 1);
        }

        // Make edge
        agedge(res, nodes[called_key], nodes[parent_key], nullptr, 1);
    }

    return res;

}

} // namespace oonalysis::graph