#include<stdbool.h>
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
FILE *z;
tete tetef;
block block_tmp;

void creation(char name[5])//done
{
    printf("\ncreation\n");

    z = fopen(name, "r");
    if (z)
    {
        printf("1\n");
        printf("the file already exicte\n");
    }
    else
    {
        printf("the file NEVER exicted");
        printf("2\n");
        z = fopen(name, "w+");

        tetef.nombre_de_block = 0;
        tetef.nombre_de_produit_total = 0;
        fwrite(&tetef, sizeof(tetef), 1, z);
    }
    rewind(z);
    fread(&tetef, sizeof(tete), 1, z);
    printf("inisialement there is =====>%d block\n", tetef.nombre_de_block);
    printf("inisialement there is =====>%d produit\n", tetef.nombre_de_produit_total);
    fclose(z);
    printf("CREATION FINI\n");
    esp();
}

produit emplacment(char name[5],int number_of_block,int number_of_emlement_in_block)//done
{
    z=fopen(name,"r");
    fseek(z,sizeof(tete)+sizeof(block)*(number_of_block-1),SEEK_SET);
    fread(&block_tmp,sizeof(block_tmp),1,z);
    return block_tmp.produit[number_of_emlement_in_block];
}

void display(char name[5])//done
{
printf("\ndisplay\n");
z = fopen(name, "r");
fread(&tetef, sizeof(tete), 1, z);
printf("\n\n\n");
printf("there is =====>%d block\n", tetef.nombre_de_block);
printf("there is =====>%d produit\n", tetef.nombre_de_produit_total);

    for (int i = 1; i <= tetef.nombre_de_block; i++)
    {
        fread(&block_tmp, sizeof(block), 1, z);
        for (int j = 0; j < block_tmp.nombre_de_produit; j++)
        {   
            //printf("---------------------------------");
            printf("|block %d--produit% d\n", i, j+1);
            printf("|name----> %c\t\t\tid----> %ld\n", block_tmp.produit[j].nom, block_tmp.produit[j].id);
        }
            printf("____________________________");
            printf("____________________________\n");
            printf("____________________________");
            printf("____________________________\n");
        printf("\n\n");
    }
}

bool recherche(char name[5],produit prodect,int *number_of_block,int *number_of_emlement_in_block)//done
{
z=fopen(name,"r");
fread(&tetef, sizeof(tete), 1, z);
       for (int i = 0; i < tetef.nombre_de_block; i++)
       {
          fread(&block_tmp,sizeof(block),1,z);
          for (int j =0; j < block_tmp.nombre_de_produit;j++)
          {
             if (block_tmp.produit[j].id==prodect.id)
             {
              fclose(z);
              *number_of_block=i+1;
              *number_of_emlement_in_block=j+1;
              printf("the prodect is here \nin block----->%d\nand it number----->%d",i+1,j+1);
              return true;
             }
          }
       }
    fclose(z);
     printf("it does not exciste!!");
    return false;}

bool O_recherche (char name[5],produit prodect,int *number_of_block,int *number_of_emlement_in_block)
{
*number_of_block=0;
*number_of_emlement_in_block=0;
z=fopen(name,"r");
fseek(z,sizeof(tetef),SEEK_SET);
fread(&block_tmp,sizeof(block_tmp),1,z);
if (block_tmp.produit[0].id>prodect.id)
    {
        printf("\n\n\nthe prodect youre looking for does not exicte SO SORRY!!!!\nthe value is too small\n\n\n");
        fclose(z);
        for (int i = 0; i < 10; i++)
        {
            printf("\n\n--->>>%ld",block_tmp.produit[i].id);
        }
        return false;
    }


fseek(z,-sizeof(block_tmp),SEEK_END);
fread(&block_tmp,sizeof(block_tmp),1,z);
if (block_tmp.produit[block_tmp.nombre_de_produit-1].id<prodect.id)
    {
        printf("\n\n\nthe prodect youre %ld looking for does not exicte SO SORRY!!!!\nthe value is too great than%ld\n\n",prodect.id,block_tmp.produit[block_tmp.nombre_de_produit-1].id);
        fclose(z);
                for (int i = 0; i < block_tmp.nombre_de_produit; i++)
        {
            printf("\n\n--->>>%ld",block_tmp.produit[i].id);
        }
        return false;
    }
rewind(z);

fread(&tetef,sizeof(tetef),1,z);
int borne_infer=1;
int borne_super=tetef.nombre_de_block;
int Moy;
Moy=(borne_infer+borne_super)/2;

while (borne_infer<borne_super)
{
    fseek(z,sizeof(tete)+sizeof(block)*(Moy-1),SEEK_SET);
    fread(&block_tmp,sizeof(block),1,z);
    printf("\n\n\n");
    printf("\nthe CUR BOLOCK===>>>%d\n",Moy);
    printf("it contains.....");
    printf("BOENE INFER===>%d\nMOYENNE===>%d\nBOENE SUPPER===>%d\n\n\n",borne_infer,Moy,borne_super);

           for (int i = 0; i < block_tmp.nombre_de_produit; i++)
           {
            printf("\n%ld",block_tmp.produit[i].id);
            if (prodect.id==block_tmp.produit[i].id)
                {
                    printf("BOENE INFER===>%d\nMOYENNE===>%d\nBOENE SUPPER===>%d\n",borne_infer,Moy,borne_super);
                    break;
                    borne_infer=borne_super;
                    *number_of_block=Moy;
                    *number_of_emlement_in_block=i+1;
                } 
           }
    if (prodect.id<block_tmp.produit[0].id)
    {
        borne_super=Moy;
    }    
    
    if (prodect.id>block_tmp.produit[9].id)
    {
        borne_infer=Moy;
    }
    
     Moy=(borne_infer+borne_super)/2;      
}

printf("\nthe prodect must be in %d\n",Moy-1);
*number_of_block=Moy/2;
for (int i = 0; i < block_tmp.nombre_de_produit; i++)
           {
             printf("\n%ld",block_tmp.produit[i].id);
             if (prodect.id==block_tmp.produit[i].id)
                {
                    fclose(z);
                    return true;
                } 
           }
fclose(z);
return false;
}

void R_inserstion(char name[5], produit prodect)
{
printf("\ninsertion\n");
z = fopen(name, "r+");
fread(&tetef, sizeof(tete), 1, z);
    if (tetef.nombre_de_produit_total % 10 == 0)
    {
        tetef.nombre_de_block++;
        tetef.nombre_de_produit_total++;
        rewind(z);
        fwrite(&tetef, sizeof(tete), 1, z);
        /* ****************************** */
        block_tmp.nombre_de_produit=1;
        block_tmp.produit[0]=prodect;
        fseek(z,0,SEEK_END);
        fwrite(&block_tmp,sizeof(block),1,z);
    }
    else
    {
        tetef.nombre_de_produit_total++;
        rewind(z);
        fwrite(&tetef, sizeof(tete), 1, z);
        fseek(z,-sizeof(block),SEEK_END);
        fread(&block_tmp,sizeof(block),1,z);
        block_tmp.produit[block_tmp.nombre_de_produit]=prodect;
        block_tmp.nombre_de_produit++;
        fseek(z,-sizeof(block),SEEK_END);
        fwrite(&block_tmp,sizeof(block),1,z);
    }

rewind(z);
fwrite(&tetef, sizeof(tete), 1, z);
printf("inisialement there is =====>%d block\n", tetef.nombre_de_block);
printf("inisialement there is =====>%d produit\n", tetef.nombre_de_produit_total);
    

    printf("insertion FINI\n");
    fclose(z);
}

void Oinserstion(char name[5], produit prodect)
{
int blokc,element;
blokc=0;
element=0;
if (O_recherche(name,prodect,&blokc,&element))
{printf("l element que vous vouler inserer existe deja");
return;}
z=fopen(name,"r+");
fread(&tetef,sizeof(tete),1,z);
if (tetef.nombre_de_produit_total%10==0)
    {   fseek(z,0,SEEK_END);
        fwrite(&block_tmp,sizeof(block),1,z);
        rewind(z);
        fread(&tetef,sizeof(tete),1,z);
        tetef.nombre_de_block++;
        tetef.nombre_de_produit_total++;
        fwrite(&tetef,sizeof(tete),1,z);
    }
for (int i = tetef.nombre_de_block-1; i > 0; i--)
    {
      
    }

    
}

void R_supristion(char name[5],produit prodect)
{
    int a,b;
    a=0;    
    b=0;
    if (!O_recherche(name,prodect,&a,&b))
    {
     printf("\nIT DOES NOT EXICTE   %ld!!!\n",prodect.id);
     return;
    } 
    z=fopen(name,"r+");
    fread(&tetef,sizeof(tete),1,z);
    if (tetef.nombre_de_produit_total%10==0)
    {
        tetef.nombre_de_block--;
    }
    tetef.nombre_de_produit_total--;
    if (tetef.nombre_de_produit_total==0)
    {printf("fichier fini !!");
     remove(name);
        return;}
    rewind(z);
    fwrite(&tetef,sizeof(tete),1,z);
    fseek(z,sizeof(tete)+sizeof(block)*(a-1),SEEK_SET);
    fread(&block_tmp,sizeof(block),1,z);
    block_tmp.produit[b]=emplacment(name,tetef.nombre_de_block,tetef.nombre_de_produit_total/10);
    fseek(z,sizeof(tete)+sizeof(block)*(a-1),SEEK_SET);
    fwrite(&block_tmp,sizeof(block),1,z);
   /* fseek(z,-sizeof(block),SEEK_END);
    fread(&block_tmp,sizeof(block),1,z);
    block_tmp.nombre_de_produit--;
    fseek(z,-sizeof(block),SEEK_END);
    fwrite(&block_tmp,sizeof(block),1,z);
*/

    
    
}
