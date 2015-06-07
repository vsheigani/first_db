#include <stdbool.h>
#include <termios.h>
#include <limits.h>
#include <unistd.h>
#include "stdio.h"
#include "stdlib.h"
#include "sqlite3.h"
#include "string.h"
#include "callbackh.h"
#include "create_db.h"
#include "call_help.h"
#include "insert_data.h"
#include "create_table.h"
#include "select_data.h"
#include "delete_data.h"
#include "update_data.h"




sqlite3 *db;
int  rc ;

// Changing global state of terminal so you don't need to 
// hit enter for entering any key

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


      


// Refreshing Application menu after each action

void refresh_menu(){

   system("clear");
   setBufferedInput(false);
   printf("\033[2;7H%-20s","Hints:");
   printf("\033[3;7H%-20s","Press 1 For Creating or Connecting to Database: ");
   printf("\033[4;7H%-20s","Press 2 For Creating a Table: ");
   printf("\033[5;7H%-20s","Press 3 For Inserting data into table: ");
   printf("\033[6;7H%-20s","Press 4 For Delete data from the table: ");
   printf("\033[7;7H%-20s","Press 5 For Update your table data: ");
   printf("\033[8;7H%-20s","Press 6 For Select your table data: ");
   printf("\033[9;7H%-20s","Press Q For Quit: ");

}



int main(int argc, char const *argv[])
{
      FILE *file;
      int status=0;
      char getkey;
      char table_name[100];
   //   char table_name2[100];
      char db_name[20];
      char dbn[30];
      char txt[512];
      char command[50];
   

   if (argv[1]!= NULL && strcmp(argv[1],"-h")== 0)
   {
      call_help();
      getchar();
   }

refresh_menu();


while(1){

getkey=getchar();
switch(getkey){


  // doing appropriate action if key 1 pressed
   case '1':
     system("clear");
     setBufferedInput(true);
     strcpy(dbn,"");
     if(db != NULL)
     {
       sqlite3_close(db);
       db = NULL;
     }

     printf("List of avliable Databases:\n");
   
     system("cd ~/gitdir/first_db");
     
     FILE *p = popen("ls *.db","r");
     printf("\x1b[31m");
     while ( fgets( txt, 512, p ) != NULL ) {
     printf("%s", txt );
     }
     printf("\x1b[0m");
     pclose(p); 
     
        printf("\n");
    
   

      printf("Please enter the name of database (wiothout extension): ");
      printf("\x1b[31m");
      scanf("%s",db_name);
      printf("\x1b[0m");
      strcpy(dbn,db_name);
      strcat(dbn,".db");

    if(fopen(dbn,"r"))
        {
            printf("Database \x1b[31m%s\x1b[0m exists, so connected.\n", dbn);
        }
    else
        {
            printf("Database \x1b[31m%s\x1b[0m doesn't exist, so created.\n", dbn);
        }
   create_db(dbn);
getchar();

      getchar();
      refresh_menu();
      break;


// doing appropriate action if key 2 pressed
   case '2':
   system("clear");
   setBufferedInput(true);
   
   printf("Plase enter the name of table: ");
   printf("\x1b[31m");
   scanf("%s",table_name);
   printf("\x1b[0m");
        printf("\n");

   create_table(table_name);
      getchar();
      getchar();
      printf("\x1b[0m");
   refresh_menu();
     break;

// doing appropriate action if key 3 pressed
   case '3':
     system("clear");
     setBufferedInput(true);
      printf("Please enter the name of table: ");
       printf("\x1b[31m");
      scanf("%s",table_name);
       printf("\x1b[0m");
            printf("\n");

      insert_data(table_name);
      getchar();
      getchar();
      refresh_menu();

      break;
   
// doing appropriate action if key 4 pressed

   case '4':
     system("clear");
     setBufferedInput(true);
      printf("Please enter the name of table that you want to delete data: ");
       printf("\x1b[31m");
      scanf("%s",table_name);
       printf("\x1b[0m");
            printf("\n");
      select_data(table_name);
      printf("\n\n");
      delete_data(table_name);
      getchar();
     getchar();
      refresh_menu();
      break;

// doing appropriate action if key 5 pressed
       case '5':
     system("clear");
     setBufferedInput(true);
      printf("Please enter the name of table to update data \x1b[31m%s\x1b[0m database: ", db_name);
        printf("\x1b[31m");
      scanf("%s",table_name);
       printf("\x1b[0m");
            printf("\n");

      update_data(table_name);
      getchar();
getchar();
      refresh_menu();
      break;


// doing appropriate action if key 6 pressed
    case '6':
     system("clear");
     setBufferedInput(true);
      printf("Please enter the name of table to select data in \x1b[31m%s\x1b[0m database: ", db_name);
        printf("\x1b[31m");
      scanf("%s",table_name);
       printf("\x1b[0m");
            printf("\n");

      select_data(table_name);
      getchar();
   getchar();
      refresh_menu();
      break;


// doing appropriate action if key Q pressed

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
