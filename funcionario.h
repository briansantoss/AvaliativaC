#ifndef FUNCIONARIO_H

typedef struct Funcionario {
    int matricula;
    char *nome;
    char *cargo;
    double salario;
    struct Funcionario *esq;
    struct Funcionario *dir;
} Funcionario;

void inserir_funcionario(Funcionario** funcionario, int matricula, const char* nome, const char* cargo, double salario);
void atualizar_funcionario(Funcionario* funcionario, int matricula_alvo, const char *novo_nome, const char *novo_cargo, double novo_salario);
void buscar_funcionario(Funcionario* funcionario, int matricula_alvo);
void listar_funcionarios(Funcionario* funcionario);
void limpar_cadastros(Funcionario* funcionario);

#endif