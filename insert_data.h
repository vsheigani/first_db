#include "stdio.h"
#include "sqlite3.h"
#include "stdlib.h"
#include <stdbool.h>
#include "callbackh.h"

  extern char **items;
  extern int count;
  int rc;
  sqlite3 *db;

  // This header file created for inserting data into tables
  // This func checks if the insterted data is integer or not

// This Function checks if the string parameter is only integer or not
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

//This function inserts data into table
void insert_data(char table_name[])
   {
    int k;
   char sql_string[600];
   char sql_string2[600];
   char *zErrMsg = 0;
   char *sql_2;
   char *sql;
   char data[100][count];

// This part of function execute a select command in sqlite and
// It calls callback_find func and so it will store the table items 
// count of items in two variables 

   sprintf(sql_string2,"SELECT * FROM %s ",table_name);

   sql_2 = sql_string2;
   printf("%s\n", sql_string2);

     rc = sqlite3_exec(db, sql_2, callback_find, 0, &zErrMsg);
   if( rc != SQLITE_OK )
   {
      fprintf(stderr, "Hi: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }

   else{
  

   for ( k = 0; k < count; ++k)
   {
    printf("Hi\n");
    printf("%s", items[k]);
    printf("Please Insert data for %s: ",items[k]);
    scanf("%s", data[k]);
    printf("\n");
   }
// This part of code creates an sql string to insert data and execute it

  sprintf(sql_string,"INSERT INTO %s (",table_name);
  for (k = 0; k < count; ++k)
  {
    strcat(sql_string,items[k]);
    if (k < count-1)
    {
    strcat(sql_string,",");
    }

  }
 
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

 
   /* Execute SQL statement */

   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK )
   {
    printf("%s\n",sql_string );
         fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   else
   {
      fprintf(stdout, "Data Inserted Succefully\n");
   }
   
 }
} 