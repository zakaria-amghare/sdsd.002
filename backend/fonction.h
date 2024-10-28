#include<stdbool.h>
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
FILE *z;
tete tetef;
block block_tmp;

void creation(char name[5])
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

void display(char name[5])
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
            printf("|name----> %c\t\t\tprix----> %d\n", block_tmp.produit[j].nom, block_tmp.produit[j].prix);
        }
            printf("____________________________");
            printf("____________________________\n");
            printf("____________________________");
            printf("____________________________\n");
        printf("\n\n");
    }
}

bool recherche(char name[5],produit prodect)
{
z=fopen(name,"r");
fread(&tetef, sizeof(tete), 1, z);
       for (int i = 0; i < tetef.nombre_de_block; i++)
       {
          fread(&block_tmp,sizeof(block),1,z);
          for (int j =0; j < block_tmp.nombre_de_produit;j++)
          {
             if (block_tmp.produit[j].nom==prodect.nom)
             {
              fclose(z);
              return true;
              printf("the prodect is here \nin block----->%d\nand it number----->%d",i,j+1);
             }
          }
       }
    fclose(z);
     printf("it does not exciste!!");
    return false;}

void R_inserstion(char name[5], produit prodect)
{
esp();
printf("\n\t\t\t\tinsertion\n");
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
    

    printf("\ninsertion FINI\n");
    esp();
    fclose(z);
}

void R_supristion(char name[5],produit prodect)
{
    if (!recherche(name,prodect))
    {
     printf("it does not exciste!!");
     return;
    } 
    z=fopen(name,"r+");
    
}

bool O_recherche (char name[5],produit prodect,int number_of_block,int number_of_emlement_in_block)
{
number_of_block=0;
number_of_emlement_in_block=0;
z=fopen(name,"r");
fseek(z,sizeof(tetef),SEEK_SET);
fread(&block_tmp,sizeof(block_tmp),1,z);
if (block_tmp.produit[0].prix>prodect.prix)
    {
        printf("\n\n\nthe prodect youre looking for does not exicte SO SORRY!!!!\nthe value is too small\n\n\n");
        fclose(z);
        for (int i = 0; i < 10; i++)
        {
            printf("\n\n--->>>%d",block_tmp.produit[i].prix);
        }
        return false;
    }


fseek(z,-sizeof(block_tmp),SEEK_END);
fread(&block_tmp,sizeof(block_tmp),1,z);
if (block_tmp.produit[block_tmp.nombre_de_produit-1].prix<prodect.prix)
    {
        printf("\n\n\nthe prodect youre %d looking for does not exicte SO SORRY!!!!\nthe value is too great than%d\n\n",prodect.prix,block_tmp.produit[block_tmp.nombre_de_produit-1].prix);
        fclose(z);
                for (int i = 0; i < block_tmp.nombre_de_produit; i++)
        {
            printf("\n\n--->>>%d",block_tmp.produit[i].prix);
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
           for (int i = 0; i < block_tmp.nombre_de_produit; i++)
           {
            printf("\n%d",block_tmp.produit[i].prix);
            if (prodect.prix==block_tmp.produit[i].prix)
                {
                    printf("BOENE INFER===>%d\nMOYENNE===>%d\nBOENE SUPPER===>%d\n",borne_infer,Moy,borne_super);
                    borne_infer=borne_super;
                    number_of_block=Moy;
                    number_of_emlement_in_block=i;
                } 
           }
    if (prodect.prix<block_tmp.produit[0].prix)
    {
        borne_super=Moy;
    }    
    
    if (prodect.prix>block_tmp.produit[9].prix)
    {
        borne_infer=Moy;
    }
    
     Moy=(borne_infer+borne_super)/2;      
}

printf("\nthe prodect must be in %d\n",Moy-1);
for (int i = 0; i < block_tmp.nombre_de_produit; i++)
           {
             printf("\n%d",block_tmp.produit[i].prix);
             if (prodect.prix==block_tmp.produit[i].prix)
                {
                    fclose(z);
                    return true;
                } 
           }
fclose(z);
return false;
}

void Oinserstion(char name[5], produit prodect)
{
z=fopen(name,"r+");
fread(&tetef,sizeof(tete),1,z);
if (tetef.nombre_de_produit_total%10==0)
    {   fseek(z,0,SEEK_END);
        fwrite(&block_tmp,sizeof(block),1,z);
    }
for (int i = tetef.nombre_de_block; i > 0; i--)
    {
        fseek(z,i*sizeof(block),SEEK_END);
    }

    
}

produit emplacment(char name[5],int number_of_block,int number_of_emlement_in_block)
{
    z=fopen(name,"r");
    fseek(z,sizeof(tete)+sizeof(block)*number_of_block,SEEK_SET);
    fread(&block_tmp,sizeof(block_tmp),1,z);
    return block_tmp.produit[number_of_emlement_in_block];
}
