#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_PRODUTOS 20

// Estrutura para armazenar dados dos produtos na memória
typedef struct {
    int Identificacao;  // Código do produto
    char nome_produto[20];  // Nome do produto
    char data_fabricacao[11];  // Data de fabricação (formato dd/mm/aaaa)
    char nome_fornecedor[20]; // Nome do fornecedor
    int quantidade;  // Quantidade de produtos
    float valor_compra; // Valor de compra do produto
} Produto; // O título da struct fica fora da chave para não precisar utilizar "struct" todas as vezes que for menciona-lo.

//Estrutura criada para gerenciar os dados cadastrados em um sistema de controle de estoque.
//Acompanha um vetor (array) de estruturas (Produto) que armazena todos os produtos cadastrados no estoque.
typedef struct {
    Produto produtos[MAX_PRODUTOS];
    int total_produtos; // Contador de produtos, mantém o controle dos produtos cadastrados em estoque.
} Estoque;

// Função para cálculo de capacidade de produção
// Essa função exibe a capacidade de produção diária, mensal e anual
void calcularProducao(float producaoMensal) {
    // Calcula a capacidade total da fábrica (baseada na produção atual ser 40%)
    float capacidadeMensal = producaoMensal / 0.4;
    float capacidadeAnual = capacidadeMensal / 30;
    float capacidadeDiaria = capacidadeMensal * 12;

    printf("\n======================\n");
    printf("\nCAPACIDADE DE PRODUÇÃO\n");
    printf("\n======================\n");
    printf("Produção atual (40%%): %.2f unidades/mês", producaoMensal);
    printf("\nCAPACIDADE TOTAL DE PRODUÇÃO: \n");
    printf("\nCapacidade diária: %.2f\n", capacidadeDiaria);
    printf("\nCapacidade mensal: %.2f\n", capacidadeMensal);
    printf("\nCapacidade anual: %.2f\n", capacidadeAnual);
}

// Função para verificar estoque e se possível cadastrar um novo produto no estoque caso não esteja cheio
void cadastrarProduto(Estoque *estoque) { // Recebe um ponteiro para o estoque e adiciona um novo produto ao array
    if (estoque->total_produtos >= MAX_PRODUTOS) {
        printf("\nLimite de estoque excedido! Não é possível cadastrar mais produtos.\n");
        return;
    }
    
    Produto p;
    
    // Entrada de dados do usuário para criar um novo produto
    printf("\n====================\n");
    printf("\nCADASTRO DE PRODUTO\n");
    printf("\n====================\n");
    printf("Código do Produto: ");
    scanf("%d", &p.Identificacao); 
    printf("Nome do Produto: ");
    scanf(" %[^\n]s", p.nome_produto); // Utilizando o %[^\n]s para que consiga ler os espaços em branco na string
    printf("Data de Fabricação: (DD/MM/AA): ");
    scanf(" %[^\n]s", p.data_fabricacao);
    printf("Nome do Fonercedor: ");
    scanf(" %[^\n]s", p.nome_fornecedor);
    printf("Quantidade de Produtos: ");
    scanf("%d", &p.quantidade);
    printf("Valor de Compra: ");
    scanf("%f", &p.valor_compra);

    // Adiciona o novo produto ao estoque
    estoque->produtos[estoque->total_produtos] = p;
    estoque-> total_produtos++;

    printf("\n=============================\n");
    printf("PRODUTO CADASTRADO COM SUCESSO!\n");
    printf("\n=============================\n");
}
// Função para listar todos os produtos cadastrados no estoque
// Recebe o estoque como parâmetro e exibe todos os produtos
void listarProdutos(Estoque *estoque) {
    if (estoque->total_produtos == 0) {
        printf("\nEstoque vazio! Não existe protudo cadastrado.\n");
        return;
    }
    // Exibe os produtos um por um
    printf("\n======================\n");
    printf("\n PRODUTO EM ESTOQUE\n");
    for (int i = 0; i < estoque->total_produtos; i++) {
        Produto p = estoque-> produtos[i];
        printf("\nProduto %d:\n", i + 1);
        printf("Código do Produto: %d\n", p.Identificacao);
        printf("Nome do Produto: %s\n", p.nome_produto);
        printf("Data de Fabricação: %s\n", p.data_fabricacao);
        printf("Fonercedor: %s\n", p.nome_fornecedor);
        printf("Quantidade de Produtos: %d\n", p.quantidade);
        printf("Valor de Compra: %.2f\n", p.valor_compra);
    }
    printf("\n=====================\n");
}
// Como solicitado, criei uma função para que o usuário possa pesquisar o produto no menu, através do nome ou ID. 
void pesquisarProdutos(Estoque *estoque) {
    if (estoque->total_produtos == 0) {
        printf("\nEstoque vazio! Nenhum produto cadastrado.\n");
        return;
    }
    // SUB-MENU para receber a opção do usuário
    int tipoBusca;
    printf("\n=== Pesquisa de Produto ===\n");
    printf("Escolha o tipo de busca:\n");
    printf("1. Buscar pelo Código\n");
    printf("2. Buscar pelo Nome\n");
    printf("Opção: ");
    scanf("%d", &tipoBusca);
    // verificação da opção
    if (tipoBusca == 1) {
        // Busca por código
        int codigoBusca;
        printf("\nDigite o código do produto que deseja buscar: ");
        scanf("%d", &codigoBusca);
        // criação de índice através do for para percorrer o estoque e verificar o produto desejado. 
        for (int i = 0; i < estoque->total_produtos; i++) {
            if (estoque->produtos[i].Identificacao == codigoBusca) {
                Produto p = estoque->produtos[i];
                printf("\n--- Produto Encontrado ---\n");
                printf("Código: %d\n", p.Identificacao);
                printf("Nome: %s\n", p.nome_produto);
                printf("Data de Fabricação: %s\n", p.data_fabricacao);
                printf("Fornecedor: %s\n", p.nome_fornecedor);
                printf("Quantidade: %d\n", p.quantidade);
                printf("Valor de Compra: R$ %.2f\n", p.valor_compra);
                printf("---------------------------------\n");
                return;
            }
        }
        printf("\nProduto com código %d não encontrado.\n", codigoBusca);
        // verificação para a seleção de opção 2
    } else if (tipoBusca == 2) {
        // Busca por nome
        char nomeBusca[50];
        printf("\nDigite o nome do produto que deseja buscar: ");
        scanf(" %[^\n]s", nomeBusca);
        // o for com o mesmo objetivo da busca por código
        for (int i = 0; i < estoque->total_produtos; i++) {
            if (strcmp(estoque->produtos[i].nome_produto, nomeBusca) == 0) {
                Produto p = estoque->produtos[i];
                printf("\n--- Produto Encontrado ---\n");
                printf("Código: %d\n", p.Identificacao);
                printf("Nome: %s\n", p.nome_produto);
                printf("Data de Fabricação: %s\n", p.data_fabricacao);
                printf("Fornecedor: %s\n", p.nome_fornecedor);
                printf("Quantidade: %d\n", p.quantidade);
                printf("Valor de Compra: R$ %.2f\n", p.valor_compra);
                printf("---------------------------------\n");
                return;
            }
        }
        // Em caso de não encontrar o Produto
        printf("\nProduto com nome \"%s\" não encontrado.\n", nomeBusca);
    } else {
        printf("\nOpção inválida! Tente novamente.\n");
    }
}
// Função para contabilizar os valores de compra semanal, mensal e anual.

void contabilizador(Estoque *estoque){
    if (estoque->total_produtos == 0) {
    printf("\nEstoque vazio! Nenhum produto cadastrado.\n");
    return;
    }
    float total_semanal = 0;  
    float total_mensal = 0;  
    float total_anual = 0; 
    float valor_total; 
    // for para percorrer o estoque
    for (int i = 0; i < estoque->total_produtos; i++){ 
        Produto p = estoque->produtos[i]; 
        // somando os valores considerando a quantidade
        valor_total= p.valor_compra *p.quantidade; 
        
        // calcula compras semanais
        total_semanal+=valor_total; 
        //calcula compras mensais 
        total_mensal+=valor_total;
        // calcula compras anuais
        total_anual+=valor_total * 12; 
    }
    
    printf("\n===================\n");
    printf("\n VALORES DE COMPRAS \n"); 
    printf(" Compras Semanais: R$ %.2f\n", total_semanal); 
    printf(" Compras Mensais: R$ %.2f\n", total_mensal); 
    printf(" Compras Anuais: R$ %.2f\n", total_anual); 
    printf("\n===================\n");
}


// Função principal do módulo onde chamarei o menu, as funções e structs para exibir o controle

int main() {
// Chamando a função do Estoque
    Estoque estoque = { .total_produtos = 0}; // Inicializa o estoque vazio
    int opcao;
    
    do { 
        printf("\n\n");
        printf("\t\t\t\t\t\t       --------------------------------\n");
        printf("\t\t\t\t\t\t       |        MENU OPERACIONAL      |\n");
        printf("\t\t\t\t\t\t       --------------------------------\n");
        printf("\t\t\t\t\t\t       |1. CAPACIDADE DE PRODUÇÃO     |\n");
        printf("\t\t\t\t\t\t       |2. CADASTRAR PRODUTO          |\n");
        printf("\t\t\t\t\t\t       |3. LISTAR PRODUTO             |\n");
        printf("\t\t\t\t\t\t       |4. PESQUISAR PRODUTO          |\n");
        printf("\t\t\t\t\t\t       |5. CONTABILIZADOR             |\n");
        printf("\t\t\t\t\t\t       |6. SAIR                       |\n");
        printf("\t\t\t\t\t\t       --------------------------------\n\n\n");

        
        printf("\nOLÁ USUÁRIO, SEJA BEM VINDO AO NOSSO MENU OPERACIONAL E CONTROLE DE ESTOQUE!");
        printf("\nPARA COMEÇAR SELECIONE A OPÇÃO DESEJADA: \n");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                calcularProducao(500);
            break;
            case 2:
                cadastrarProduto(&estoque);
            break;
            case 3:
                listarProdutos(&estoque);
            break;
            case 4: 
                pesquisarProdutos(&estoque); 
            break; 
            case 5:
            contabilizador(&estoque); 
            break; 
            case 6:
                printf("Encerrando o sistema***\n");
            break;
            default:
                printf("\nOpção inválida! Escolha novamente.\n");
        }
    }while (opcao != 6);

    return 0;
}