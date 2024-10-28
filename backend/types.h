#include<stdio.h>
#include<stdlib.h>
typedef struct produit
{
char nom;
int prix;

}produit;

typedef struct block
{produit produit[10];
int nombre_de_produit;
 
}block;

typedef struct tete
{
int nombre_de_produit_total;
int nombre_de_block;
}tete;


void esp() 
{
    printf("*********---------------------------------------------------------------*********\n");
    printf("*********---------------------------------------------------------------*********\n");
    printf("*********---------------------------------------------------------------*********\n");
    printf("*********---------------------------------------------------------------*********\n");
    printf("*********---------------------------------------------------------------*********\n");
}
