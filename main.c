#include <stdio.h>
#include "funcionario.h"

#define STR_TAM 100

typedef enum OpcaoMenu {
    ADICIONAR_FUNC = 1,
    ATUALIZAR_FUNC,
    BUSCAR_FUNC,
    LISTAR_FUNCS,
    SAIR_MENU
} OpcaoMenu;

void imprimir_menu(void) {
    printf("\n\n[1] - Adicionar funcionario\n[2] - Atualizar funcionario\n[3] - Buscar funcionario\n[4] - Listar funcionarios\n[5] - Sair do sistema");
    printf("\nInforme o numero da opcao desejada: ");
}

int main(void) {
    char nome[STR_TAM], cargo[STR_TAM];
    int matricula;
    double salario;

    Funcionario *func_raiz = NULL; // Inicializa a árvore vazia

    int opcao = 0;
    do {
        imprimir_menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case ADICIONAR_FUNC:
                // Recolhe os dados necessários para cadastro
                printf("\nInforme o numero de matricula: ");
                scanf("%d", &matricula);

                printf("\nInforme nome: ");
                scanf("\n%99[^\n]", nome);
                
                printf("\nInforme cargo: ");
                scanf("\n%99[^\n]", cargo);
                
                printf("\nInforme salario: ");
                scanf("%lf", &salario);

                // Invoca a função de inserção passando os dados requisitados
                inserir_funcionario(&func_raiz, matricula, nome, cargo, salario);
                break;

            case ATUALIZAR_FUNC:
            printf("\nInforme o numero de matricula: ");
                scanf("%d", &matricula);

                printf("\nInforme o novo nome: ");
                scanf("\n%99[^\n]", nome);
                
                printf("\nInforme o novo cargo: ");
                scanf("\n%99[^\n]", cargo);
                
                printf("\nInforme o novo salario: ");
                scanf("%lf", &salario);

                atualizar_funcionario(func_raiz, matricula, nome, cargo, salario);
                break;
            
            case BUSCAR_FUNC:
                printf("\nInforme o numero de matricula: ");
                scanf("%d", &matricula);

                buscar_funcionario(func_raiz, matricula);
                break;

            case LISTAR_FUNCS:
                listar_funcionarios(func_raiz);
        }
    } while (opcao != SAIR_MENU);
    limpar_cadastros(func_raiz); // Libera a estrutura de dados usada
    puts("\nObrigado por confiar em nosso sistema.");

    return 0;
}