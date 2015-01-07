#include "stdio.h"
#include "sqlite3.h"
#include "stdlib.h"
#include <stdbool.h>
#include "callbackh.h"




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

void insert_data(char table_name2[],int rc, sqlite3 *db)
   {
  //  char types[100][5];
    int k;
 //   sqlite3 *db;
   char *zErrMsg = 0;
 //  int  rc;
   char sql_string[700];
   char sql_p1[300],sql_p2[300];

   char sql_string2[600]; 
   sprintf(sql_string2,"SELECT * FROM %s ",table_name2);

   char *sql2=sql_string2;
   printf("%s", sql_string2);

     rc = sqlite3_exec(db, sql2, callback_find, 0, &zErrMsg);
   if( rc != SQLITE_OK )
   {
      fprintf(stderr, "Table Not Found\n");
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


  sprintf(sql_string,"INSERT INTO %s (",table_name2);
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

  char *sql= sql_string;
 // k=0; count=0;
 printf("%s",sql_string);
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
