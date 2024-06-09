#include <stdio.h>
#include <stdlib.h>
#include <locale.h> //necessário para usar setlocale e colocar a linguagem
#define TAM 3

char M[TAM][TAM];
int vence();
void preenche(); //preenche tudo com espaços
void jogada(); //declara função que capta e faz a jogada, usando linha e coluna
void printMatriz(); //imprime a matriz
int BuscarNumero(); //busca se a posição está ocupada
int col = 0, lin = 0;
char n; // a jogada deve ser global ou passada de outra forma

int main() {
    int i = 0;

    setlocale(LC_ALL, "Portuguese");
    preenche();
    while (i < 9 && !vence()) {
        printMatriz();
        printf("\n");
        jogada();
        system("clear");
        if (vence()) {
            printf("\nParabéns! Você venceu!\n");
            break;
        }
        i++;
    }

    if (i >= 9 && !vence()) {
        printf("\nEmpate!\n");
    }

    return 0;
}

void preenche() {
    int i, j;
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            M[i][j] = ' ';
        }
    }
}

void printMatriz() {
    int i, j;
    printf("    0   1   2\n");
    for (i = 0; i < TAM; i++) {
        printf(" %d ", i);
        for (j = 0; j < TAM; j++) {
            printf(" %c ", M[i][j]);
            if (j < TAM - 1) printf("|");
        }
        printf("\n");
        if (i < TAM - 1) {
            printf("   ---|---|---\n");
        }
    }
}

int BuscarNumero() {
    if (M[lin][col] != ' ') {
        return 1;
    }
    return 0;
}

void jogada() {
    do {
        printf("Digite a linha em que quer jogar:\n");
        scanf("%d", &lin);
        printf("Digite a coluna em que quer jogar:\n");
        scanf("%d", &col);
        if (lin < 0 || lin >= TAM || col < 0 || col >= TAM) {
            printf("Jogada não permitida!! \n");
        }
        else if (BuscarNumero() == 1) {
            printf("Esse lugar já está ocupado, digite outro.\n");
        }
    } while (lin < 0 || lin >= TAM || col < 0 || col >= TAM || BuscarNumero() == 1);

    printf("Digite X ou O: ");
    scanf(" %c", &n); // leio a jogada
    M[lin][col] = n;
}

int vence() {
    int i, j;

    // verificar vertificais e horizontais
    for (i = 0; i < 3; i++) {
        if (M[i][0] == M[i][1] && M[i][1] == M[i][2] && M[i][0] != ' ') {
            return 1;
        }
        if (M[0][i] == M[1][i] && M[1][i] == M[2][i] && M[0][i] != ' ') {
            return 1;
        }
    }

    //verificar diagonais
    if ((M[0][0] == M[1][1] && M[1][1] == M[2][2] && M[0][0] != ' ') ||
        (M[0][2] == M[1][1] && M[1][1] == M[2][0] && M[0][2] != ' ')) {
        return 1;
    }

    return 0;
}
