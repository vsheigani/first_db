#include "stdio.h"
#include "sqlite3.h"
#include "stdlib.h"

  void select_data(char table_name2[],int rc,sqlite3 *db)
   {
 //   sqlite3 *db;
   char *zErrMsg = 0;
 //  int  rc;
   char sql_string[700];
   char sql_p1[300],sql_p2[300];


      strcpy(sql_p1,"SELECT * FROM ");
     // strcpy(sql_p2,";");
      
      sprintf(sql_string,"%s%s",sql_p1,table_name2);
   
   //printf("%s",sql_string);
   char *sql= sql_string;


   /* Execute SQL statement */

   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK )
   {
         fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   else
   {
      fprintf(stdout, "Table Selected succefully\n");
   }
   
   }