// Copyright 2018 Tabirca Natalia-Mihaela
#include <stdio.h>
#include <math.h>

void afis(int , int , int); // functie de afisare a unei linii de . si *
// afisarea tuturor liniilor
void afisare(int , int, int, int, int, int, int , int , int, int, int, int,
  int, int, int, int, int, int, int, int, int, int);
// afisarea codului
void afisare_cod(int, int, int, int, int, int, int, int, int, int,  int, int);
int main() {
    int n, i, nn = 0, cod, scala, ep, viz;
    int cod1, cod2, cod3, cod4, cod5, cod6, cod7, cod8, cod9, cod0, scala0;
    int scala1, scala2, scala3, scala4, scala5, scala6, scala7, scala8, scala9;
    cod1 = cod2 = cod3 = cod4 = cod5 = -1;
    cod6 = cod7 = cod8 = cod9 = cod0 = -1;
    scanf("%d", &n);
    for ( i = 1; i <= n; ++i ) {
        scanf("%d%d%d", &cod, &viz, &ep); // cit. un cod, nr ep viz, nr ep tot
        scala = round(((float) viz/ep)*10); // calculez scala
        // copiez codul citit si scala in variabilele corespunzatoare
        if ( cod == 1 ) {
            cod1 = cod;
            scala1 = scala;
        }
        if ( cod == 2 ) {
                cod2 = cod;
                scala2 = scala;
        }
        if ( cod == 3 ) {
                cod3 = cod;
                scala3 = scala;
        }
        if ( cod == 4 ) {
                cod4 = cod;
                scala4 = scala;
        }
        if ( cod == 5 ) {
                cod5 = cod;
                scala5 = scala;
        }
        if ( cod == 6 ) {
                cod6 = cod;
                scala6 = scala;
        }
        if ( cod == 7 ) {
                cod7 = cod;
                scala7 = scala;
        }
        if ( cod == 8 ) {
                cod8 = cod;
                scala8 = scala;
        }
        if ( cod == 9 ) {
                cod9 = cod;
                scala9 = scala;
        }
        if ( cod == 0 ) {
                cod0 = cod;
                scala0 = scala;
        }
    }
    afisare(n, nn, cod0, scala0, cod1, scala1, cod2, scala2, cod3, scala3,
     cod4, scala4, cod5, scala5, cod6, scala6, cod7, scala7, cod8, scala8,
     cod9, scala9);
    afisare_cod(n, nn, cod0, cod1, cod2, cod3, cod4, cod5,
     cod6, cod7, cod8, cod9);
    printf("\n");
    return 0;
}

void afis(int a, int b, int c) {
    if ( a != -1 ) {
        if ( b >= c )
                printf("*");
        else
                printf(".");
    }
}

void afisare(int n, int nn, int cod0, int scala0, int cod1, int scala1,
  int cod2, int scala2, int cod3, int scala3, int cod4, int scala4,
  int cod5, int scala5, int cod6, int scala6, int cod7, int scala7,
  int cod8, int scala8, int cod9, int scala9) {
    int i;
    // afiser linie cu linie . sau * pentru fiecare serial
    nn = n;
    for ( i = 10; i >= 1; --i ) {
        nn = n-1;
        afis(cod0, scala0, i);
        if ( nn && cod0 != -1 ) {
            printf(" ");
            nn--;
        }
        afis(cod1, scala1, i);
        if ( nn && cod1 != -1 ) {
            printf(" ");
            nn--;
        }
        afis(cod2, scala2, i);
        if ( nn && cod2 != -1 ) {
            printf(" ");
            nn--;
        }
        afis(cod3, scala3, i);
        if ( nn && cod3 != -1 ) {
            printf(" ");
            nn--;
        }
        afis(cod4, scala4, i);
        if ( nn && cod4 != -1 ) {
            printf(" ");
            nn--;
        }
        afis(cod5, scala5, i);
        if ( nn && cod5 != -1 ) {
            printf(" ");
            nn--;
        }
        afis(cod6, scala6, i);
        if ( nn && cod6 != -1 ) {
            printf(" ");
            nn--;
        }
        afis(cod7, scala7, i);
        if ( nn && cod7 != -1 ) {
            printf(" ");
            nn--;
        }
        afis(cod8, scala8, i);
        if ( nn && cod8 != -1 ) {
            printf(" ");
            nn--;
        }
        afis(cod9, scala9, i);
        printf("\n");
    }
}

void afisare_cod(int n, int nn, int cod0, int cod1, int cod2, int cod3,
  int cod4, int cod5, int cod6, int cod7,  int cod8, int cod9) {
    // afisez codul corespunzator serialelor din histograma
    nn = n-1;
    if ( cod0 != -1 ) {
        printf("0");
        if ( nn ) {
            printf(" ");
            nn--;
        }
    }
    if ( cod1 != -1 ) {
        printf("1");
        if ( nn ) {
            printf(" ");
            nn--;
        }
    }
    if ( cod2 != -1 ) {
        printf("2");
        if ( nn ) {
            printf(" ");
            nn--;
        }
    }
    if ( cod3 != -1 ) {
        printf("3");
        if ( nn ) {
            printf(" ");
            nn--;
        }
    }
    if ( cod4 != -1 ) {
        printf("4");
        if ( nn ) {
            printf(" ");
            nn--;
        }
    }
    if ( cod5 != -1 ) {
        printf("5");
        if ( nn ) {
            printf(" ");
            nn--;
        }
    }
    if ( cod6 != -1 ) {
        printf("6");
        if ( nn ) {
            printf(" ");
            nn--;
        }
    }
    if ( cod7 != -1 ) {
        printf("7");
        if ( nn ) {
            printf(" ");
            nn--;
        }
    }
    if ( cod8 != -1 ) {
        printf("8");
        if ( nn ) {
            printf(" ");
            nn--;
        }
    }
    if ( cod9 != -1 )
        printf("9");
}
