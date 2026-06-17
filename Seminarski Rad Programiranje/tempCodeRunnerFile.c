#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char tabla[9];
char igrac = 'X', bot = 'O';

void napraviTablu() {
    for (int i = 0; i < 9; i++) tabla[i] = '0' + i;
}

void prikaziTablu() {
    printf("\n");
    printf(" %c | %c | %c \n", tabla[0], tabla[1], tabla[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", tabla[3], tabla[4], tabla[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", tabla[6], tabla[7], tabla[8]);
    printf("\n");
}

int proveraPobede(char simbol) {
    int kombinacije[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    for (int i = 0; i < 8; i++) {
        int broj = 0, slobodno = -1;
        for (int j = 0; j < 3; j++) {
            if (tabla[kombinacije[i][j]] == simbol) broj++;
            if (tabla[kombinacije[i][j]] != 'X' && tabla[kombinacije[i][j]] != 'O') slobodno = kombinacije[i][j];
        }
        if (broj == 2 && slobodno != -1) return slobodno;
    }
    return -1;
}

int nereseno() {
    for (int i = 0; i < 9; i++) if (tabla[i] != 'X' && tabla[i] != 'O') return 0;
    return 1;
}

int suprotniUglovi() {
    if (tabla[0] == 'X' && tabla[8] == 'X') return 1;
    if (tabla[2] == 'X' && tabla[6] == 'X') return 1;
    return 0;
}

void botPotez(int zadnjiPotez) {
    int potez = -1;

    potez = proveraPobede(bot);
    if (potez != -1) { tabla[potez] = bot; return; }

    potez = proveraPobede(igrac);
    if (potez != -1) { tabla[potez] = bot; return; }

    int uglovi[4] = {0, 2, 6, 8};
    for (int i = 0; i < 4; i++) {
        if (zadnjiPotez == uglovi[i] && tabla[4] != 'X' && tabla[4] != 'O') {
            tabla[4] = bot;
            return;
        }
    }

    if (suprotniUglovi()) {
        int strane[4] = {1, 3, 5, 7};
        for (int i = 0; i < 4; i++) {
            if (tabla[strane[i]] != 'X' && tabla[strane[i]] != 'O') {
                tabla[strane[i]] = bot;
                return;
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        int suprotni = 8 - uglovi[i];
        if (tabla[uglovi[i]] != 'X' && tabla[uglovi[i]] != 'O' &&
            tabla[suprotni] != 'X' && tabla[suprotni] != 'O') {
            tabla[suprotni] = bot;
            return;
        }
    }

    for (int i = 0; i < 4; i++) {
        if (tabla[uglovi[i]] != 'X' && tabla[uglovi[i]] != 'O') { tabla[uglovi[i]] = bot; return; }
    }

    if (tabla[4] != 'X' && tabla[4] != 'O') { tabla[4] = bot; return; }

    int strane[4] = {1, 3, 5, 7};
    for (int i = 0; i < 4; i++) {
        if (tabla[strane[i]] != 'X' && tabla[strane[i]] != 'O') { tabla[strane[i]] = bot; return; }
    }
}

int main() {
    int potez;
    napraviTablu();
    prikaziTablu();

    int linije[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};

    while (1) {
        printf("Unesite vas potez (0-8): ");
        scanf("%d", &potez);

        if (potez < 0 || potez > 8 || tabla[potez] == 'X' || tabla[potez] == 'O') {
            printf("Nevalidan potez!\n");
            continue;
        }
        tabla[potez] = igrac;

        for (int i = 0; i < 8; i++) {
            if (tabla[linije[i][0]] == igrac && tabla[linije[i][1]] == igrac && tabla[linije[i][2]] == igrac) {
                prikaziTablu();
                printf("Pobedili ste!\n");
                return 0;
            }
        }

        if (nereseno()) { prikaziTablu(); printf("Nereseno!\n"); return 0; }

        botPotez(potez);
        prikaziTablu();

        for (int i = 0; i < 8; i++) {
            if (tabla[linije[i][0]] == bot && tabla[linije[i][1]] == bot && tabla[linije[i][2]] == bot) {
                printf("Bot pobeduje!\n");
                return 0;
            }
        }

        if (nereseno()) { printf("Nereseno!\n"); return 0; }
    }

    return 0;
}