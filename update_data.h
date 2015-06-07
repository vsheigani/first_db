
#include "stdio.h"
#include "sqlite3.h"
#include "stdlib.h"

//This Header File Update data in Sqlite3 table

void update_data(char table_name[]){
 
   char *zErrMsg = 0;
   char sql_string[700];
   char sql_p1[100],sql_p2[100];
   char idx[30], newdata[20], field[20];

   printf("Please enter \x1b[31mID\x1b[0m you to want update: ");
       printf("\x1b[31m");
      scanf("%s", idx);
      printf("\x1b[0m");

   printf("Please enter Field you want to update in ID=\x1b[31m%s\x1b[0m: ",idx);
       printf("\x1b[31m"); 
      scanf("%s", field);
      printf("\x1b[0m");

   printf("Please enter Field New data to update in ID=\x1b[31m%s\x1b[0m Field=\x1b[31m%s\x1b[0m: ",idx,field);
   printf("\x1b[31m");
      scanf("%s", newdata);
      printf("\x1b[0m");


      sprintf(sql_string,"UPDATE %s SET %s = '%s' WHERE ID=%s; ",table_name,field,newdata,idx);
   

   char *sql= sql_string;
   

   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK )
   {
         fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   else
   {
      fprintf(stdout, "Data Updated succefully\n");
   }
   


}