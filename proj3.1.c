#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100

typedef struct {
    int id_prod;
    char nome[15];
    float watts;
	float tempo;
    float dias;
    float kwh;
    
} cad_prod;

/*typedef struct {
    float tempo;
    float dias;
    float kwh;
} tempo_uso;*/

/* ********************************************* */
/* ***     preenche o vetor de produtos      *** */
/* ***       a partir do arquivo texto       *** */
/* ********************************************* */
void preencheVetor(cad_prod *v,int n) {
    FILE *arqprod;
    int i;

    arqprod = fopen("arqprod.txt", "r");
    if (arqprod == NULL) {
        printf("Problemas com o arquivo de entrada de dados\n");
        exit(1);
    }

    for (i = 0; i < n; i++) {
        fscanf(arqprod, "%d", &v[i].id_prod);
        fscanf(arqprod, "%s", v[i].nome);
        fscanf(arqprod, "%f", &v[i].watts);
        fscanf(arqprod, "%f", &v[i].tempo);
        fscanf(arqprod, "%f", &v[i].dias);
    }

    fclose(arqprod);
}

/* ********************************************* */
/* ***          Exibir produtos formatados     *** */
/* ********************************************* */
void exibirProdutos(cad_prod *v, int n) {
    int i;

    printf("%-10s %-20s %-10s %-10s %-10s\n", "ID", "Nome", "Watts", "Horas", "Dias");
    printf("---------------------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("%-10d %-20s %-10.2f %-10.2f %-10.2f\n", 
               v[i].id_prod, v[i].nome, v[i].watts, v[i].tempo, v[i].dias);
    }
}

int main() {
    cad_prod produtos[MAX_PRODUTOS];
    /*tempo_uso tempos[MAX_PRODUTOS];*/
    int contador = 0;
    int x,i;

    while (1) {
        printf("\nMenu:\n");
        printf("1- Cadastrar produto\n");
        printf("2- Ver produtos\n");
        printf("3- Ler do arquivo\n");
        printf("5- Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &x);
        printf("------------------------------------\n");
        getchar(); // Evita problemas ao ler strings após números

        switch (x) {
            case 1:
                if (contador < MAX_PRODUTOS) {
                    printf("ID do produto: ");
                    scanf("%d", &produtos[contador].id_prod);
                    getchar(); // Para evitar problemas ao ler a string depois do número

                    printf("Nome do produto: ");
                    scanf("%14s", produtos[contador].nome); // Evita estouro de buffer

                    printf("Watts do produto: ");
                    scanf("%f", &produtos[contador].watts);

                    printf("Tempo de uso por dia (horas): ");
                    scanf("%f", &produtos[contador].tempo);

                    printf("Dias usando o produto: ");
                    scanf("%f", &produtos[contador].dias);

                    // Cálculo do consumo
                    produtos[contador].kwh = (produtos[contador].watts * produtos[contador].tempo * produtos[contador].dias) / 1000.0;

                    printf("\nProduto cadastrado com sucesso!\n");
                    contador++;
                } else {
                    printf("Limite de produtos cadastrados atingido!\n");
                }
            break;

            case 2:
            	
            	
                if (contador == 0) {
                    printf("Nenhum produto cadastrado.\n");
                } else {
                    printf("\nProdutos cadastrados:\n");
                    for (i = 0; i < contador; i++) {
                        printf("ID: %d\n", produtos[i].id_prod);
                        printf("Nome: %s\n", produtos[i].nome);
                        printf("Watts: %.2f W\n", produtos[i].watts);
                        printf("Tempo de uso por dia: %.2f horas\n", produtos[i].tempo);
                        printf("Dias: %.2f dias\n", produtos[i].dias);
                        printf("Consumo: %.2f kWh\n", produtos[i].kwh);
                        printf("------------------------------------\n");
                    }
                }
            break;

            case 3: {
                int numProdutos;
                printf("Digite o numero de produtos a serem lidos: ");
                if (scanf("%d", &numProdutos) != 1 || numProdutos > MAX_PRODUTOS || numProdutos <= 0) {
                    printf("Número inválido de produtos!\n");
                    break;
                }

                // Chama a função para preencher os produtos a partir do arquivo
                preencheVetor(produtos, numProdutos);
                exibirProdutos(produtos, numProdutos);

                printf("\nDados carregados do arquivo!\n");
                            
            break;
            }

            case 5:
                printf("Saindo do programa...\n");
                return 0;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }

    return 0;
}
