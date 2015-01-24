#include "stdio.h"
#include "sqlite3.h"
#include "stdlib.h"

// This Header File Delete data from Sqlite3 table

void delete_data(char table_name2[],int rc,sqlite3 *db){
 
   char *zErrMsg = 0;
   char sql_string[700];
   char sql_p1[100],sql_p2[100];
   char idx[3];


   printf("Please enter id to delete: ");
   scanf("%s",idx);

      strcpy(sql_p1,"DELETE FROM ");
      strcpy(sql_p2," WHERE ID");
      
      sprintf(sql_string,"%s%s%s=%s; ",sql_p1,table_name2,sql_p2,idx);
   

   char *sql= sql_string;
   

   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK )
   {
         fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   else
   {
      fprintf(stdout, "Data deleted succefully\n");
   }
}
