#include "stdio.h"
#include "sqlite3.h"
#include "stdlib.h"
#include  "string.h"
#include <stdbool.h>

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


