#include "stdio.h"
#include "sqlite3.h"
#include "stdlib.h"
#include <stdbool.h>
#include "callbackh.h"

// This header file created for inserting data into tables

// This func checks if the insterted data is integer or not

bool isInt(char *string){
    char *endp;
    long n;
    n = strtol(string, &endp, 0);
    if(!*endp && INT_MIN <= n && n <= INT_MAX) {
   //     *num = (int)n;
        return true;
    }
    return false;
}


void insert_data(char table_name[],int rc, sqlite3 *db)
   {
    int k;
   char sql_string[600];
   char sql_string2[600];
   char *zErrMsg = 0;
   char *sql_2;
   char *sql;


   sprintf(sql_string2,"SELECT * FROM %s ",table_name);

   sql_2 = sql_string2;
   printf("%s\n", sql_string2);

     rc = sqlite3_exec(db, sql_2, callback_find, 0, &zErrMsg);
   if( rc != SQLITE_OK )
   {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }

   else{
  char data[100][count];

   for ( k = 0; k < count; ++k)
   {
     printf("Please Insert data for %s: ",items[k]);
     scanf("%s", data[k]);
     printf("\n");
   }


  sprintf(sql_string,"INSERT INTO %s (",table_name);
  for (k = 0; k < count; ++k)
  {
    strcat(sql_string,items[k]);
    if (k < count-1)
    {
    strcat(sql_string,",");
    }

  }
  items=NULL;
  strcat(sql_string, ") VALUES (");

  for (k = 0; k < count; ++k)
  {
    if (isInt(data[k]))
    {
      strcat(sql_string,data[k]);
    }
    else{
    strcat(sql_string,"'");
    strcat(sql_string,data[k]);
        strcat(sql_string,"'");
    }
    if (k < count-1)
    {
    strcat(sql_string,",");
    }
   }
  strcat(sql_string, "); ");

  sql= sql_string;
 // k=0; count=0;
 //printf("%s",sql_string);
   /* Execute SQL statement */

   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK )
   {
         fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   else
   {
      fprintf(stdout, "Data Inserted Succefully\n");
   }
 }
} 