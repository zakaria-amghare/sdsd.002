#include <stdio.h>
#include "fonction.h"
int main ()

{ 
int a,b;
produit pro;
creation("zaki");

for (int i = 0; i < 20; i++)
{   
  pro.nom='a';
  pro.id=i;
  R_inserstion("zaki",pro);

}
display("zaki");
    pro.id=15;
 // recherche("zaki",pro,&a,&b);
O_recherche("zaki",pro,&a,&b);
printf("\n|block %d--produit% d\n", a, b);

remove("zaki");
}