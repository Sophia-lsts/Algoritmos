#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define TAM 11 // Considera o '\0' final de cada string

char pal[5][TAM] = {"algoritmos", "quadrilhas", "cientistas", "rastreador", "computador"};
char tent[TAM] = "----------";

void desenho(int erro) { //erro como parâmetro para mostrar desenho conforme for aumentando
    switch(erro) {
        case 1:
            printf("-----|\n");
            printf("     O\n");
            break;
        case 2:
            printf("-----|\n");
            printf("     O\n");
            printf("     |\n");
            break;
        case 3:
            printf("-----|\n");
            printf("     O\n");
            printf("    /|\n");
            break;
        case 4:
            printf("-----|\n");
            printf("     O\n");
            printf("    /|\\\n");
            break;
        case 5:
            printf("-----|\n");
            printf("     O\n");
            printf("    /|\\\n");
            printf("    / \n");
            break;
        case 6:
            printf("-----|\n");
            printf("     O\n");
            printf("    /|\\\n");
            printf("    / \\\n");
            break;
        default:
            printf("-----|\n");
            break;
    }
}

void jogar() {
    srand(time(NULL)); // permite o uso da função rand
    char c;
    char word[TAM]; // guarda a string da palavra escolhida
    int i, encontrou;
    int tentativas = 6;
    int erro = 0;

    strcpy(word, pal[rand() % 5]); // copia a palavra do índice gerado em word
    strcpy(tent, "----------"); // reseta o tent para um novo jogo

    do {
        system("clear");
        desenho(erro);
        printf("Sua palavra está assim: %s\n", tent);
        printf("\nDigite um caractere:\n");
        scanf(" %c", &c); // o espaço antes do %c exclui o '\n' de quando digitar o caractere

        encontrou = 0;

        for (i = 0; i < TAM - 1; i++) {
            if (word[i] == '\0') // chegou ao final da string
                break; // para de contar e verificar
            if (c == word[i]) {
                encontrou = 1;
                tent[i] = c;
            }
        }

        if (encontrou) {
            printf("Sua letra foi encontrada, e sua palavra ficou assim: %s\n", tent);
        } else {
            erro += 1;
            tentativas = 6 - erro;
            printf("Sua letra não foi encontrada.\n");
            printf("Você tem mais %d tentativas.\n", tentativas);
        }

    } while ((strcmp(word, tent) != 0) && erro < 6);

    if (strcmp(word, tent) == 0) {
        printf("Você achou todas as letras, parabéns!\n");
        printf("Sua palavra era: %s\n", tent);
    } else {
        printf("Você perdeu :(\n");
        printf("A palavra correta era: %s\n", word);
    }
}

int main() {
    char restart;
    do {
        jogar(); //a partida toda é chamada aqui e se encerra depois de uma vez
        printf("Deseja jogar novamente? (s/n): \n");
        scanf(" %c", &restart); // lê o que o usuário quer
    } while (restart == 's' || restart == 'S'); // se sim, continua loop 
    printf("Obrigada por jogar!\n"); //se não, encerra
    return 0;
}
