/*
  Desafio (nível novato): Batalha Naval básico
  - Tabuleiro 10x10 (0 = água)
  - 2 navios de tamanho 3 (valor 3): um horizontal e um vertical
  - Valida limites e evita sobreposição
  - Imprime o tabuleiro
*/

#include <stdio.h>

#define BOARD_SIZE 10
#define SHIP_SIZE  3
#define WATER      0
#define SHIP       3
#define HORIZONTAL 0
#define VERTICAL   1

/* zera o tabuleiro com 0 */
void zera_tabuleiro(int tab[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            tab[i][j] = WATER;
        }
    }
}

/* checa se o navio cabe dentro do 10x10 */
int cabe(int lin, int col, int orient) {
    if (lin < 0 || lin >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) return 0;
    if (orient == HORIZONTAL) {
        return (col + (SHIP_SIZE - 1) < BOARD_SIZE);
    } else { /* VERTICAL */
        return (lin + (SHIP_SIZE - 1) < BOARD_SIZE);
    }
}

/* checa se vai bater em outro navio (sobreposição) */
int sobrepoe(int tab[BOARD_SIZE][BOARD_SIZE], int lin, int col, int orient) {
    if (orient == HORIZONTAL) {
        for (int k = 0; k < SHIP_SIZE; k++) {
            if (tab[lin][col + k] != WATER) return 1;
        }
    } else { /* VERTICAL */
        for (int k = 0; k < SHIP_SIZE; k++) {
            if (tab[lin + k][col] != WATER) return 1;
        }
    }
    return 0;
}

/* coloca o navio copiando o valor 3 do vetor p/ a matriz */
void coloca(int tab[BOARD_SIZE][BOARD_SIZE], const int navio[SHIP_SIZE],
            int lin, int col, int orient) {
    if (orient == HORIZONTAL) {
        for (int k = 0; k < SHIP_SIZE; k++) tab[lin][col + k] = navio[k];
    } else { /* VERTICAL */
        for (int k = 0; k < SHIP_SIZE; k++) tab[lin + k][col] = navio[k];
    }
}

/* imprime a matriz com separadores (fica fácil de ver) */
void imprime(int tab[BOARD_SIZE][BOARD_SIZE]) {
    printf("\nTabuleiro (0=agua, 3=navio)\n\n   ");
    for (int c = 0; c < BOARD_SIZE; c++) printf("%d ", c);
    printf("\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%2d ", i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
        }
    printf("\n");
}

int main(void) {
    int tab[BOARD_SIZE][BOARD_SIZE];
    zera_tabuleiro(tab);

    /* navios como vetores 1D (cada célula vale 3) */
    int navio_h[SHIP_SIZE] = {SHIP, SHIP, SHIP};
    int navio_v[SHIP_SIZE] = {SHIP, SHIP, SHIP};

    /* coordenadas iniciais (mude aqui p/ testar)
       -> manter dentro do tabuleiro e sem sobreposição */
    int lin_h = 2, col_h = 1; /* horizontal começa em (2,1) */
    int lin_v = 5, col_v = 7; /* vertical   começa em (5,7) */

    /* valida e posiciona horizontal */
    if (!cabe(lin_h, col_h, HORIZONTAL)) {
        printf("ERRO: navio horizontal nao cabe em (%d,%d)\n", lin_h, col_h);
        return 1;
    }
    if (sobrepoe(tab, lin_h, col_h, HORIZONTAL)) {
        printf("ERRO: navio horizontal sobrepoe em (%d,%d)\n", lin_h, col_h);
        return 1;
    }
    coloca(tab, navio_h, lin_h, col_h, HORIZONTAL);

    /* valida e posiciona vertical */
    if (!cabe(lin_v, col_v, VERTICAL)) {
        printf("ERRO: navio vertical nao cabe em (%d,%d)\n", lin_v, col_v);
        return 1;
    }
    if (sobrepoe(tab, lin_v, col_v, VERTICAL)) {
        printf("ERRO: navio vertical sobrepoe em (%d,%d)\n", lin_v, col_v);
        return 1;
    }
    coloca(tab, navio_v, lin_v, col_v, VERTICAL);

    /* mostra resultado */
    imprime(tab);
    return 0;
}
