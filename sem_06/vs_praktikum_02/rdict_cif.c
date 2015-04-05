/* rdict_cif.c - initw, insertw, deletew, lookupw, ... */

#include <rpc/rpc.h>
#include <stdio.h>
#include "rdict.h"

extern CLIENT *handle;
static int *ret;
static char **ret_char;
static manywords *ret_manywords;

int initw() {
   ret = initw_1 (0, handle);
   return ret==0 ? 0 : *ret;
}

int insertw(word)
char *word;
{
   char **arg;
   arg = &word;
   ret = insertw_1(arg, handle);
   return ret==0 ? 0 : *ret;
}

int deletew (word)
char *word;
{
   char **arg;
   arg = &word;
   ret = deletew_1 (arg, handle);
   return ret==0 ? 0 : *ret;
}

int lookupw (word)
char *word;
{
   char **arg;
   arg = &word;
   ret = lookupw_1 (arg, handle);
   return ret==0 ? 0 : *ret;
}

int updatew (word, word2)
char *word, *word2;
{
   struct upd arguments, *arg;
   arguments.upd_old = word;
   arguments.upd_new = word2;
   arg = &arguments;
   ret = updatew_1 (arg, handle);
   return ret==0 ? 0 : *ret;
}

int
selectw(void)
{
   char **ret = selectw_1(NULL, handle);
   printf("%s\n", *ret);
   return ret==0 ? 0 : 1;
}

int
select2w(void)
{
   manywords *ret = select2w_1(NULL, handle);
   u_int i;
   for (i = 0; i < ret->words.words_len; i++) {
      printf("%s\n", ret->words.words_val[i].word);
   }
   return ret==0 ? 0 : 1;
}
