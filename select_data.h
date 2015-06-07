#include "stdio.h"
#include "sqlite3.h"
#include "stdlib.h"


// This Header file select data from table and show them in Terminal

  void select_data(char table_name2[])
   {
 
   char *zErrMsg = 0;

   char sql_string[700];
   char sql_p1[300],sql_p2[300];


      strcpy(sql_p1,"SELECT * FROM ");
     
      
      sprintf(sql_string,"%s%s",sql_p1,table_name2);

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
      fprintf(stdout, "Table Data Selected succefully\n");
   }
   
   }