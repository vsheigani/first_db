#include "stdio.h"
#include "sqlite3.h"
#include "stdlib.h"
#include <stdbool.h>


int count;
  // This values will be initialized by callback_find function

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
    int result= 0;
   char sql_string[600];
   char sql_string2[600];
   char *zErrMsg = 0;
  // char *sql_2;
   char *sql;
   sqlite3_stmt * stmt;
   char *col;
   char stemp[50];
   char sstr[150];
   char data[100][count];

// This part of function execute a select command in sqlite and
// It calls callback_find func and so it will store the table items 
// count of items in two variables 
// sprintf(sstr, "SELECT sql FROM sqlite_master;");
// sprintf(sstr, ".schema %s",table_name);
// strcat(sstr,"'");
// strcat(sstr,"table");
// strcat(sstr,"';");
// sprintf(stemp,"ORDER BY %s;",table_name);

// strcat(sstr,stemp);
  sprintf(sstr,"pragma table_info(%s);",table_name);


//  sprintf(sstr,"select * from %s;",table_name);
  printf("%s\n",sstr );
  sqlite3_prepare_v2( db, sstr, -1, &stmt, NULL );
  sqlite3_step( stmt );
  count = sqlite3_column_count(stmt);



   //sprintf(sql_string2,"select * from %s;",table_name);
  
  

  // printf("%s\n", sql_string2);

  //   rc = sqlite3_exec(db, sql_string2, callback_find, 0, &zErrMsg);
   printf("%d\n",count);

//   if( rc != SQLITE_OK )
 //  {
 //     fprintf(stderr, "%s\n", zErrMsg);
  //    sqlite3_free(zErrMsg);
 //  }

  // else{
  
  
   // printf("yes\n");
              {
   for ( k = -1; k < count+3; ++k)
   {
    col = (char *)sqlite3_column_text( stmt, k);
    printf("Please Insert data for %s: ",col);
    scanf("%s", data[k]);
    printf("\n");
   }
  
// This part of code creates an sql string to insert data and execute it

  sprintf(sql_string,"INSERT INTO %s (",table_name);
  for (k = 0; k < count; ++k)
  {
   // strcat(sql_string,items[k]);
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
sqlite3_finalize(stmt);
} 