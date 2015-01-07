#include "stdio.h"
#include "stdlib.h"
#include "sqlite3.h"
#include "string.h"
#include "call_help.h"
#include <stdbool.h>
#include <termios.h>
#include <limits.h>
#include <unistd.h>
#include "insert_data.h"
#include "create_table.h"
#include "select_data.h"
#include "delete_data.h"
#include "update_data.h"


static char **items;
static int count;
sqlite3 *db;
int  rc;


/*
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
        items=azColName;
        count=argc;
    }

   return 0;
}
*/

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
   create_table(table_name,rc,db);
   getchar();
      getchar();
   refresh_menu();
     break;

   case '3':
     system("clear");
     setBufferedInput(true);
      printf("Please enter the name of table: ");
      scanf("%s",table_name2);
      insert_data(table_name2,rc,db);
      getchar();
      getchar();
      refresh_menu();
      break;
   

   case '4':
     system("clear");
     setBufferedInput(true);
      printf("Please enter the name of table that you want to delete data: ");
      scanf("%s",table_name2);
      delete_data(table_name2,rc,db);
      getchar();
      getchar();
      refresh_menu();
      break;


       case '5':
     system("clear");
     setBufferedInput(true);
      printf("Please enter the name of database: ");
      scanf("%s",table_name2);
      update_data(table_name2,rc,db);
      getchar();
      getchar();
      refresh_menu();
      break;


    case '6':
     system("clear");
     setBufferedInput(true);
      printf("Please enter the name of table to select data in %s database: ", db_name);
      scanf("%s",table_name2);
      select_data(table_name2,rc,db);
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