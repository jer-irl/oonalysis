#include "dbtypes.h"

bool add_dbfile(db_file dbfile);
db_file get_dbfile(int id);
int get_dbfiles(db_file** files);
bool update_dbfile(db_file dbfile, int id);
bool delete_dbfile(int id);

bool add_dbcppinclusion(db_cppinclusion inclusion);
db_cppinclusion get_dbcppinclusion(int id);
int get_dbcppinclusions(db_cppinclusion** inclusions);
bool update_dbcppinclusion(db_cppinclusion inclusion, int id);
bool delete_dbcppinclusion(int id);

