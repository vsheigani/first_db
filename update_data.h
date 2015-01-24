
#include "stdio.h"
#include "sqlite3.h"
#include "stdlib.h"

//This Header File Update data in Sqlite3 table

void update_data(char table_name2[],int rc,sqlite3 *db){
 
   char *zErrMsg = 0;
   char sql_string[700];
   char sql_p1[100],sql_p2[100];
   char idx[3], new[20], field[20];

   printf("Please enter id you to want update: ");
   scanf("%s",idx);

   printf("Please enter item you want to update in ID=%s ",idx);
   scanf("%s",field);

   printf("Please enter item new data to update in ID=%s Field=%s: ",idx,field);
   scanf("%s",new);

      sprintf(sql_string,"UPDATE %s SET %s = %s WHERE ID=%s; ",table_name2,field,new,idx);
   

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