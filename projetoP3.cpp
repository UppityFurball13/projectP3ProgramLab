#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Produto {
public:
    string nome;
    int quantidade;
    double preco_unitario;
    double gasto_total;

    Produto(string n, int q, double p) : nome(n), quantidade(q), preco_unitario(p) {
        gasto_total = quantidade * preco_unitario;
    }
};

vector<Produto> produtos;
vector<Produto> vendas;

void adicionarProduto() {
    string nome;
    int quantidade;
    double preco_unitario;
    char adicionarOutro;

    do {
        cout << "Digite o nome do produto: ";
        cin >> nome;
        cout << "Digite a quantidade do produto: ";
        cin >> quantidade;
        cout << "Digite o preco unitario do produto: ";
        cin >> preco_unitario;

        Produto novoProduto(nome, quantidade, preco_unitario);
        produtos.push_back(novoProduto);

        cout << "Produto adicionado com sucesso!" << endl;
        cout << "Deseja adicionar outro produto? (s/n): ";
        cin >> adicionarOutro;

    } while (adicionarOutro == 's' || adicionarOutro == 'S');

    double valor_total = 0;
    for (size_t i = 0; i < produtos.size(); ++i) {
        valor_total += produtos[i].gasto_total;
    }
    cout << "Valor total dos produtos: R$" << valor_total << endl;
}

void venderProduto() {
    string nome;
    int quantidade;
    double valor_total_venda = 0;
    vector<Produto> vendaAtual;

    do {
        cout << "Digite o nome do produto que deseja vender: ";
        cin >> nome;
        cout << "Digite a quantidade do produto que deseja vender: ";
        cin >> quantidade;

        bool produtoEncontrado = false;
        for (size_t i = 0; i < produtos.size(); ++i) {
            if (produtos[i].nome == nome) {
                if (produtos[i].quantidade >= quantidade) {
                    produtos[i].quantidade -= quantidade;
                    Produto venda(nome, quantidade, produtos[i].preco_unitario);
                    vendas.push_back(venda);
                    vendaAtual.push_back(venda);
                    valor_total_venda += venda.gasto_total;
                    produtoEncontrado = true;
                    cout << "Venda realizada com sucesso!" << endl;
                    break;
                } else {
                    cout << "Quantidade insuficiente em estoque!" << endl;
                    produtoEncontrado = true;
                    break;
                }
            }
        }
        if (!produtoEncontrado) {
            cout << "Produto nao encontrado!" << endl;
        }

        cout << "Deseja vender outro produto? (s/n): ";
        cin >> nome; // Reutilizando a variavel nome para armazenar a resposta de continuar ou nao.

    } while (nome == "s" || nome == "S");

    cout << "\nProdutos vendidos nesta transacao:\n";
    for (size_t i = 0; i < vendaAtual.size(); ++i) {
        cout << "Produto: " << vendaAtual[i].nome << ", Quantidade: " << vendaAtual[i].quantidade << ", Preco Unitario: R$" << vendaAtual[i].preco_unitario << ", Total: R$" << vendaAtual[i].gasto_total << endl;
    }
    cout << "Valor total da venda: R$" << valor_total_venda << endl;
}

void mostrarDadosVendas() {
    int opcaoDadosVendas;
    cout << "Escolha uma opcao:" << endl;
    cout << "1 - Quantidade de produtos vendidos" << endl;
    cout << "2 - Quantidade de produtos a vender" << endl;
    cout << "3 - Montante de vendas" << endl;
    cin >> opcaoDadosVendas;

    switch (opcaoDadosVendas) {
        case 1: {
            int totalProdutosVendidos = 0;
            for (size_t i = 0; i < vendas.size(); ++i) {
                totalProdutosVendidos += vendas[i].quantidade;
            }
            cout << "Quantidade total de produtos vendidos: " << totalProdutosVendidos << endl;
            break;
        }
        case 2: {
            cout << "Quantidade de produtos disponiveis para venda:" << endl;
            for (size_t i = 0; i < produtos.size(); ++i) {
                cout << "Produto: " << produtos[i].nome << ", Quantidade: " << produtos[i].quantidade << endl;
            }
            break;
        }
        case 3: {
            double valor_total_vendas = 0;
            cout << "Dados das vendas:" << endl;
            for (size_t i = 0; i < vendas.size(); ++i) {
                cout << "Produto: " << vendas[i].nome << ", Quantidade: " << vendas[i].quantidade << ", Preco Unitario: R$" << vendas[i].preco_unitario << ", Total Gasto: R$" << vendas[i].gasto_total << endl;
                valor_total_vendas += vendas[i].gasto_total;
            }
            cout << "Valor total das vendas: R$" << valor_total_vendas << endl;
            
            char gerarArquivo;
            cout << "Deseja gerar um arquivo .txt com essas informacoes? (s/n): ";
            cin >> gerarArquivo;

            if (gerarArquivo == 's' || gerarArquivo == 'S') {
                ofstream arquivo("dados_vendas.txt");
                if (arquivo.is_open()) {
                    arquivo << "Dados das vendas:" << endl;
                    for (size_t i = 0; i < vendas.size(); ++i) {
                        arquivo << "Produto: " << vendas[i].nome << ", Quantidade: " << vendas[i].quantidade << ", Preco Unitario: R$" << vendas[i].preco_unitario << ", Total Gasto: R$" << vendas[i].gasto_total << endl;
                    }
                    arquivo << "Valor total das vendas: R$" << valor_total_vendas << endl;
                    arquivo.close();
                    cout << "Arquivo 'dados_vendas.txt' gerado com sucesso!" << endl;
                } else {
                    cout << "Erro ao gerar o arquivo!" << endl;
                }
            }
            break;
        }
        default:
            cout << "Opcao invalida! Tente novamente." << endl;
    }
}

int main() {
    int opcao;
    do {
        cout << "Menu Principal:" << endl;
        cout << "1 - Adicionar produtos" << endl;
        cout << "2 - Venda dos produtos" << endl;
        cout << "3 - Dados das Vendas" << endl;
        cout << "4 - Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                adicionarProduto();
                break;
            case 2:
                venderProduto();
                break;
            case 3:
                mostrarDadosVendas();
                break;
            case 4:
                cout << "Saindo do programa..." << endl;
                break;
            default:
                cout << "Opcao invalida! Tente novamente." << endl;
        }
    } while (opcao != 4);

    return 0;
}

