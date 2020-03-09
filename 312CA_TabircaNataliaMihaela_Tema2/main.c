// Copyright 2018 TABIRCA NATALIA-MIHAELA
#include <stdio.h>
#include <string.h>
#define N 100

// functii task 1
void init_mat(int n, int a[][N]); // initializarea matricei cu o val dif de X/0
int valid(int x, int y, int a[][N], char p[], int i, int n); // verif mutare
void completare(int a[][N], int n, int macro[][N], char p, int x, int y,
    int *, int *); // completez matricea cu 0 sau 1
void completare_automata(int a[][N], int macro[][N], char p, int n, int ok);
int is_full(int a[][N], int n);
void task_1(int n, int m, char player[], int x, int y, int a[][N],
    int *nr_x, int *nr_0, int *, int*, int macro[][N]);

// functii task 2
int castigator(int a[][N], int n, int x, int y); // castigator microboard
void task_2(int macro[][N], int n);

// functii task 3
void task_3(int nr_x, int nr_o, int, int);

int main() {
    int n, m, a[N][N], macro[N][N], x = 0, y = 0, nr_x, nr_0;
    int x_win = 0, o_win = 0;
    char player[1000000];
    scanf("%d%d", &n, &m);
    init_mat(n, macro);
    task_1(n, m, player, x, y, a, &nr_x, &nr_0, &x_win, &o_win, macro);
    task_2(macro, n);
    task_3(nr_x, nr_0, x_win, o_win);
    // printf("\n");
    return 0;
}

// task1

void init_mat(int n, int a[][N]) {
    int i, j;
    for ( i = 0; i < n*n ; i++ ) {
        for ( j = 0; j < n*n ; j++ ) {
            a[i][j] = -1;
        }
    }
}

int valid(int x, int y, int a[][N], char p[], int i, int n) {
    if ( p[i-1] == p[i] ) {
        return -2; // cod eroare pentru "NOT YOUR TURN"
    }
    if ( x < 0 || x >= n*n || y < 0 || y >= n*n ) {
        return -1; // cod eroare pentru "INVALID INDEX"
    }
    if ( a[x][y] != -1 ) {
        return 0; // cod eroare pentru "NOT AN EMPTY CELL"
    }
    return 1; // MUTAREA ESTE VALIDA
}

void completare(int a[][N], int n, int macro[][N], char p, int x, int y,
  int *x_win, int *o_win) {
    if ( p == 'X' ) {
        a[x][y] = 1;
        if ( macro[x/n][y/n] == -1 && castigator(a, n, (x/n), (y/n)) == 1 ) {
            (*x_win)++;
            macro[x/n][y/n] = castigator(a, n, (x/n), (y/n));
        }
    } else {
        a[x][y] = 0;
        if ( macro[x/n][y/n] == -1 && castigator(a, n, (x/n), (y/n)) == 0 ) {
            (*o_win)++;
            macro[x/n][y/n] = castigator(a, n, (x/n), (y/n));
        }
    }
}

void completare_automata(int a[][N], int macro[][N], char p, int n, int ok ) {
    int i, j;
    ok = 0;
    for ( i = 0; i < n*n ; i++ ) {
        if ( a[i][i] == -1 ) {
            if ( p == 'X' ) {
                a[i][i] = 1;
                if ( macro[i/n][i/n] == -1 ) {
                  if ( castigator(a, n, (i/n), (i/n)) == 1 ) {
                    macro[i/n][i/n] = castigator(a, n, (i/n), (i/n));
                  }
                }
            } else {
                a[i][i] = 0;
                if ( macro[i/n][i/n] == -1 ) {
                  if ( !castigator(a, n, (i/n), (i/n) ) ) {
                    macro[i/n][i/n] = castigator(a, n, (i/n), (i/n));
                  }
                }
            }
            ok = 1;
            return;
        }
    }
    if ( ok == 0 ) {   // daca inca nu a fost completata valoarea
        for ( j = 1; j < n*n; j++ ) {
            for ( i = 0; i < n*n - j ; i++ ) {
                if ( a[i][i+j] == -1 ) {
                    if ( p == 'X' ) {
                     a[i][i+j] = 1;
                     if ( macro[i/n][(i+j)/n] == -1 ) {
                      if ( castigator(a, n, (i/n), ((i+j)/n)) == 1 ) {
                       macro[i/n][(i+j)/n] = castigator(a, n, (i/n), ((i+j)/n));
                      }
                     }
                    } else {
                     a[i][i+j] = 0;
                     if ( macro[i/n][(i+j)/n] == -1 ) {
                      if ( castigator(a, n, (i/n), ((i+j)/n)) == 0 ) {
                       macro[i/n][(i+j)/n] = castigator(a, n, (i/n), ((i+j)/n));
                      }
                     }
                    }
                    ok = 1;
                    return;
                }
            }
            for ( i = 0; i < n*n - j ; i++ ) {
                if ( a[i+j][i] == -1 ) {
                    if ( p == 'X' ) {
                     a[i+j][i] = 1;
                     if ( macro[(i+j)/n][i/n] == -1 ) {
                      if ( castigator(a, n, ((i+j)/n), (i/n)) == 1 ) {
                      macro[(i+j)/n][i/n] = castigator(a, n, ((i+j)/n), (i/n));
                      }
                     }
                    } else {
                     a[i+j][i] = 0;
                     if ( macro[(i+j)/n][i/n] == -1 ) {
                      if ( castigator(a, n, ((i+j)/n), (i/n)) == 0 ) {
                      macro[(i+j)/n][i/n] = castigator(a, n, ((i+j)/n), (i/n));
                      }
                     }
                    }
                    ok = 1;
                    return;
                }
            }
        }
    }
}

void afis_task_1(int x, int y, int a[][N], int macro[][N], char p[],
  int i, int n) {
    int ok = 0;
    if ( valid(x, y, a, p, i, n) == -2 ) {
        printf("NOT YOUR TURN\n");
    }
    if ( valid(x, y, a, p, i, n) == -1 ) {
        printf("INVALID INDEX\n");
        completare_automata(a, macro, p[i], n, ok);
    }
    if ( valid(x, y, a, p, i, n) == 0 ) {
        printf("NOT AN EMPTY CELL\n");
        completare_automata(a, macro, p[i], n, ok);
    }
}

int is_full(int a[][N], int n) {
    int j, i, nr = 0;
    for ( i = 0; i < n*n; i++ ) {
        for ( j = 0; j < n*n; j++ ) {
            if ( a[i][j] == -1 )
                nr++;
        }
    }
    return nr;
}

void task_1(int n, int m, char player[], int x, int y, int a[][N],
            int *nr_x, int *nr_0, int *x_win, int *y_win, int macro[][N]) {
    int i, k;
    init_mat(n, a);
    k = 0;
    int ok = 1;
    while ( ok ) {
        scanf(" %c%d%d", &player[k], &x, &y);
        if ( player[k] == '0' ) {
            printf("NOT YOUR TURN\n");
        } else {
            ok = 0;
        }
        k++;
    }
    if ( valid(x, y, a, player, k-1, n) == 1 ) {
        completare(a, n, macro, player[k-1], x, y, x_win, y_win);
        if ( player[k-1] == 'X' ) {
            (*nr_x)++;
        } else {
            (*nr_0)++;
        }
    } else {
        if ( valid(x, y, a, player, k-1, n) == -1 ) {
            afis_task_1(x, y, a, macro, player, k-1, n);
            if ( valid(x, y, a, player, k-1, n) == -1 ) {
                if ( player[k-1] == 'X' ) {
                    (*nr_x)++;
                } else {
                    (*nr_0)++;
                }
            }
        }
    }
    for ( i = k; i < m; i++ ) {
        scanf(" %c%d%d", &player[i], &x, &y);
        if ( is_full(a, n) == 0 ) {
            if ( valid(x, y, a, player, i, n) == 0 ) {
                printf("NOT AN EMPTY CELL\n");
            }
            if ( valid(x, y, a, player, i, n) == -1 ) {
                printf("INVALID INDEX\n");
            }
            printf("FULL BOARD\n");
            return;
        }
        if ( valid(x, y, a, player, i, n) == 1 ) {
            completare(a, n, macro, player[i], x, y, x_win, y_win);
            if ( player[i] == 'X' ) {
                (*nr_x)++;
            } else {
                (*nr_0)++;
            }
        } else {
            afis_task_1(x, y, a, macro, player, i, n);
            if ( valid(x, y, a, player, i, n) == 0 ) {
                if ( player[i] == 'X' ) {
                    (*nr_x)++;
                } else {
                    (*nr_0)++;
                }
            }
            if ( valid(x, y, a, player, i, n) == -1 ) {
                if ( player[i] == 'X' ) {
                    (*nr_x)++;
                } else {
                    (*nr_0)++;
                }
            }
        }
    }
}

// task2

int castigator(int a[][N], int n, int x, int y) {
    int v[2]= {0}, i, j;
    // verific daca exista vreo linie castigatoare
    for ( i = n*x; i < n*(x + 1); i++ ) {
        v[0] = v[1] = 0;
        for ( j = n*y; j < n*(y + 1); j++ ) {
            if ( a[i][j] == 0 ) {
                v[0]++;
            } else {
                if ( a[i][j] == 1 ) {
                    v[1]++;
                }
            }
        }
        if ( v[0] == n ) {
            return 0;
        } else {
            if ( v[1] == n )
                return 1;
        }
    }
    // verific daca exista vreo coloana castigatoare
    for ( j = n*y; j < n*(y + 1); j++ ) {
        v[0] = v[1] = 0;
        for ( i = n*x; i < n*(x + 1); i++ ) {
            if ( a[i][j] == 0 ) {
                v[0]++;
            } else {
                if ( a[i][j] == 1 ) {
                    v[1]++;
                }
            }
        }
        if ( v[0] == n ) {
            return 0;
        } else {
            if ( v[1] == n )
                return 1;
        }
    }
    // verific diagonala principala
    v[0] = v[1] = 0;
    for ( i = n * x, j = n * y; i < n*(x + 1) && j < n*(y + 1); i++, j++ ) {
        if ( a[i][j] == 0 ) {
            v[0]++;
        } else {
            if ( a[i][j] == 1 ) {
                v[1]++;
            }
        }
    }
    if ( v[0] == n ) {
        return 0;
    } else {
        if ( v[1] == n )
            return 1;
    }
    // verific diagonala secundara
    v[0] = v[1] = 0;
    for ( i = n*x, j = n*(y + 1) - 1; i < n*(x + 1); i++, j-- ) {
        if ( a[i][j] == 0 ) {
            v[0]++;
        } else {
            if ( a[i][j] == 1 ) {
                v[1]++;
            }
        }
    }
    if ( v[0] == n ) {
        return 0;
    } else {
        if ( v[1] == n )
            return 1;
    }
    return -1;
}



void task_2(int macro[][N], int n) {
    int i, j, v[2] = {0}, x = 0, o = 0;
    // afisarea macro - ului
    for ( i = 0; i < n; i++ ) {
        for ( j = 0; j < n; j++ ) {
            if ( macro[i][j] == 0 )
                printf("%d", 0);
            else if ( macro[i][j] == 1 )
                printf("%c", 'X');
            else
                printf("%c", '-');
        }
        printf("\n");
    }
    for ( i = 0; i < n; i++ ) {
        if ( macro[i][i] == 1 ) {
            v[1]++;
        } else {
            if ( macro[i][i] == 0 ) {
                v[0]++;
            }
        }
    }
    if ( v[1] == n )
        x++;
    if ( v[0] == n )
        o++;
    v[0] = v[1] = 0;
    for ( i = 0; i < n; i++ ) {
        if ( macro[i][n - i -1] == 1 ) {
            v[1]++;
        } else {
            if ( macro[i][n - i -1] == 0 ) {
                v[0]++;
            }
        }
    }
    if ( v[1] == n )
        x++;
    if ( v[0] == n )
        o++;
    for ( i = 0; i < n; i++ ) {
        v[0] = v[1] = 0;
        for ( j = 0; j < n; j++ ) {
            if ( macro[i][j] == 1 ) {
                v[1]++;
            } else {
                if ( macro[i][j] == 0 ) {
                    v[0]++;
            }
        }
        if ( v[1] == n )
            x++;
        if ( v[0] == n )
            o++;
        }
    }
    for ( i = 0; i < n; i++ ) {
        v[0] = v[1] = 0;
        for ( j = 0; j < n; j++ ) {
            if ( macro[j][i] == 1 ) {
                v[1]++;
            } else {
                if ( macro[j][i] == 0 ) {
                    v[0]++;
            }
        }
        if ( v[1] == n )
            x++;
        if ( v[0] == n )
            o++;
        }
    }
    if ( x == o ) {
        printf("Draw again! Let's play darts!\n");
    } else {
        if ( x > o ) {
            printf("X won\n");
        } else {
            printf("0 won\n");
        }
    }
}


void task_3(int nr_x, int nr_o, int x_win, int o_win) {
    if ( nr_x == 0 ) {
            printf("X N/A\n");
    } else {
        printf("X %.10lf\n", (double) x_win / nr_x);
    }
    if ( nr_o == 0 ) {
            printf("0 N/A\n");
    } else {
        printf("0 %.10lf\n", (double) o_win / nr_o);
    }
}
