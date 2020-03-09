// "Copyright [2018] <Tabirca Natalia-Mihaela>"
#include <stdio.h>
#include <math.h>

int main() {
        int n, i, nr_min = 0, nr_max = 0, lungime = 1, lungime_max = 0, ok = 0;
        float sum = 0, prod = 1, sum_p = 0, sum_inv = 0;
        float min = 10000000, max = -10000000;
        float x, xx, m_arit = 0, m_geom = 0, m_patr = 0, m_arm = 0, stdev = 0;
        scanf("%d", &n);
        scanf("%f", &xx); // citesc prima inregistrare separat
        for ( i = 1; i < n; i++ ) {
                x = xx; // creez o copie a inregistrarii anterioare
                if (x < 0) ok = 1; // verific daca avem termeni negativi
                sum += x; // suma numerelor citite
                prod *= x; // produsul numerelor citite
                sum_p += x*x; // suma patratelor
                sum_inv += 1./x; // suma inverselor
                // Aflu valoarea minima si numarul de aparitii
                if (x < min) {
                      nr_min = 1;
                      min = x;
                } else {
                        if (x == min) {
                              nr_min++;
                        }
                }
                // Aflu valoarea maxima si numarul de aparitii
                if (x > max) {
                        nr_max = 1;
                        max = x;
                } else {
                        if (x == max) {
                              nr_max++;
                        }
                }
                scanf("%f", &xx); // citim noua valoare
                // caut secvente crescatoare si calculez lungimile
                if (xx >= x) {
                      lungime++;
                } else {
                lungime = 1;
                }
                // aflu daca lungimea curenta devine lungime maxima
                if (lungime > lungime_max) {
                      lungime_max = lungime;
                }
        }
        // Aflu daca ultima valoare citita este maxima sau minima
        if (xx < min) {
              nr_min = 1;
              min = xx;
        } else {
                if (xx == min) {
                      nr_min++;
                }
        }
        if (xx > max) {
                nr_max = 1;
                max = xx;
        } else {
                if (xx == max) {
                      nr_max++;
                }
        }
        // se adauga in sume ultimul termen citit
        sum += xx;
        prod *= xx;
        sum_inv += 1./xx;
        sum_p += xx*xx;
        m_arit = sum/n;
        printf("%.4f\n", m_arit);
        if (ok) {
                printf("-\n");
        } else {
                m_geom = pow(prod, 1./n);
                printf("%.4f\n", m_geom);
        }
        m_arm = n/sum_inv;
        m_patr = sqrt(sum_p/n);
        float s =(sum_p-2*sum*m_arit)/n+m_arit*m_arit;
        if (s == 0)
                stdev = 0;
        else
                stdev = sqrt(s);
        printf("%.4f\n%.4f\n%.4f\n", m_arm, m_patr, stdev);
        printf("%.4f %d\n%.4f %d\n%d\n", min, nr_min, max, nr_max, lungime_max);
        return 0;
}
