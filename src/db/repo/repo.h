#ifndef REPO_H
#define REPO_H

#include <memory>
#include <vector>
#include <SQLiteCpp.h>
#include "types.h"


namespace oonalysis::db::repo {

bool dbfile_present(int id);
bool dbfile_present(const std::string& id);
bool add_dbfile(db_file dbfile);
std::shared_ptr<db_file> get_dbfile(int id);
std::shared_ptr<db_file> get_dbfile(const std::string& filename);
std::vector<std::shared_ptr<db_file>> get_dbfiles();
bool update_dbfile(int id, db_file dbfile);
bool delete_dbfile(int id);
uint32_t max_loc();
float avg_loc();
uint32_t num_files();

bool dbcppinclusion_present(const std::string& includer, const std::string& includee);
bool add_dbcppinclusion(db_cppinclusion inclusion);
std::shared_ptr<db_cppinclusion> get_dbcppinclusion(int id);
std::vector<std::shared_ptr<db_cppinclusion>> get_dbcppinclusions();
bool update_dbcppinclusion(db_cppinclusion inclusion, int id);
bool delete_dbcppinclusion(int id);
uint32_t num_cppinclusions();

bool dbfunctionimpl_present(const std::string& name, const std::string& file);
bool add_dbfunctionimpl(db_function_impl func);
db_function_impl get_dbfunctionimpl(int id);
db_function_impl get_dbfunctionimpls();
bool update_dbfunctionimpl(int id, db_function_impl func);
bool delete_dbfunctionimpl(int id);

} // namespace oonalysis::db::repo

#endif // REPO_H
