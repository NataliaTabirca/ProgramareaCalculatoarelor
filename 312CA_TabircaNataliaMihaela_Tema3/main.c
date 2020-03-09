// Copyright 2018 Tabirca Natalia-Mihaela
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct glaciar {
    int alt, dmg;
};

struct elf {
    char name[80];
    int x, y, hp, stamina, nr, elim, status, dmg;
};

// signature of functions
// alloc, read and free
void read_glaciar(struct glaciar **a, int n, FILE *f);
void read_elf(struct elf *s, struct glaciar **gl, int p, int n, int *in_game,
  FILE *f, FILE *g);
struct glaciar **alloc_matrix(int n);
void free_matrix(struct glaciar **gl, int n);
// move
int is_out(struct elf s, int n);
int minim(int a, int b);
void directions(struct elf *s, int i, char c, struct glaciar **gl, int n,
  int players, int *in_game, FILE *g);
void move(struct elf *s, int id, char c[], struct glaciar **gl, int n,
  int players, int *in_game, FILE *g);
// print_scoreboard
void swap_elf(struct elf *s1, struct elf *s2);
void copy_elf(struct elf *s, struct elf *cp, int player);
void print_scoreboard(struct elf *s, int players, FILE *g);
// meltdown
void meltdown(struct glaciar **gl, int n, struct elf *s, int players,
  int stam, int *in_game, FILE *g);
// snowstorm
void snowstorm(struct elf *s, int K, int players, int *in_game, FILE *g);
// read
void read_commands(struct elf *s, struct glaciar **gl, int n, int players,
  int *in_game, FILE *f, FILE *g);

int main() {
    FILE *f = fopen("snowfight.in", "rt");
    FILE *g = fopen("snowfight.out", "wt");
    int r, n, nn, players;
    struct glaciar **gl;
    struct elf *spiridus;
    fscanf(f, "%d%d", &r, &players);
    int in_game = players;
    n = r * 2 + 1;
    nn = n;
    gl = alloc_matrix(n); // alloc the matrix with the glacier
    read_glaciar(gl, n, f);
    spiridus = calloc (players, sizeof(struct elf)); // alloc space for players
    read_elf(spiridus, gl, players, n, &in_game, f, g);
    read_commands(spiridus, gl, n, players, &in_game, f, g);
    // free all space
    free_matrix(gl, nn);
    free(spiridus);
    fclose(f);
    fclose(g);
    return 0;
}

struct glaciar **alloc_matrix(int n) {
    int i;
    struct glaciar **gl;
    gl = malloc(n * sizeof(struct glaciar));
    if ( gl == NULL ) {
        return NULL;
    }
    for ( i = 0; i < n; i++ ) {
        gl[i] = calloc(n, sizeof(struct glaciar));
        if ( gl[i] == NULL ) {
            free(gl);
            return NULL;
        }
    }
    return gl;
}

void free_matrix(struct glaciar **gl, int n) {
    int i;
    for ( i = 0; i < n; i++ ) {
        free(*(gl+i));
    }
    free(gl);
}

int is_out(struct elf s, int n) {
    int r = n / 2;
    if ( (r - s.x) * (r - s.x) + (r - s.y) * (r - s.y) > r * r ) {
        return 1; // the elf is out of the glacier
    }
    if ( !( s.x >= 0 && s.y >= 0 && s.x < n && s.y < n ) )
        return 1;
    return 0;
}

void read_glaciar(struct glaciar **a, int n, FILE *f) {
    int i, j;
    for ( i = 0; i < n; i++ ) {
        for ( j = 0; j < n; j++ ) {
            fscanf(f, "%d%d", &a[i][j].alt, &a[i][j].dmg);
        }
    }
}

void read_elf(struct elf *s, struct glaciar **gl, int p, int n, int *in_game,
  FILE *f, FILE *g) {
    int i;
    for ( i = 0; i < p; i++ ) {
        fscanf(f, "%s%d%d%d%d", s[i].name, &s[i].x, &s[i].y, &s[i].hp,
          &s[i].stamina);
        s[i].nr = i;
        s[i].elim = 0; // this will count how many elfs each one eliminates
        s[i].status = 1; // dry/wet
        if ( is_out(s[i], n) == 1 ) {
            fprintf(g, "%s has missed the glacier.\n", s[i].name);
            s[i].status = 0;
            (*in_game)--;
        } else {
            s[i].dmg = gl[s[i].x][s[i].y].dmg;
            gl[s[i].x][s[i].y].dmg = 0;
        }
    }
}

int same_cell(struct elf s, struct elf *spiridus, int players) {
    int i;
    for ( i = 0; i <= players; i++ ) {
        if ( i != s.nr && s.x == spiridus[i].x &&
           s.y == spiridus[i].y && spiridus[i].status == 1 ) {
            return i;
        }
    }
    return -1;
}

int minim(int a, int b) {
    if ( a > b ) return b;
    return a;
}

void directions(struct elf *s, int i, char c, struct glaciar **gl, int n,
  int players, int *in_game, FILE *g) {
    int up = 0 , down = 0, left = 0, right = 0;
    // make sure the elf does not step out of the matrix
    if ( s[i].status == 1 && is_out(s[i], n) == 0 ) {
        if ( s[i].x > 0 )
            up = abs(gl[s[i].x][s[i].y].alt - gl[s[i].x - 1][s[i].y].alt);
        if ( s[i].x < n - 1 )
            down = abs(gl[s[i].x][s[i].y].alt - gl[s[i].x + 1][s[i].y].alt);
        if ( s[i].y > 0 )
            left = abs(gl[s[i].x][s[i].y].alt - gl[s[i].x][s[i].y - 1].alt);
        if ( s[i].y < n - 1 )
            right = abs(gl[s[i].x][s[i].y].alt - gl[s[i].x][s[i].y + 1].alt);
    }
    // modify the coordinates and stamina
    if ( c == 'U' && s[i].stamina >= up ) {
        s[i].x--, s[i].stamina -= up;
    }
    if ( c == 'D' && s[i].stamina >= down ) {
        s[i].x++, s[i].stamina -= down;
    }
    if ( c == 'L' && s[i].stamina >= left ) {
        s[i].y--, s[i].stamina -= left;
    }
    if ( c == 'R' && s[i].stamina >= right ) {
        s[i].y++, s[i].stamina -= right;
    }
    int aux;
    if ( is_out(s[i], n) == 0 ) {
        if ( s[i].dmg < gl[s[i].x][s[i].y].dmg ) {
                aux = s[i].dmg;
                s[i].dmg = gl[s[i].x][s[i].y].dmg;
                gl[s[i].x][s[i].y].dmg = aux;
            }
    }
    // verify if 2 elfs meet
    int k = same_cell(s[i], s, players), val = 0, first = 0, ok = 0;
    if ( s[i].status == 1  && k != -1 ) {
        if ( s[i].stamina >= s[k].stamina ) {
            s[k].hp -= s[i].dmg;
            first = 1;
        } else {
            s[i].hp -= s[k].dmg;
            first = 2;
        }
        // val = how many times to throw snowballs until one is almost wet
        val = minim(s[i].hp / s[k].dmg, s[k].hp / s[i].dmg);
        s[i].hp -= val * s[k].dmg;
        s[k].hp -= val * s[i].dmg;
        if ( s[i].hp == 0 || ( s[i].hp - s[k].dmg <= 0 &&
          s[k].hp - s[i].dmg > 0)) {
            fprintf(g, "%s sent %s back home.\n", s[k].name, s[i].name);
            s[k].stamina += s[i].stamina;
            s[i].stamina = 0;
            s[i].status = 0;
            s[k].elim++;
            ok = 1;
        }
        if ( s[k].hp == 0 || ( s[k].hp - s[i].dmg <= 0 &&
          s[i].hp - s[k].dmg > 0)) {
            fprintf(g, "%s sent %s back home.\n", s[i].name, s[k].name);
            s[i].stamina += s[k].stamina;
            s[k].stamina = 0;
            s[k].status = 0;
            s[i].elim++;
            ok = 1;
        }
        if ( s[i].hp - s[k].dmg <= 0 && s[k].hp - s[i].dmg <= 0  && ok == 0 ) {
            if ( first == 1 ) {
                fprintf(g, "%s sent %s back home.\n", s[k].name, s[i].name);
                s[k].stamina += s[i].stamina;
                s[i].stamina = 0;
                s[i].status = 0;
                s[k].elim++;
            } else {
                fprintf(g, "%s sent %s back home.\n", s[i].name, s[k].name);
                s[i].stamina += s[k].stamina;
                s[k].stamina = 0;
                s[k].status = 0;
                s[i].elim++;
            }
        }
        (*in_game)--;
    }
}

void move(struct elf *s, int id, char *str, struct glaciar **gl, int n,
  int players, int *in_game, FILE *g) {
    int i, lung = strlen(str);
    for ( i = 1; i < lung - 1; i++ ) {
        if ( s[id].status == 1 && is_out(s[id], n) == 0 ) {
            directions(s, id, str[i], gl, n, players, in_game, g);
            if ( is_out(s[id], n) ) {
                fprintf(g, "%s fell off the glacier.\n", s[id].name);
                s[id].status = 0;
                (*in_game)--;
                break;
            }
        }
    }
}

void swap_elf(struct elf *s1, struct elf *s2) {
    struct elf aux;
    aux.nr = s1->nr;
    s1->nr = s2->nr;
    s2->nr = aux.nr;
    aux.x = s1->x;
    s1->x = s2->x;
    s2->x = aux.x;
    aux.y = s1->y;
    s1->y = s2->y;
    s2->y = aux.y;
    aux.hp = s1->hp;
    s1->hp = s2->hp;
    s2->hp = aux.hp;
    aux.stamina = s1->stamina;
    s1->stamina = s2->stamina;
    s2->stamina = aux.stamina;
    aux.status = s1->status;
    s1->status = s2->status;
    s2->status = aux.status;
    aux.elim = s1->elim;
    s1->elim = s2->elim;
    s2->elim = aux.elim;
    strncpy(aux.name, s1->name, sizeof(s1->name));
    strncpy(s1->name, s2->name, sizeof(s2->name));
    strncpy(s2->name, aux.name, sizeof(aux.name));
}

void copy_elf(struct elf *s, struct elf *cp, int player) {
    int  i;
    for ( i = 0; i < player; i++ ) {
        cp[i].nr = s[i].nr;
        cp[i].x = s[i].x;
        cp[i].y = s[i].y;
        cp[i].hp = s[i].hp;
        cp[i].stamina = s[i].stamina;
        cp[i].status = s[i].status;
        cp[i].elim = s[i].elim;
        strncpy(cp[i].name, s[i].name, sizeof(s[i].name));
    }
}

void print_scoreboard(struct elf *s, int players, FILE *g) {
    int i, ok;
    fprintf(g, "SCOREBOARD:\n");
    do {
        ok = 0;
        for ( i = 0; i < players - 1; i++ ) {
            if ( s[i].status < s[i + 1].status ) {
                swap_elf(&s[i], &s[i + 1]);
                ok = 1;
            }
        }
    } while ( ok );

    do {
        ok = 0;
        for ( i = 0; i < players - 1; i++ ) {
          if ( s[i].elim < s[i + 1].elim && s[i].status == s[i + 1].status ) {
                swap_elf(&s[i], &s[i + 1]);
                ok = 1;
            }
        }
    } while ( ok );

    do {
        ok = 0;
        for ( i = 0; i < players - 1; i++ ) {
          if ( s[i].elim == s[i + 1].elim && s[i].status == s[i + 1].status ) {
                if ( strcmp(s[i].name, s[i + 1].name) > 0 ) {
                    swap_elf(&s[i], &s[i+1]);
                    ok = 1;
                }
            }
        }
    } while ( ok );

    for ( i = 0; i < players; i++ ) {
        fprintf(g, "%s\t", s[i].name);
        if ( s[i].status == 1)
            fprintf(g, "DRY");
        else
            fprintf(g, "WET");
        fprintf(g, "\t%d\n", s[i].elim);
    }
}

void meltdown(struct glaciar **gl, int n, struct elf *s, int players, int stam,
  int *in_game, FILE *g) {
    int i, j, R = n / 2 - 1;
    for ( i = 0; i < players; i++ ) {
        if ( s[i].status == 1  && is_out(s[i], n) == 0 ) {
            if ( (R - s[i].x + 1) * (R - s[i].x + 1) +
                             (R - s[i].y + 1) * (R - s[i].y + 1) > R * R ) {
              fprintf(g, "%s got wet because of global warming.\n", s[i].name);
              s[i].status = 0;
              (*in_game)--;
            } else {
                s[i].stamina += stam;
                if ( s[i].x > 0 && s[i].y > 0 ) {
                    s[i].x--;
                    s[i].y--;
                }
            }
        }
    }
    for ( i = 0; i < n - 2; i++ ) {
        for ( j = 0; j < n - 2; j++ ) {
            gl[i][j].alt = gl[i+1][j+1].alt;
            gl[i][j].dmg = gl[i+1][j+1].dmg;
        }
    }
}

void snowstorm(struct elf *s, int K, int players, int *in_game, FILE *g) {
    int X, Y, R, DMG, m, aux1, aux2, aux3, i;
    m = (1 << 8) - 1;
    X = K & m;
    aux1 = (K - X) >> 8;
    Y = aux1 & m;
    aux2 = (aux1 - Y) >> 8;
    R =  aux2 & m;
    aux3 = (aux2 - R) >> 8;
    DMG = aux3 & m;
    for ( i = 0; i < players; i++ ) {
    if ( (X - s[i].x) * (X - s[i].x) + (Y - s[i].y) * (Y - s[i].y) <= R * R ) {
            if ( s[i].status == 1 ) {
                s[i].hp -= DMG;
                if ( s[i].hp <= 0 ) {
                    s[i].status = 0;
                    (*in_game)--;
                    s[i].stamina = 0;
                    fprintf(g, "%s was hit by snowstorm.\n", s[i].name);
                }
            }
        }
    }
}

void read_commands(struct elf *s, struct glaciar **gl, int n, int players,
  int *in_game, FILE *f, FILE *g) {
    int id, k, stam, i;
    char *com, *dir;
    struct elf *cp;
    cp = calloc (players, sizeof(struct elf));
    com = calloc(20, sizeof(char));
    dir = calloc(20, sizeof(char));
    while ( fscanf(f, "%s", com) != EOF && (*in_game) > 1 ) {
        if ( strcmp(com, "MOVE") == 0 ) {
            fscanf(f, "%d", &id);
            fgets(dir, 100, f);
            if ( s[id].status == 1 )
                move(s, id, dir, gl, n, players, in_game, g);
        } else {
            if ( strcmp(com, "SNOWSTORM") == 0 ) {
                fscanf(f, "%d", &k);
                snowstorm(s, k, players, in_game, g);
            } else {
                if ( strcmp(com, "PRINT_SCOREBOARD") == 0 ) {
                    copy_elf(s, cp, players);
                    print_scoreboard(cp, players, g);
                } else {
                    if ( strcmp(com, "MELTDOWN") == 0 ) {
                        fscanf(f, "%d", &stam);
                        meltdown(gl, n, s, players, stam, in_game, g);
                        n -= 2;
                    }
                }
            }
        }
    }
    free(cp);
    free(com);
    free(dir);
    if ( (*in_game) == 1 ) {
        for ( i = 0; i < players; i++ ) {
            if ( s[i].status == 1 ) {
                fprintf(g, "%s has won.\n", s[i].name);
                break;
            }
        }
    }
}
