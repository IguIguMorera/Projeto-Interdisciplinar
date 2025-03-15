/*este programa faz o cadastro de produtos, wats e tempode uso, vamos usar
para o projeto interdisciplinar;
*/


#include <iostream>
#include <string>

struct Produto {
    char nome[15];
    float wats;
    float tempo;
};

int main(int argc, char** argv) {
    float x = 0;
    int n;
    Produto produtos[10];  
    int contador = 0;  




    while (x != 5) {

        std::cout << "menu: \n";
        std::cout << "1- cadastrar produto\n";
        std::cout << "2- ver produtos\n";
        std::cout << "5- sair\n";
        std::cout << "\n";
        std::cin >> x;

        if (x == 1) {
            if (contador < 10) {  // Verifica se h� espa�o para mais produtos
                std::cout << "Nome do produto: \n";
                std::cin >> produtos[contador].nome;
                std::cout << "Wats do produto: \n";
                std::cin >> produtos[contador].wats;
                std::cout << "Tempo do produto: \n";
                std::cin >> produtos[contador].tempo;

                std::cout << "\nProduto cadastrado com sucesso!\n";
                contador++;  // Incrementa o contador de produtos cadastrados
            } else {
                std::cout << "Limite de produtos cadastrados atingido!\n";
            }
        }

        if (x == 2) {
            if (contador == 0) {
                std::cout << "Nenhum produto cadastrado.\n";
            } else {
                std::cout << "Produtos cadastrados: \n";
                for (int i = 0; i < contador; i++) {
                    std::cout << "\nProduto " << i + 1 << ":\n";
                    std::cout << "Nome: " << produtos[i].nome << "\n";
                    std::cout << "Wats: " << produtos[i].wats << " W\n";
                    std::cout << "Tempo: " << produtos[i].tempo << " minutos\n";
                }
            }
        }
    }

    return 0;
}

