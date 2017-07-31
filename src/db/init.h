#ifndef INIT_H
#define INIT_H

#include <string>
#include <SQLiteCpp.h>

namespace oonalysis {
namespace db {

void init_db();
void set_db_name(const std::string& name);

} // namespace db
} // namespace oonalysis

#endif // INIT_H
