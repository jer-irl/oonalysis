#include "dbtypes.h"

bool add_dbfile(db_file dbfile);
bool get_dbfile(int id, db_file* dbfile);
int get_dbfiles(db_file** files);
bool update_dbfile(db_file dbfile, int id);
bool delete_dbfile(int id);

bool add_dbcppinclusion(db_cppinclusion inclusion);
bool get_dbcppinclusion(int id, db_cppinclusion* incl);
int get_dbcppinclusions(db_cppinclusion** inclusions);
bool update_dbcppinclusion(db_cppinclusion inclusion, int id);
bool delete_dbcppinclusion(int id);

