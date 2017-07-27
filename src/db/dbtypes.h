#include "db.h"

typedef struct db_file
{
    int id;
    char filename[MAX_FILENAME];
} db_file;

typedef struct db_cppinclusion
{
    int id;
    char includer[MAX_FILENAME];
    char includee[MAX_FILENAME];
} db_cppinclusion;
