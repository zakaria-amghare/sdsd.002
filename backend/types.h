#include<stdio.h>
#include<stdlib.h>
typedef struct produit
{
char nom[20];
int prix;

}produit;

typedef struct block
{produit produit[10];
int nb_p;
 
}block;

typedef struct tete
{
int nb_p_t;
int nb_b;
}tete;

