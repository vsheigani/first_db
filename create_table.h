
#include "stdio.h"
#include "sqlite3.h"
#include "stdlib.h"
#include <stdbool.h>


// This Header file creates Tables with needed fields and Types 

   void create_table(char table_name2[],int rc,sqlite3 *db)
   {
    char names[100][5];
    char types[100][5];
    int i;
    int j;
 //   sqlite3 *db;
   char *zErrMsg = 0;
 //  int  rc;
   char sql_string[700];
   char sql_p1[300],sql_p2[300];
   // Takes number of fields the user wants to create

   printf("How many fields you want to create in this table: ");
   scanf("%d",&j);
   for ( i = 0; i < j; ++i)
   {
     printf("Please Enter the name of field you want create in table %s: ",table_name2);
     scanf("%s", names[i]);

     printf("Please enter type of field %s in table %s: ",names[i],table_name2);
     scanf("%s", types[i]);
   }

   sprintf(sql_string,"CREATE TABLE %s (" ,table_name2);

      for ( i = 0; i < j; ++i)
   {
    strcat(sql_string,names[i]);
    strcat(sql_string," ");
    strcat(sql_string,types[i]);
    strcat(sql_string," ");
    if (i < j-1)
    {
    strcat(sql_string,",");
    }
   }
   strcat(sql_string," );");

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