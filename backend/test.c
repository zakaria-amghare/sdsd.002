#include<stdio.h>
#include<stdlib.h>
#include "fonction.h"
#include "types.h"

int main ()
{

FILE *z;
z=fopen("bombom.bin","w+");
tete tet;
tet.nb_b=10;
tet.nb_p_t=90;
tete et;
et.nb_b=110;
et.nb_p_t=990;


block block__write;
block__write.nb_p=100;
for (int i = 0; i < 10; i++)
{
block__write.produit[i].prix=i+i*10+i*100;
}
block block__read;



fwrite(&tet,sizeof(tet),1,z);

fwrite(&block__write,sizeof(block__write),1,z);
fwrite(&block__write,sizeof(block__write),2,z);
for (int i = 0; i < 50; i++)
{
fwrite(&block__write,sizeof(block__write),1,z);
}




rewind(z);
fread(&et,sizeof(tet),1,z);
fread(&block__read,sizeof(block__read),1,z);
            for (int j = 0; j < 10; j++)
            { 
            printf("****%d*****%d\n",et.nb_b,block__read.produit[j].prix);
            }
fread(&block__read,sizeof(block__read),1,z);




            printf("\n\n\n\n\n\n%d",3);
            for (int j = 0; j < 10; j++)
            { 
            printf("****%d*****%d\n",et.nb_b,block__read.produit[j].prix);
            }


      for (int i =0; i < 50; i++)
{
fread(&block__read,sizeof(block),1,z);
            for (int j = 0; j < 10; j++)
            { 
            printf("****%d*****%d\n",et.nb_b,block__read.produit[j].prix);
            }
            printf("\n\n\n\n\n\n%d",i);
}

//fprintf(z,"\nazertyuiop\n");


}
/*


printf("----%d+++++++%d\n\n",et.nb_b,et.nb_p_t);





*/
