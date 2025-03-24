#include <stdio.h>
#include <stdlib.h>
#include "funcionario.h"
#include <string.h>

void inserir_funcionario(Funcionario** funcionario, int matricula, const char *nome, const char *cargo, double salario) {
    if (!*funcionario) {
        // Reserva espaço para o novo funcionário na memória
        Funcionario *novo_funcionario = (Funcionario*) malloc(sizeof (Funcionario));
        if (!novo_funcionario) { // Se a alocação falhar a função devolve o controle de fluxo à invocadora
            fprintf(stderr, "\nErro: nao foi possivel registrar o funcionario.");
            return; 
        }     
        
        novo_funcionario->nome = (char*) malloc(sizeof (nome) + 1); // Reserva espaço para o nome
        if (!novo_funcionario->nome) {
            free(novo_funcionario); // Libera a memória utilizada pelo novo funcionário
            fprintf(stderr, "\nErro: nao foi possivel registrar o funcionario.");
        }
        strcpy(novo_funcionario->nome, nome); // Atribui o nome ao usuário
        
        novo_funcionario->cargo = (char*) malloc(sizeof (cargo) + 1); // Reserva espaço para o cargo
        if (!novo_funcionario->cargo) {
            // Libera a memória utilizada pelas alocações anteriores
            free(novo_funcionario->nome);
            free(novo_funcionario); 
            fprintf(stderr, "\nErro: nao foi possivel registrar o funcionario.");
        }
        strcpy(novo_funcionario->cargo, cargo); // Atribui o cargo ao funcionário

        // Inicializa os dois filhos com NULL
        novo_funcionario->esq = novo_funcionario->dir = NULL;

        // Atribui salário e matrícula
        novo_funcionario->matricula = matricula;
        novo_funcionario->salario = salario;

        *funcionario = novo_funcionario; // Preenche o nó atual com os dados do novo funcionario

        puts("\nFuncionario registrado com sucesso."); 
        return; // Retorna previamente, evitando mais chamadas recursivas 
    }

    // Percorre as subárvores com base na comparação entre a matrícula da raiz e a para ser inserida
    if (matricula < (*funcionario)->matricula) {
        inserir_funcionario(&((*funcionario)->esq), matricula, nome, cargo, salario);
    } else if (matricula > (*funcionario)->matricula) {
        inserir_funcionario(&((*funcionario)->dir), matricula, nome, cargo, salario);
    } else { // Trata duplicatas (identificadas com base no número inteiro da matrícula)
        fprintf(stderr, "\nErro: numero de matricula duplicado.");
        return;
    } 
}

void atualizar_funcionario(Funcionario* funcionario, int matricula_alvo, const char* novo_nome, const char* novo_cargo, double novo_salario)  {
    if (funcionario) { // Verifica se o nó não é nulo
        // Comparações entre a matrícula atual e a buscada
        if (matricula_alvo < funcionario->matricula) {
            buscar_funcionario(funcionario->esq, matricula_alvo);
        } else if (matricula_alvo > funcionario->matricula) {
            buscar_funcionario(funcionario->dir, matricula_alvo);
        } else {
            char* antigo_nome = funcionario->nome;
            funcionario->nome = (char*) malloc(sizeof (novo_nome) + 1); // Reserva espaço para o novo nome
            if (!funcionario->nome) {          // Libera a memória utilizada pelas alocações anteriores
                funcionario->nome = antigo_nome;
                fprintf(stderr, "\nErro: nao foi possivel atualizar o funcionario.");
            }
            strcpy(funcionario->nome, novo_nome); // Atribui o cargo ao funcionário
        
            // Faz o mesmo para o cargo
            char* antigo_cargo = funcionario->cargo;
            funcionario->cargo = (char*) malloc(sizeof (novo_cargo) + 1);
            if (!funcionario->cargo) {
                funcionario->nome = antigo_nome; // Desfaz a alteração do nome
                fprintf(stderr, "\nErro: nao foi possivel atualizar o funcionario.");
            }
            strcpy(funcionario->cargo, novo_cargo); // Atribui o cargo ao funcionário
            
            // Libera a memória usada pelas antigas alocações de cargo e nome
            free(antigo_nome);
            free(antigo_cargo);

            // Atualiza o salário
            funcionario->salario = novo_salario;

            return; // Retorno prévio evitando mais chamadas recursivas
        }
    }
}

void buscar_funcionario(Funcionario* funcionario, int matricula_alvo) {
    if (funcionario) { // Verifica se o nó não é nulo
        // Comparações entre a matrícula atual e a buscada
        if (matricula_alvo < funcionario->matricula) {
            buscar_funcionario(funcionario->esq, matricula_alvo);
        } else if (matricula_alvo > funcionario->matricula) {
            buscar_funcionario(funcionario->dir, matricula_alvo);
        } else {
            puts("\nO funcionario foi encontrado!");
            printf("\nMatricula: %d\nNome: %s\nCargo: %s\nSalario: %.2lf", funcionario->matricula, funcionario->nome, funcionario->cargo, funcionario->salario);
            return; // Retorno prévio evitando mais chamadas recursivas
        }
    }
}

// Lista os usuários percorrendo as sub árvore primeiro e depois a raiz (pós-ordem)
void listar_funcionarios(Funcionario *funcionario) {
    if (funcionario) {
        listar_funcionarios(funcionario->esq);
        listar_funcionarios(funcionario->dir);
        printf("\nMatricula: %d\nNome: %s\nCargo: %s\nSalario: %.2lf\n", funcionario->matricula, funcionario->nome, funcionario->cargo, funcionario->salario);
    }
}

// Libera a memória das subárvores e depois da raiz
void limpar_cadastros(Funcionario* funcionario) {
    if (funcionario) {
        limpar_cadastros(funcionario->esq);
        limpar_cadastros(funcionario->dir);
        free(funcionario);
    }
}