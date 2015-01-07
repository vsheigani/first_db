#include "stdio.h"
#include "sqlite3.h"
#include "stdlib.h"
#include <stdbool.h>


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