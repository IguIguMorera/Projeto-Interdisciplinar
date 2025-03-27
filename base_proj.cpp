/*este programa faz o cadastro de produtos, wats e tempode uso, vamos usar
para o projeto interdisciplinar;
*/

#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

struct cad_prod {
    int id_prod;
    string nome;
    float watts;
};

struct cal {
    float tempo;
    float dias;
    float kwh;
};

int main() {
    int x = 0;
    int contador = 0;
    cad_prod produtos[10];
    cal tempos[10];

    while (x != 5) {
        cout << "Menu:\n";
        cout << "1- Cadastrar produto\n";
        cout << "2- Ver produtos\n";
        cout << "5- Sair\n";
        cin >> x;

        if (x == 1) {
            if (contador < 10) {
                cout << "ID do produto: ";
                cin >> produtos[contador].id_prod;
                cin.ignore(); // Evita problemas ao ler strings após números
                cout << "Nome do produto: ";
                getline(cin, produtos[contador].nome);
                cout << "Watts do produto: ";
                cin >> produtos[contador].watts;
                cout << "Tempo de uso por dia (horas): ";
                cin >> tempos[contador].tempo;
                cout << "Dias usando o produto: ";
                cin >> tempos[contador].dias;

                // Cálculo do consumo
                tempos[contador].kwh = (produtos[contador].watts * tempos[contador].tempo * tempos[contador].dias) / 1000.0;

                cout << "\nProduto cadastrado com sucesso!\n";
                contador++;
            } else {
                cout << "Limite de produtos cadastrados atingido!\n";
            }
        }

        if (x == 2) {
            if (contador == 0) {
                cout << "Nenhum produto cadastrado.\n";
            } else {
                cout << "Produtos cadastrados:\n";
                for (int i = 0; i < contador; i++) {
                    cout << "ID: " << produtos[i].id_prod << "\n";
                    cout << "Nome: " << produtos[i].nome << "\n";
                    cout << "Watts: " << produtos[i].watts << " W\n";
                    cout << "Tempo de uso por dia: " << tempos[i].tempo << " horas\n";
                    cout << "Dias: " << tempos[i].dias << " dias\n";
                    cout << "Consumo: " << tempos[i].kwh << " kWh\n";
                }
            }
        }
    }

    return 0;
}

