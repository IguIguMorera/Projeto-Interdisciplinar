#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>

typedef struct {
    char nome[15];
    float watts;
    int id_comodo;
} cad_prod;

typedef struct {
    char nome[256];
    char email[256];
    char tel[20];
    char cpf[15];
} cad_cli;

typedef struct {
    char desc[256];
    int id_cliente;
} cad_comodo;

// Conectar ao banco de dados
MYSQL* conectarBD() {
    MYSQL* conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "serverbdpi.ddns.net", "admin", "Mced", "mced", 3306, NULL, 0)) {
        fprintf(stderr, "Erro ao conectar: %s\n", mysql_error(conn));
        exit(1);
    }

    return conn;
}

/* ********************************************* */
/* ***           Cadastrar Cliente           *** */
/* ********************************************* */
void cadastraCliente(MYSQL* conn, cad_cli *c) {
    char query[512];

    sprintf(query,
        "INSERT INTO clientes (cpf_cliente, nm_cliente, tel_cliente, email_cliente) "
        "VALUES ('%s', '%s', '%s', '%s')",
        c->cpf, c->nome, c->tel, c->email
    );

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao inserir cliente: %s\n", mysql_error(conn));
    } else {
        printf("\nCliente inserido com sucesso!\n");
    }
}

/* ********************************************* */
/* ***          Cadastrar Comodos            *** */
/* ********************************************* */
void cadastraComodo(MYSQL* conn, cad_comodo *cd) {
    char query[512];

    sprintf(query,
        "INSERT INTO comodos (ds_comodo, ID_cliente) "
        "VALUES ('%s', %d)",
        cd->desc, cd->id_cliente
    );

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao inserir comodo: %s\n", mysql_error(conn));
    } else {
        printf("\nComodo inserido com sucesso!\n");
    }
}

/* ********************************************* */
/* ***          Cadastrar Produtos           *** */
/* ********************************************* */
void inserirProduto(MYSQL* conn, cad_prod *p) {
    char query[512];

    sprintf(query,
        "INSERT INTO produtos (nm_prod, watts, id_comodo) "
        "VALUES ('%s', %.2f, %d)",
        p->nome, p->watts, p->id_comodo
    );

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao inserir produto: %s\n", mysql_error(conn));
    } else {
        printf("Produto inserido com sucesso!\n");
    }
}

/* ********************************************* */
/* ***     Mostrar produtos cadastrados      *** */
/* ********************************************* */
void exibirProdutos(MYSQL* conn) {
    if (mysql_query(conn, "SELECT * FROM produtos")) {
        fprintf(stderr, "Erro ao buscar produtos: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;

    printf("\n%-5s %-15s %-10s\n", "ID", "Nome", "Watts");
    printf("----------------------------------------\n");

    while ((row = mysql_fetch_row(res))) {
        printf("%-5s %-15s %-10s\n", row[0], row[1], row[2]);
    }

    mysql_free_result(res);
}

/* ********************************************* */
/* ***                MAIN                   *** */
/* ********************************************* */
int main() {
    MYSQL* conn = conectarBD();
    int opcao;
    cad_prod p;
    cad_cli c;
    cad_comodo cd;

    while (1) {
        printf("\nMenu:\n");
        printf("1 - Cadastrar Cliente\n");
        printf("2 - Cadastrar Comodo \n");
        printf("3 - Cadastrar produto\n");
        printf("4 - Exibir produtos\n");
        printf("5 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // Limpa Enter

        switch (opcao) {
            case 1:
			    printf("CPF (somente numeros): ");
			    fgets(c.cpf, sizeof(c.cpf), stdin);
			    c.cpf[strcspn(c.cpf, "\n")] = 0;
			
			    printf("Nome: ");
			    fgets(c.nome, sizeof(c.nome), stdin);
			    c.nome[strcspn(c.nome, "\n")] = 0;
			
			    printf("Telefone: ");
			    fgets(c.tel, sizeof(c.tel), stdin);
			    c.tel[strcspn(c.tel, "\n")] = 0;
			
			    printf("Email: ");
			    fgets(c.email, sizeof(c.email), stdin);
			    c.email[strcspn(c.email, "\n")] = 0;
			
			    // Verificação
			    if (strlen(c.cpf) == 0  || strlen(c.nome) == 0 || strlen(c.tel) == 0 || strlen(c.email) == 0) {
			        printf("Erro: CPF, telefone e email sao obrigatorios!\n");
			    } else {
			        cadastraCliente(conn, &c);
			    }
			    break;
			    
			case 2:
			    printf("Nome do comodo: ");
			    fgets(cd.desc, sizeof(cd.desc), stdin);
			    cd.desc[strcspn(cd.desc, "\n")] = 0;
			
			    printf("ID do cliente: ");
			    scanf("%hhd", &cd.id_cliente); // ou %d se mudar tipo
			    getchar();
			
			    if (strlen(cd.desc) == 0) {
			        printf("Erro: Descricao do comodo e obrigatoria!\n");
			    } else {
			        cadastraComodo(conn, &cd);
			    }
			    break;

            case 3:
			    printf("Nome do produto: ");
			    fgets(p.nome, sizeof(p.nome), stdin);
			    p.nome[strcspn(p.nome, "\n")] = 0;
			
			    printf("Watts: ");
			    scanf("%f", &p.watts);
			    getchar();
			
			    printf("ID do comodo: ");
			    scanf("%d", &p.id_comodo);
			    getchar();
			
			    if (strlen(p.nome) == 0 || p.id_comodo <= 0) {
			        printf("Erro: Nome, Watts e ID do comodo sao obrigatorios!\n");
			    } else {
			        inserirProduto(conn, &p);
			    }
			    break;

            case 4:
                exibirProdutos(conn);
                break;

            case 5:
                mysql_close(conn);
                printf("Encerrando...\n");
                return 0;

            default:
                printf("Opcao invalida!\n");
        }
    }

    return 0;
}

