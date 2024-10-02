#include <stdio.h>
#include "fonction.h"
#include "types.h"
/*creation de fichier */
void creation ()
{
 FILE *file;
 file= fopen("fileee","w+");
 if (file==NULL)
 {
  perror("haha");
 }
 
}