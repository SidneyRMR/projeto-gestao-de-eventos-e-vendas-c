#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "usuario.h"

void criarUsuario() {
    Usuario usuario;
    char p_nome[51]; // Array de caracteres para armazenar o nome do usuário
    char p_login[21]; // Array de caracteres para armazenar o login do usuário
    char p_senha[11]; // Array de caracteres para armazenar a senha do usuário
    char p_tipo[15]; // Array de caracteres para armazenar o tipo do usuário
    int p_status = 1; // Status padrão do usuário

    int opcaoTipo = 0;

    printf("=======================================================\n");
    printf("|             TELA DE CADASTRO DE USUARIO             |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|\tDigite o NOME: ");
    scanf(" %50[^\n]", p_nome);
    printf("|\tDigite o LOGIN: ");
    scanf(" %20[^\n]", p_login);
    printf("|\tDigite A SENHA: ");
    scanf(" %10[^\n]", p_senha);
    printf("|\tEscolha o tipo de usuario:                    |\n");
    printf("|\t\t1. Vendedor                           |\n");
    printf("|\t\t2. Administrador                      |\n");
    printf("|     Escolha: ");
    scanf("%d", &opcaoTipo);
    printf("|-----------------------------------------------------|\n");

    // Solicitar ao usuário que escolha o tipo de usuário
    while (opcaoTipo != 1 && opcaoTipo != 2) {
        printf("Escolha o tipo de usuario: \n"
               "\t 1. Vendedor\n"
               "\t 2. Administrador\n"
               "\t Escolha: ");
        scanf("%d", &opcaoTipo);
    }

    // Determinar o tipo do usuário com base na escolha do usuário
    switch (opcaoTipo) {
        case 1:
            strcpy(p_tipo, "vendedor");
            break;
        case 2:
            strcpy(p_tipo, "administrador");
            break;
    }

    // Preencher a estrutura do usuário com os dados inseridos
    usuario.id = carregarUltimoUsuario(); // Incrementar o ID do último usuário
    strcpy(usuario.nome, p_nome);
    strcpy(usuario.login, p_login);
    strcpy(usuario.senha, p_senha);
    strcpy(usuario.tipo, p_tipo);
    usuario.status = p_status;
    usuario.id_evento = 1; // TODO - Preciso receber como parâmetro

    salvarUsuario(usuario);
}


int listarUsuarios() {
    FILE *file;
    char filename[] = "data/usuarios.txt";
    file = fopen(filename, "r");

    if (file != NULL) {
        //printf("Arquivo foi aberto com sucesso.\n\n");

        // Imprimir cabeçalho da tabela

        printf("|-------------------------------------------------------------------------------------------------------------------|\n");
        printf("|                                                 LISTA DE USUARIOS                                                 |\n");
        printf("|-------------------------------------------------------------------------------------------------------------------|\n");
        printf("| %-3s | %-38s | %-15s | %-10s | %-14s | %-7s | %-8s |\n", "Cod", "Nome", "Login", "Senha", "Tipo", "Status", "Evento");
        printf("|-------------------------------------------------------------------------------------------------------------------|\n");

        Usuario usuario;
        char aux_senha[20]; // Ajuste o tamanho conforme necessário

// Ler e exibir cada linha do arquivo
        while (fscanf(file, "%d '%[^']' %s %s %s %d %d", &usuario.id, usuario.nome, usuario.login, usuario.senha, usuario.tipo, &usuario.status, &usuario.id_evento) != EOF) {
            strcpy(aux_senha, "******"); // Definir uma senha fictícia para exibição
            printf("| %-3d | %-38s | %-15s | %-10s | %-14s | %-7d | %-8d |\n", usuario.id, usuario.nome, usuario.login, aux_senha, usuario.tipo, usuario.status, usuario.id_evento);
        }


        printf("|-------------------------------------------------------------------------------------------------------------------|\n");

        fclose(file);
    } else {
        perror("Não foi possível abrir o arquivo %s.\n\n");
    }

    return 0;
}

int carregarUltimoUsuario() {
    FILE *file;
    char filename[] = "data/usuarios.txt";
    file = fopen(filename, "r");

    int contador_linhas = 0;

    if (file != NULL) {
        int c;
        // Percorrer o arquivo caractere por caractere
        while ((c = fgetc(file)) != EOF) {
            if (c == '\n') {
                ++contador_linhas;
            }
        }
        fclose(file);
        //printf("Registro %d\n", contador_linhas);
    } else {
        printf("Erro ao abrir o arquivo %s.\n", filename);
    }

    return contador_linhas+1;
}

void salvarUsuario(Usuario usuario) {
    FILE *file;
    char filename[] = "data/usuarios.txt";
    file = fopen(filename, "a"); // Abrir o arquivo em modo de escrita, acrescentando ao final

    if (file != NULL) {
        fprintf(file, "%d '%s' %s %s %s %d %d\n", usuario.id, usuario.nome, usuario.login, usuario.senha, usuario.tipo, usuario.status, usuario.id_evento);
        fclose(file);
        printf("Usuario salvo com sucesso!\n");
    } else {
        printf("Erro ao abrir o arquivo %s.\n", filename);
    }
}


Usuario consultarUsuarioPorID(int id) {
    FILE *file;
    char filename[] = "data/usuarios.txt";
    file = fopen(filename, "r"); // Abrir o arquivo em modo de leitura

    if (file != NULL) {
        Usuario usuario;
        int encontrado = 0;

        // Lê cada usuário do arquivo até encontrar o usuário com o ID correspondente
        while (fscanf(file, "%d '%49[^']' %19s %19s %19s %d %d\n", &usuario.id, usuario.nome, usuario.login,
                      usuario.senha, usuario.tipo, &usuario.status, &usuario.id_evento) != EOF) {
            if (usuario.id == id) {
                encontrado = 1;
                fclose(file);
                return usuario;
            }
        }

        fclose(file);
        if (!encontrado) {
            printf("Usuário com ID %d não encontrado.\n", id);
        }
    } else {
        printf("Erro ao abrir o arquivo %s.\n", filename);
    }

    Usuario usuario_vazio; // Retorna um usuário vazio se não encontrar
    usuario_vazio.id = -1; // Ou outro valor que você considerar adequado
    return usuario_vazio;
}
