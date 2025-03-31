#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100

typedef struct {
    int id_prod;
    char nome[15];
    float watts, dias, tempo, kwh;
} cad_prod;

/* ********************************************* */
/* ***     Preenche o vetor de produtos      *** */
/* ***       a partir do arquivo texto       *** */
/* ********************************************* */
void preencheVetor(cad_prod *v, int *ultimoID, int n) {
    FILE *arqprod;
    int i, id, repetido;

    arqprod = fopen("arqprod.txt", "r");
    if (arqprod == NULL) {
        printf("Problemas com o arquivo de entrada de dados\n");
        exit(1);
    }

    for (i = 0; i < n; i++) {
        // Gerar um ID único entre 0 e 100, sem repetir
        do {
            repetido = 0;
            (*ultimoID)++; // Incrementa ID sequencialmente

            // Verifica se o ID gerado já existe
            for (id = 0; id < i; id++) {
                if (v[id].id_prod == *ultimoID) {
                    repetido = 1;
                    break;
                }
            }
        } while (repetido);

        // Atribui o ID ao produto
        v[i].id_prod = *ultimoID;

        // Leitura dos dados do produto
        fscanf(arqprod, "%s", v[i].nome);
        fscanf(arqprod, "%f", &v[i].watts);
        fscanf(arqprod, "%f", &v[i].tempo);
        fscanf(arqprod, "%f", &v[i].dias);
    }

    fclose(arqprod);
}

/* ********************************************* */
/* ***     Calcular consumo dos produtos     *** */
/* ********************************************* */
void calculaprod(cad_prod *v, int ultimoID) {
    int i;

    for (i = 0; i < ultimoID; i++) {
        v[i].kwh = (v[i].watts * v[i].tempo * v[i].dias) / 1000.0;
    }
}

/* ********************************************* */
/* ***        Exibir produtos formatados     *** */
/* ********************************************* */
void exibirProdutos(cad_prod *v, int n) {
    int i;

    if (n == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("%-10s %-20s %-10s %-10s %-10s\n", "ID", "Nome", "Watts", "Horas", "Dias");
    printf("---------------------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("%-10d %-20s %-10.0f %-10.2f %-10.0f\n", 
               v[i].id_prod, v[i].nome, v[i].watts, v[i].tempo, v[i].dias);
    }
}

/* ********************************************* */
/* ***        Exibir produtos calculados     *** */
/* ********************************************* */
void prodcalculado(cad_prod *v, int ultimoID) {
    int i;

    if (ultimoID == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    calculaprod(v, ultimoID);

    printf("\nProdutos cadastrados:\n");
    for (i = 0; i < ultimoID; i++) {
        printf("ID: %d\n", v[i].id_prod);
        printf("Nome: %s\n", v[i].nome);
        printf("Watts: %.0f W\n", v[i].watts);
        printf("Tempo de uso por dia: %.2f horas\n", v[i].tempo);
        printf("Dias: %.0f dias\n", v[i].dias);
        printf("Consumo: %.2f kWh\n", v[i].kwh); // Exibe o consumo calculado
        printf("------------------------------------\n");
    }
}

/* ********************************************* */
/* ***                MAIN                   *** */
/* ********************************************* */
int main() {
    cad_prod produtos[MAX_PRODUTOS];
    int ultimoID = 0, x = 0;  // Inicializando x
    int numProdutos;

    while (x != 5) {
        printf("\nMenu:\n");
        printf("1- Ler do arquivo\n");
        printf("2- Ver produtos cadastrados\n");
        printf("3- Mostrar produtos com consumo calculado\n");
        printf("5- Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &x);
        printf("------------------------------------\n");

        switch (x) {
            case 1:
                printf("Digite o numero de produtos a serem lidos: ");
                if (scanf("%d", &numProdutos) != 1 || numProdutos > MAX_PRODUTOS || numProdutos <= 0) {
                    printf("Numero inválido de produtos!\n");
                    break;
                }

                // Chama a função para preencher os produtos a partir do arquivo
                preencheVetor(produtos, &ultimoID, numProdutos);
                printf("\nDados carregados do arquivo!\n");
                break;

            case 2:
                exibirProdutos(produtos, ultimoID);
                break;

            case 3:
                prodcalculado(produtos, ultimoID);
                break;

            case 5:
                printf("Saindo do programa...\n");
                return 0;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }

    return 0;
}

