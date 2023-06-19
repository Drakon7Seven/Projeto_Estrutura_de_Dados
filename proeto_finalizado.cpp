#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
#define MAX_DESCRICAO 100
#define MAX_MARCA 50
#define MAX_SITE 100
#define MAX_TELEFONE 20
#define MAX_UF 3

typedef struct {
    char descricao[MAX_DESCRICAO];
    float peso;
    float valorCompra;
    float valorVenda;
    float valorLucro;
    float percentualLucro;
    char fabricante[MAX_MARCA];
} Produto;

typedef struct {
    char marca[MAX_MARCA];
    char site[MAX_SITE];
    char telefone[MAX_TELEFONE];
    char UF[MAX_UF];
} Fabricante;

Produto produtos[100];
int numProdutos = 0;

Fabricante fabricantes[100];
int numFabricantes = 0;

void cadastrarProduto() {
    Produto produto;
    printf("======= Cadastro de Produto =======\n");
    printf("Descrição: ");
    getchar();
    fgets(produto.descricao, MAX_DESCRICAO, stdin);
    produto.descricao[strcspn(produto.descricao, "\n")] = '\0';
    printf("Peso: ");
    scanf("%f", &produto.peso);
    printf("Valor de compra: ");
    scanf("%f", &produto.valorCompra);
    printf("Valor de venda: ");
    scanf("%f", &produto.valorVenda);
    produto.valorLucro = produto.valorVenda - produto.valorCompra;
    produto.percentualLucro = (produto.valorLucro / produto.valorCompra) * 100;
    printf("Fabricante: ");
    getchar();
    fgets(produto.fabricante, MAX_MARCA, stdin);
    produto.fabricante[strcspn(produto.fabricante, "\n")] = '\0';

    produtos[numProdutos] = produto;
    numProdutos++;

    printf("Produto cadastrado com sucesso.\n");
    system("pause");
    system("cls");
}
void cadastrarFabricante() {
    Fabricante fabricante;
    printf("======= Cadastro de Fabricante =======\n");
    printf("Marca: ");
    getchar();
    fgets(fabricante.marca, MAX_MARCA, stdin);
    fabricante.marca[strcspn(fabricante.marca, "\n")] = '\0';
    printf("Site: ");
    fgets(fabricante.site, MAX_SITE, stdin);
    fabricante.site[strcspn(fabricante.site, "\n")] = '\0';
    printf("Telefone: ");
    fgets(fabricante.telefone, MAX_TELEFONE, stdin);
    fabricante.telefone[strcspn(fabricante.telefone, "\n")] = '\0';
    printf("UF: ");
    fgets(fabricante.UF, MAX_UF, stdin);
    fabricante.UF[strcspn(fabricante.UF, "\n")] = '\0';

    fabricantes[numFabricantes] = fabricante;
    numFabricantes++;

    printf("Fabricante cadastrado com sucesso.\n");
    system("pause");
    system("cls");
}

void listarMarcas() {
    printf("======= Lista de Marcas =======\n");
    for (int i = 0; i < numFabricantes; i++) {
        printf("%s\n", fabricantes[i].marca);
    }
    system("pause");
    system("cls");
}

void listarProdutos() {
    printf("======= Lista de Produtos =======\n");
    for (int i = 0; i < numProdutos; i++) {
        printf("Descrição: %s\n", produtos[i].descricao);
        printf("Peso: %.2f\n", produtos[i].peso);
        printf("Valor de compra: %.2f\n", produtos[i].valorCompra);
        printf("Valor de venda: %.2f\n", produtos[i].valorVenda);
        printf("Valor do lucro: %.2f\n", produtos[i].valorLucro);
        printf("Percentual do lucro: %.2f%%\n", produtos[i].percentualLucro);
        printf("Fabricante: %s\n", produtos[i].fabricante);
        printf("\n");
    }
    system("pause");
    system("cls");
}

void listarProdutosEstado(const char estado[]) {
    printf("======= Produtos do Estado %s =======\n", estado);
    int encontrou = 0;

    for (int i = 0; i < numProdutos; i++) {
        for (int j = 0; j < numFabricantes; j++) {
            if (strcmp(produtos[i].fabricante, fabricantes[j].marca) == 0 && strcmp(fabricantes[j].UF, estado) == 0) {
                printf("Descrição: %s\n", produtos[i].descricao);
                printf("Peso: %.2f\n", produtos[i].peso);
                printf("Valor de compra: %.2f\n", produtos[i].valorCompra);
                printf("Valor de venda: %.2f\n", produtos[i].valorVenda);
                printf("Valor do lucro: %.2f\n", produtos[i].valorLucro);
                printf("Percentual do lucro: %.2f%%\n", produtos[i].percentualLucro);
                printf("Fabricante: %s\n", produtos[i].fabricante);
                printf("\n");
                encontrou = 1;
                break;
            }
            system("pause");
            system("cls");
        }
    }

    if (!encontrou) {
        printf("Nenhum produto encontrado no estado %s.\n", estado);
        system("pause");
        system("cls");
    }
}

void listarProdutosMarca(const char marca[]) {
    printf("======= Produtos da Marca %s =======\n", marca);
    int encontrou = 0;

    for (int i = 0; i < numProdutos; i++) {
        if (strcmp(produtos[i].fabricante, marca) == 0) {
            printf("Descrição: %s\n", produtos[i].descricao);
            printf("Peso: %.2f\n", produtos[i].peso);
            printf("Valor de compra: %.2f\n", produtos[i].valorCompra);
            printf("Valor de venda: %.2f\n", produtos[i].valorVenda);
            printf("Valor do lucro: %.2f\n", produtos[i].valorLucro);
            printf("Percentual do lucro: %.2f%%\n", produtos[i].percentualLucro);
            printf("Fabricante: %s\n", produtos[i].fabricante);
            printf("\n");
            encontrou = 1;
        }
        system("pause");
        system("cls");
    }

    if (!encontrou) {
        printf("Nenhum produto encontrado da marca %s.\n", marca);
        system("pause");
        system("cls");
    }
}

void estadoProdutoMaisCaro() {
    float maiorValor = produtos[0].valorVenda;
    char estadoMaisCaro[MAX_UF];
    int encontrou = 0;

    for (int i = 0; i < numProdutos; i++) {
        for (int j = 0; j < numFabricantes; j++) {
            if (strcmp(produtos[i].fabricante, fabricantes[j].marca) == 0 && produtos[i].valorVenda > maiorValor) {
                maiorValor = produtos[i].valorVenda;
                strcpy(estadoMaisCaro, fabricantes[j].UF);
                encontrou = 1;
            }
        }
    }

    if (encontrou) {
        printf("Estado(s) do Produto Mais Caro: %s\n", estadoMaisCaro);
        system("pause");
        system("cls");
    } else {
        printf("Nenhum produto encontrado.\n");
        system("pause");
        system("cls");
    }
}

void fabricanteProdutoMaisBarato() {
    float menorValor = produtos[0].valorVenda;
    char fabricanteMaisBarato[MAX_MARCA];
    int encontrou = 0;

    for (int i = 0; i < numProdutos; i++) {
        for (int j = 0; j < numFabricantes; j++) {
            if (strcmp(produtos[i].fabricante, fabricantes[j].marca) == 0 && produtos[i].valorVenda < menorValor) {
                menorValor = produtos[i].valorVenda;
                strcpy(fabricanteMaisBarato, fabricantes[j].marca);
                encontrou = 1;
            }
        }
    }

    if (encontrou) {
        printf("Fabricante(s) do Produto Mais Barato: %s\n", fabricanteMaisBarato);
        system("pause");
        system("cls");
    } else {
        printf("Nenhum produto encontrado.\n");
        system("pause");
        system("cls");
    }
}

void ordenarProdutosPorValor() {
    printf("======= Produtos em Ordem Crescente de Valor =======\n");
    Produto temp;

    for (int i = 0; i < numProdutos - 1; i++) {
        for (int j = 0; j < numProdutos - i - 1; j++) {
            if (produtos[j].valorVenda > produtos[j + 1].valorVenda) {
                temp = produtos[j];
                produtos[j] = produtos[j + 1];
                produtos[j + 1] = temp;
            }
        }
    }

    listarProdutos();
    system("pause");
    system("cls");
}

void ordenarProdutosPorLucro() {
    printf("======= Produtos em Ordem Crescente de Valor do Lucro =======\n");
    Produto temp;

    for (int i = 0; i < numProdutos - 1; i++) {
        for (int j = 0; j < numProdutos - i - 1; j++) {
            if (produtos[j].valorLucro > produtos[j + 1].valorLucro) {
                temp = produtos[j];
                produtos[j] = produtos[j + 1];
                produtos[j + 1] = temp;
            }
        }
    }

    listarProdutos();
    system("pause");
    system("cls");
}

void exibirMenu() {
    printf("======= Menu =======\n");
    printf("1. Cadastrar Produto\n");
    printf("2. Cadastrar Fabricante\n");
    printf("3. Listar Todas as Marcas\n");
    printf("4. Listar Todos os Produtos\n");
    printf("5. Listar Produtos de um Estado\n");
    printf("6. Listar Produtos de uma Marca\n");
    printf("7. Apresentar Estado(s) do Produto Mais Caro\n");
    printf("8. Apresentar Fabricante(s) do Produto Mais Barato\n");
    printf("9. Listar Produtos em Ordem Crescente de Valor\n");
    printf("10. Listar Produtos em Ordem Crescente de Valor do Lucro\n");
    printf("0. Sair\n");
    printf("Digite a opção desejada: ");
}

int main() {
    int opcao;
    setlocale(LC_ALL,"Portuguese");
    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarProduto();
                break;
            case 2:
                cadastrarFabricante();
                break;
            case 3:
                listarMarcas();
                break;
            case 4:
                listarProdutos();
                break;
            case 5: {
                char estado[MAX_UF];
                printf("Digite o estado: ");
                getchar();
                fgets(estado, MAX_UF, stdin);
                estado[strcspn(estado, "\n")] = '\0';
                listarProdutosEstado(estado);
                break;
            }
            case 6: {
                char marca[MAX_MARCA];
                printf("Digite a marca: ");
                getchar();
                fgets(marca, MAX_MARCA, stdin);
                marca[strcspn(marca, "\n")] = '\0';
                listarProdutosMarca(marca);
                break;
            }
            case 7:
                estadoProdutoMaisCaro();
                break;
            case 8:
                fabricanteProdutoMaisBarato();
                break;
            case 9:
                ordenarProdutosPorValor();
                break;
            case 10:
                ordenarProdutosPorLucro();
                break;
            case 0:
                printf("Saindo...\n");
                sleep(3);
                system("cls");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

        printf("\n");
    } while (opcao != 0);

    return 0;
}

