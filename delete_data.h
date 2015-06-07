#include "stdio.h"
#include "sqlite3.h"
#include "stdlib.h"

// This Header File Delete data from Sqlite3 table

void delete_data(char table_name[]){
 
   char *zErrMsg = 0;
   char sql[700];
   char idx[30];


   printf("Which \x1b[31mID\x1b[0m you want to delete? ");
  
      printf("\x1b[31m");
      scanf("%s", idx);
      printf("\x1b[0m");
   
      sprintf(sql,"DELETE FROM %s WHERE ID=%s",table_name,idx);
     

   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK )
   {
         fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   else
   {
      fprintf(stdout, "Data of ID=\x1b[31m%s\x1b[0m Deleted succefully.\n",idx);
   }
}
