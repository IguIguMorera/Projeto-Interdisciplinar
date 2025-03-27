#include <stdio.h>
#include <stdlib.h>

#define MAX_PRODUTOS 100

struct cad_prod {
    int id_prod;
    char nome[15];
    float watts;
};

typedef struct cad_prod cad_prod;

/* ********************************************* */
/* ***     preenche o vetor de produtos      *** */
/* ***       a partir do arquivo texto       *** */
/* ********************************************* */
void preencheVetor(cad_prod *v, int n) {
    FILE *arqprod;
    int i;

    arqprod = fopen("arqprod.txt", "r");
    if (arqprod == NULL) {
        printf("Problemas com o arquivo de entrada de dados\n");
        exit(1);
    }

    for (i = 0; i < n; i++) {
        if (fscanf(arqprod, "%d %14s %f", &v[i].id_prod, v[i].nome, &v[i].watts) != 3) {
            printf("Erro ao ler os dados do arquivo\n");
            fclose(arqprod);
            exit(1);
        }
    }

    fclose(arqprod);
}

void exibirProdutos(cad_prod *v, int n) {
	int i;
    printf("%-10s %-20s %-10s\n", "ID", "Nome", "Watts");
    printf("-------------------------------------------\n");
    for ( i = 0; i < n; i++) {
        printf("%-10d %-20s %-10.2f\n", v[i].id_prod, v[i].nome, v[i].watts);
    }
}

int main() {
    cad_prod produtos[MAX_PRODUTOS];
    int numProdutos;

    printf("Digite o numero de produtos a serem lidos: ");
    if (scanf("%d", &numProdutos) != 1 || numProdutos > MAX_PRODUTOS || numProdutos <= 0) {
        printf("Número invalido de produtos!\n");
        return 1;
    }

    preencheVetor(produtos, numProdutos);
    exibirProdutos(produtos, numProdutos);

    return 0;
}

