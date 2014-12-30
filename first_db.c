#include "stdio.h"
#include "stdlib.h"
#include "sqlite3.h"
#include "string.h"
#include "call_help.h"
#include <stdbool.h>
#include <termios.h>
#include <limits.h>
#include <unistd.h>

sqlite3 *db;
int  rc;
char **items;
int count;

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


static int callback(void *NotUsed, int argc, char **argv, char **azColName)

{
   int i;

   for(i=0; i<argc; i++)
   	{
      	printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   	}

   printf("\n");
   return 0;
}

static int callback_find(void *NotUsed, int argc, char **argv, char **azColName)

{
   int i;

   for(i=0; i<argc; i++)
    {
        //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
      items =azColName;
      count=argc;
    }

   //printf("\n");
   return 0;
}
  void setBufferedInput(bool enable) {
    static bool enabled = true;
    static struct termios old;
    struct termios new;
    if (enable && !enabled) {
      tcsetattr(STDIN_FILENO,TCSANOW,&old);
      enabled = true;
    } else if (!enable && enabled) {
    tcgetattr(STDIN_FILENO,&new);
    old = new;
    new.c_lflag &=(~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO,TCSANOW,&new);
    enabled = false;
    }
  }

void create_db(char db_name[])
{
   

   rc = sqlite3_open(db_name, &db);
   if( rc )
      {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
      }
   else
      {
         fprintf(stdout, "Database %s opened successfully\n",db_name);
         
      }
   }
   
      void insert_data(char table_name2[])
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
 //  printf("%s",sql_string2 );

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

  //    strcpy(sql_p1,"CREATE TABLE ");
   //   strcpy(sql_p2," ("  \
   //      "ID INT PRIMARY KEY     NOT NULL," \
   //      "NAME           TEXT    NOT NULL," \
  //       "AGE            INT     NOT NULL," \
  //       "ADDRESS        CHAR(50)," \
   //      "SALARY         REAL );");
  // sprintf(sql_string,"CREATE TABLE %s (" \
   //  " INDEX INT PRIMARY KEY AUTOINCREMENT," \
   //  " %s %s NOT NULL," \
   //  " %s %s NOT NULL," \
   //  " %s %s NOT NULL," \
   //  " %s %s," \
  //   " %s %s); ",table_name2,names[0],types[0],names[1],types[1],names[2],types[2],names[3],types[3],names[4],types[4]);

  sprintf(sql_string,"INSERT INTO %s (",table_name2);
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
      fprintf(stdout, "Data Inserted Succefully\n");
   }
 }
 
   }

   void create_table(char table_name2[])
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

  //    strcpy(sql_p1,"CREATE TABLE ");
   //   strcpy(sql_p2," ("  \
   //      "ID INT PRIMARY KEY     NOT NULL," \
   //      "NAME           TEXT    NOT NULL," \
  //       "AGE            INT     NOT NULL," \
  //       "ADDRESS        CHAR(50)," \
   //      "SALARY         REAL );");
  
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


  void select_data(char table_name2[])
   {
 //   sqlite3 *db;
   char *zErrMsg = 0;
 //  int  rc;
   char sql_string[700];
   char sql_p1[300],sql_p2[300];


      strcpy(sql_p1,"SELECT * FROM ");
     // strcpy(sql_p2,";");
      
      sprintf(sql_string,"%s%s",sql_p1,table_name2);
   
   //printf("%s",sql_string);
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
      fprintf(stdout, "Table Selected succefully\n");
   }
   
   }
void refresh_menu(){

   system("clear");
   setBufferedInput(false);
   printf("\033[12;40H%-20s","Hints:");
   printf("\033[13;40H%-20s","Press 1 For Creating or Connecting to Database: ");
   printf("\033[14;40H%-20s","Press 2 For Creating a Table: ");
   printf("\033[15;40H%-20s","Press 3 For Inserting data into table: ");
   printf("\033[16;40H%-20s","Press 4 For Delete data from the table: ");
   printf("\033[17;40H%-20s","Press 5 For Update your table data: ");
   printf("\033[18;40H%-20s","Press 6 For Select your table data: ");
   printf("\033[19;40H%-20s","Press Q For Quit: ");

}
void delete_data(char table_name2[]){
 
   char *zErrMsg = 0;
   char sql_string[700];
   char sql_p1[100],sql_p2[100];
   char idx[3];


   printf("Please enter id to delete: ");
   scanf("%s",idx);

      strcpy(sql_p1,"DELETE FROM ");
      strcpy(sql_p2," WHERE ID");
  //    strcpy(sql_p3,"ID");
      
      sprintf(sql_string,"%s%s%s=%s; ",sql_p1,table_name2,sql_p2,idx);
   
   //printf("%s",sql_string);
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

void update_data(char table_name2[]){
 
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


  //    strcpy(sql_p1,"DELETE FROM ");
  //    strcpy(sql_p2," WHERE ID");
  //    strcpy(sql_p3,"ID");
      
      sprintf(sql_string,"UPDATE %s SET %s = %s WHERE ID=%s; ",table_name2,field,new,idx);
   
   //printf("%s",sql_string);
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

int main(int argc, char const *argv[])
{
      int status=0;
      char getkey;
      char table_name[100];
      char table_name2[100];
      char db_name[120];
   

   if (argv[1]!= NULL && strcmp(argv[1],"-h")== 0)
   {
      call_help();
      getchar();
   }

refresh_menu();


while(1){

getkey=getchar();
switch(getkey){
   case '1':
     system("clear");
     setBufferedInput(true);
      printf("Please enter the name of database: ");
      scanf("%s",db_name);
      create_db(db_name);
      getchar();
      getchar();
      refresh_menu();
      break;

   case '2':
   system("clear");
   setBufferedInput(true);
   
   printf("Plase enter the name of table: ");
   scanf("%s",table_name);
   create_table(table_name);
   getchar();
      getchar();
   refresh_menu();
     break;

   case '3':
     system("clear");
     setBufferedInput(true);
      printf("Please enter the name of table: ");
      scanf("%s",table_name2);
      insert_data(table_name2);
      getchar();
      getchar();
      refresh_menu();
      break;
   

   case '4':
     system("clear");
     setBufferedInput(true);
      printf("Please enter the name of table that you want to delete data: ");
      scanf("%s",table_name2);
      delete_data(table_name2);
      getchar();
      getchar();
      refresh_menu();
      break;


       case '5':
     system("clear");
     setBufferedInput(true);
      printf("Please enter the name of database: ");
      scanf("%s",table_name2);
      update_data(table_name2);
      getchar();
      getchar();
      refresh_menu();
      break;


    case '6':
     system("clear");
     setBufferedInput(true);
      printf("Please enter the name of table to select data in %s database: ", db_name);
      scanf("%s",table_name2);
      select_data(table_name2);
      getchar();
      getchar();
      refresh_menu();
      break;

   case 'q':
   system("clear");
   setBufferedInput(true);
   sqlite3_close(db);
   exit(status);
  break;
}
}

   
	return 0;
}