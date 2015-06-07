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
    else{
         return false;
        }
}

//This function inserts data into table
void insert_data(char table_name[])
   {
    int k;
    int result= 0;
   char sql_string[600];
   char sql_string2[600];
   char *zErrMsg = 0;
   sqlite3_stmt * stmt;
   char *col;
   char stemp[50];
   char sstr[150];

 

// This part of function execute a select command in sqlite and
// It calls callback_find func and so it will store the table items 
// count of items in two variables 

// sprintf(sstr, ".schema %s",table_name);
// strcat(sstr,"'");
// strcat(sstr,"table");
// strcat(sstr,"';");
// sprintf(stemp,"ORDER BY %s;",table_name);

// strcat(sstr,stemp);


  //sprintf(sstr2,"pragma table_info(%s);",table_name);
   sprintf(sstr, "SELECT * FROM %s;",table_name);
  sqlite3_prepare( db, sstr, sizeof(sstr), &stmt, NULL );
  sqlite3_step( stmt );
 // printf("%s\n",sstr2 );


  count = sqlite3_column_count(stmt);
  char data[count][20];


   //sprintf(sql_string2,"select * from %s;",table_name);
  
  

  // printf("%s\n", sql_string2);

  //   rc = sqlite3_exec(db, sql_string2, callback_find, 0, &zErrMsg);
   printf("This table has \x1b[31m%d\x1b[0m Columns.\n\n",count);

//   if( rc != SQLITE_OK )
 //  {
 //     fprintf(stderr, "%s\n", zErrMsg);
  //    sqlite3_free(zErrMsg);
 //  }

  // else{
  
  
   // printf("yes\n");
        
   for ( k = 0 ; k < count ; k++)
   { 

    printf("Please Insert data for \x1b[31m%s\x1b[0m: ",(char *)sqlite3_column_name( stmt, k));
    printf("\x1b[31m");
    scanf("%s", data[k]);
    printf("\x1b[0m");
    
    
   }

  
// This part of code creates an sql string to insert data and execute it

  sprintf(sql_string,"INSERT INTO %s ",table_name);
 
  strcat(sql_string, "VALUES (");

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
  //printf("%s\n", sql_string);


   /* Execute SQL statement */

   rc = sqlite3_exec(db, sql_string, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK )
   {
    printf("%s\n",sql_string );
         fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   else
   {
    printf("\n");
      fprintf(stdout, "Data Inserted Succefully\n");
   }
   
sqlite3_finalize(stmt);
} 