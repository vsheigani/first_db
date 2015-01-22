#include "stdio.h"
#include "sqlite3.h"
#include "stdlib.h"
#include <stdbool.h>

    char **items;
    int count;

// This is a callback function for printing table items and their data
// This will print data of table like "ITEM = DATA" in Terminal 

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

// This is a callback function for storing table items count and items in two varibales
// Then you will be able to take data for each items in table and insert it into table

static int callback_find(void *NotUsed, int argc, char **argv, char **azColName)

{         
   
        items=azColName;
        count=argc;

        return 0;
}
