/* rdict_srp.c - initw, insertw, deletew, lookupw */

#include <rpc/rpc.h>

#include "rdict.h"
char dict[DICTSIZ] [MAXWORD+1];
int  nwords = 0;
char sucherg [MAXSUCHERG];

int initw() {
   nwords = 0;
   return 1;
}

int insertw (word)
char *word;
{
   int i;
   for (i=0; i<nwords; i++)
      if (strcmp (word, dict[i]) == 0)
         return 0;
   strcpy (dict[nwords], word);
   nwords++;
   return nwords;
}

int deletew (word)
char *word;
{
   int i;
   for (i=0; i<nwords; i++)
      if (strcmp (word, dict[i]) == 0) {
         nwords--;
         strcpy (dict[i], dict[nwords]);
         return 1;
      }
   return 0;
}

int lookupw (word)
char *word;
{
   int i;
   for (i=0; i<nwords; i++)
      if (strcmp (word, dict[i]) == 0)
         return 1;
   return 0;
}

int updatew (word, word2)
char *word, *word2;
{
   int i;
   for (i=0; i<nwords; i++)
      if (strcmp (word, dict[i]) == 0) {
         strcpy (dict[i], word2);
         return 1;
      }
   return 0;
}

char **selectw(void) {
   int i;
   static char *ret_dict;
   ret_dict = malloc(sizeof(char));
   ret_dict[0] = '\0';
   for (i=0; i<nwords; i++) {
      ret_dict = realloc(ret_dict, strlen(ret_dict) + strlen(dict[i]) + 2);
      strncat (ret_dict, dict[i], strlen(dict[i]));
      strncat (ret_dict, " \0", 2);
   }
   return (&ret_dict);
}

manywords *select2w(void) {
   int i;
   static manywords *ret_value;
   ret_value = malloc(sizeof(manywords));
   ret_value->words.words_len = nwords;
   ret_value->words.words_val = malloc(nwords * sizeof(oneword));
   for (i=0; i<nwords; i++) {
      ret_value->words.words_val[i].word = dict[i];
   }
   return ret_value;
}

