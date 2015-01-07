
#include "stdio.h"
#include "sqlite3.h"
#include "stdlib.h"
#include <stdbool.h>


   void create_table(char table_name2[],int rc,sqlite3 *db)
   {
    char names[100][5];
    char types[100][5];
    int i;
 //   sqlite3 *db;
   char *zErrMsg = 0;
 //  int  rc;
   char sql_string[700];
   char sql_p1[300],sql_p2[300];
   for ( i = 0; i < 5; ++i)
   {
     printf("Please Enter the name of field you want create in table %s: ",table_name2);
     scanf("%s", names[i]);

     printf("Please enter type of field %s in table %s: ",names[i],table_name2);
     scanf("%s", types[i]);
   }

   sprintf(sql_string,"CREATE TABLE %s (" \
     " INDEX INT PRIMARY KEY AUTOINCREMENT," \
     " %s %s NOT NULL," \
     " %s %s NOT NULL," \
     " %s %s NOT NULL," \
     " %s %s," \
     " %s %s); ",table_name2,names[0],types[0],names[1],types[1],names[2],types[2],names[3],types[3],names[4],types[4]);
   
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
      fprintf(stdout, "Table created successfully\n");
   }
   }