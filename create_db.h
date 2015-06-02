#include "stdio.h"
#include "sqlite3.h"
#include "stdlib.h"
#include <stdbool.h>

 extern sqlite3 *db;
 extern int rc;
// Connect or create sqlite3 database with taking name of 
// the db from user
void create_db(char db_name[])
{
   rc = sqlite3_open(db_name, &db);
   if( rc )
      {
      fprintf(stderr, "Can't open or create database: %s\n", sqlite3_errmsg(db));
      exit(0);
      }
}
  