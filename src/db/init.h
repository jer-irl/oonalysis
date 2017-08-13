#ifndef INIT_H
#define INIT_H

#include <string>

namespace oonalysis::db {

void init_db();
void set_db_name(const std::string& name);

} // namespace oonalysis::db

#endif // INIT_H
