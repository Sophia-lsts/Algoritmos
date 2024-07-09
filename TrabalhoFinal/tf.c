#include <stdio.h>
#include <stdlib.h>
#include <time.h> //possibilidade o uso de srand(time(NULL)) e rand()
#include <locale.h>
#define TAM 6
#define RESET "\033[0m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define GREEN "\033[32m" // cores

float M[TAM][TAM]; //criação da matriz em float para realização de operações de divisões
int lin1, col1, lin2, col2; //variáveis para seleção dos 2 números na matriz
int color1,color2,sum; //estão com escopo global porque vão ser usadas em funções diferentes(show e colors), e são índices só para colorir mesmo e não atrapalhar com i e j
int tent = 24, erro = 0, acertos = 0; 
int mais = 0, menos = 0, vezes = 0, divide = 0; // contadores para as operações
char segue = 's'; //char segue tá definido com 's' e só se altera caso receba um valor diferente no decorrer do código, para sinalizar se continua o jogo ou não

void limpaTela() { // função para limpar a tela se adaptar com o sistema
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void menu() { 
    char start;

    printf(GREEN "Seja bem-vindo!\n" RESET);
    printf(GREEN "-----COMO JOGAR-----\n" RESET);
    printf(GREEN "1. A matriz tem 36 células, a cada rodada, você irá escolher duas, com base na sua posição em linha e coluna.\n" RESET);
    printf(GREEN "2. Depois disso, você pode escolher qual operação quer realizar, PORÉM você só pode selecionar uma mesma operação no máximo 5 vezes.\n" RESET);
    printf(GREEN "3. Como os cálculos serão realizados entre 2 números, você deverá acertar 18 vezes para ganhar o jogo.\n" RESET);
    printf(GREEN "4. Você pode tentar uma resposta mais de uma vez e, a partir da 3ª vez, você liberará a opção de pedir resposta.\n" RESET);
    printf(GREEN "5. Cuidado! Você tem, no total, 24 tentativas para tentar fechar o jogo.\n" RESET);
    printf(GREEN "Deseja começar? Digite 's' se sim ou qualquer tecla se não:\n" RESET);
    scanf(" %c", &start);
    if (start == 's' || start == 'S') //start só vai ser usada aqui no menu() mesmo então não precisa de escopo global
        limpaTela(); //limpa o menu, só aparece quando inicializa o código
    else
        exit(0); //fecha o código direto
}

void preenche() {
    srand(time(NULL)); //possibilita o uso de rand() para gerar números aleatórios
    int i, j;

    for (i = 0; i < TAM; i++)
        for (j = 0; j < TAM; j++)
            M[i][j] = ((rand() % 9) + 1); //rand() % 9 gera restos até 8, +1 porque não quero o número 0 e precisa ser até 9
}

void colors(){ // lógica para deixar as diagonais com as mesmas cores revezando

    switch(sum){ //nas diagonais, a soma do índice e coluna é o mesmo, substitui essa soma para printar os números das diagonais coloridos
        case 0:
            printf(CYAN " %d " RESET, (int)M[color1][color2]); //(int)M[color1][color2] para mostrar na matriz ele como inteiro e não como float, se fosse como float apareceria assim 2.00(exemplo)
            break;
        case 1:
            printf(BLUE " %d " RESET, (int)M[color1][color2]);
            break;
        case 2:
            printf(MAGENTA " %d " RESET, (int)M[color1][color2]);
            break;
        case 3:
            printf(CYAN " %d " RESET, (int)M[color1][color2]);
            break;
        case 4:
            printf(BLUE " %d " RESET, (int)M[color1][color2]);
            break;
        case 5:
            printf(MAGENTA " %d " RESET, (int)M[color1][color2]);
            break;
        case 6:
            printf(CYAN " %d " RESET, (int)M[color1][color2]);
            break;
        case 7:
            printf(BLUE " %d " RESET, (int)M[color1][color2]);
            break;
        case 8:
            printf(MAGENTA " %d " RESET, (int)M[color1][color2]);
            break;
        case 9:
            printf(CYAN " %d " RESET, (int)M[color1][color2]);
            break;
        case 10:
            printf(BLUE " %d " RESET, (int)M[color1][color2]); 
            break;
    }
}

void show() {

    printf(GREEN "     0   1   2   3   4   5\n\n" RESET);

    for (color1 = 0; color1 < TAM; color1++) {
        printf(GREEN " %d  " RESET, color1);
        for (color2 = 0; color2 < TAM; color2++) {
            if (M[color1][color2] == 0) {
                printf("   "); //caso de números que já foram selecionados, porque são definidos como 0 depois de usar
            } else {
                sum = color1 + color2;
                colors(); //colore e mostra os números
            }
            if (color2 < TAM - 1) {
                printf("|");  //mostra a barra logo após o número que está sendo mostrado assim " %d "
            }
        }
        printf("\n"); //pula linha
        if (color1 < TAM - 1) {
            printf("    -----------------------\n"); //e desenha essa divisão
        }
    }
}

void game() {
    float answer, user;
    int cont = 0;
    char again;
    char op;

    while(tent != 0 && segue == 's') { //faz enquanto não acaba as tentativas e o usuários deseja seguir
        do {
            printf("\nDigite a linha do primeiro número:\n");
            scanf("%d", &lin1);
            printf("Digite a coluna desse número:\n");
            scanf("%d", &col1);
            if (lin1 < 0 || lin1 >= TAM || col1 < 0 || col1 >= TAM)
                printf("Você selecionou uma coordenada que não existe! Por favor, escolha uma linha e coluna entre 0 a 5.\n");
            else if(M[lin1][col1] == 0)
                printf("Você selecionou um espaço em branco, escolha outro.\n");
            else {
                printf("O primeiro número que você selecionou foi: %d\n\n", (int)M[lin1][col1]);
                break;
            }
        } while (1); //só sai do loop com o break

        do {
            printf("Digite a linha do seu segundo número:\n");
            scanf("%d", &lin2);
            printf("Digite a coluna desse número:\n");
            scanf("%d", &col2);
            if (lin2 < 0 || lin2 >= TAM || col2 < 0 || col2 >= TAM) //validação de coordenada possível dentro da matriz
                printf("Você selecionou uma coordenada que não existe! Por favor, escolha uma linha e coluna entre 0 a 5.\n");
            else if(M[lin2][col2] == 0) //validação de coordenada que já foi escolhida
                printf("Você selecionou um espaço em branco, escolha outro.\n");
            else {
                printf("O segundo número que você selecionou foi: %d\n\n", (int)M[lin2][col2]);
                break;
            }
        } while (1);

        do {
            printf("Escolha uma operação entre essas ( + - x : ): ");
            scanf(" %c", &op);
            if ((op == '+' && mais >= 5) || (op == '-' && menos >= 5) || ((op == 'x' | op =='X') && vezes >= 5) || (op == ':' && divide >= 5))
                printf("Você utilizou o máximo de vezes de uma mesma operação, por favor escolher outra.\n");
            else
                break;
        } while (1); // limitando a quantidade de vezes de cada operação para 5

        switch (op) { // resolução do gabarito junto a incrementação do contador de cada operação
            case '+':
                answer = M[lin1][col1] + M[lin2][col2];
                mais++;
                break;
            case '-':
                answer = M[lin1][col1] - M[lin2][col2];
                menos++;
                break;
            case 'x' :
                answer = M[lin1][col1] * M[lin2][col2];
                vezes++;
                break;
            case ':':
                answer = M[lin1][col1] / M[lin2][col2];
                divide++;
                break;
        }

        printf("A operação que você deve realizar é %d %c %d , digite sua resposta (com três casas decimais em casos de divisão):\n", (int)M[lin1][col1], op, (int)M[lin2][col2]);
        scanf("%f", &user);

        limpaTela();


        //user - answer > 0.1 é em casos de divisões, se a diferença for maior que isso ele considera erro, se não é dado como certo por ser próximo
        //cont serve basicamente para a opção de pedir a resposta, ele é um contador
        while ((((user != answer) && op != ':') || (op == ':' && ((user - answer) > 0.05))) && (tent != 0)) {
            tent--; //diminui tent em escopo global
            cont++; // se entrou nesse while, ele já errou 1 vez
            printf("\nVocê errou! A operação que você deve realizar é %d %c %d, tente novamente: \n", (int)M[lin1][col1], op, (int)M[lin2][col2]);
            scanf("%f", &user);
            if ((cont >= 2) && ((user - answer) > 0.05)) { // a partir da 3º tentativa errada, ele faz a pergunta, delimitei a diferença de aproximação pra 1 centésimo
                printf("Você quer ver a resposta e passar para a próxima? Digite 's' se sim e 'n' se não.\n");
                scanf(" %c", &again);
                if (again == 's') {
                    limpaTela();
                    break;
                }
                else {
                    do { //vai continuar aqui até ele acertar
                        printf("\nA operação que você deve realizar é %d %c %d, tente novamente: \n", (int)M[lin1][col1], op, (int)M[lin2][col2]);
                        scanf("%f", &user); //se user for igual a answer, ele vai sair por conta do loop maior
                        tent--; //desconta outra tentativa aqui
                        if(tent == 0)
                            break;
                    } while((op == ':' && ((user - answer) > 0.05)) && (tent != 0)); // mesmo que isso esteja dentro do loop while maior para parar quando tent !0, precisa repetir para obedecer nesse loop tbm
                }
            }
        }

        limpaTela();
        if (((user - answer) <= 0.05) || again == 's') {
            if (((user - answer) <= 0.05)) {
                printf("Você acertou!\n\n");
                acertos++;
                tent--; // diminui uma tentativa do geral
            } else {
                printf("A resposta correta era: %.2f\n\n", answer); // aqui ele desistiu de tentar acertar
                erro++;
                tent--; // diminui uma tentativa do geral
            }
            //igualando valor dos números usados a 0 para printar como "  " para não usar novamente
            M[lin1][col1] = 0;
            M[lin2][col2] = 0;
        }

        if (tent <= 0 || acertos == 18) // encerra o jogo se ele chegar a quantidade de acertos ou as tentativas acabarem
            break; // mudei isso de lugar pra encerrar antes de mostrar a matriz novamente            

        show(); // mostra o estado atual da matriz
        cont = 0; // reinicia o contador de erros para a próxima jogada

        printf("\nVocê deseja continuar o jogo? Digite 's' para sim e qualquer outra tecla se não.\n");
        scanf(" %c", &segue); // segue com escopo global porque tá no while geral da função game
    }
}

int main() {

#ifdef _WIN32
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
#else
    setlocale(LC_ALL, "pt_BR.UTF-8");
#endif

    menu(); //função com menu de como jogar com opção de começar ou não
    preenche(); //preenchendo a matriz com números de 1 a 9 gerados aleatoriamente
    show();
    game();

    if (segue != 's')
        printf("Você encerrou seu jogo.\n");
    else if (acertos == 18) // se tentativas = 24 e tiver 18 acertos, ele também vence
        printf("Parabéns! Você venceu o jogo!\n");
    else
        printf("Você perdeu por ultrapassar o limite de tentativas :(\n");

    return 0;
}
