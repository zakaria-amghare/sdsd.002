#include <stdio.h>
#include "fonction.h"
int main ()

{ 
    produit pro;
    pro.nom='Z';
    pro.prix=999;
creation("zaki");

for (int i = 0; i < 200; i++)
{
    pro.prix=i;
    R_inserstion("zaki",pro);

}
display("zaki");
esp();
    pro.prix=33;

O_recherche("zaki",pro);
remove("zaki");
}