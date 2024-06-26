#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "login.h"
#include "menu.h"
#include "variaveis_compartilhadas.h"

#define MAX_USUARIOS 100 // Defina o número máximo de usuários
struct Usuario {
    int id;
    char nome[51];
    char login[21];
    char senha[11];
    char tipo[15];
    int status;
    int id_evento;
};

struct Usuario usuarios[MAX_USUARIOS]; // Declaração do array de usuários
int numUsuarios = 0; // Variável para rastrear o número atual de usuários

// Função para carregar os usuários do arquivo usuarios.txt
void carregarUsuarios() {
    FILE *file;
    char filename[] = "data/usuarios.txt";
    file = fopen(filename, "r");

    if (file != NULL) {
        while (fscanf(file, "%d '%49[^']' %19s %19s %19s %d %d",
                      &usuarios[numUsuarios].id,
                      usuarios[numUsuarios].nome,
                      usuarios[numUsuarios].login,
                      usuarios[numUsuarios].senha,
                      usuarios[numUsuarios].tipo,
                      &usuarios[numUsuarios].status,
                      &usuarios[numUsuarios].id_evento) == 7) {
            numUsuarios++;
        }
        fclose(file);
    } else {
        perror("Erro ao abrir o arquivo de usuários");
        exit(1);
    }
}


struct Usuario usuarios[MAX_USUARIOS]; // Declaração da matriz de usuários

int loginAux() {
    char usuario[21];
    char senha[21];

    printf("=======================================================\n");
    printf("|          TELA DE LOGIN - GESTAO DE EVENTOS          |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|\tDigite seu usuario: ");
    scanf(" %20s", usuario);

    printf("|\tDigite sua senha: ");
    scanf(" %20s", senha);

    printf("|-----------------------------------------------------|\n");

    for (int i = 0; i < numUsuarios; i++) {
        if(strcmp(usuario, usuarios[i].login) == 0 && strcmp(senha, usuarios[i].senha) == 0) {
            printf("|\tLogin efetuado com sucesso como %s\n", usuario);

            setNomeUsuarioCompartilhado(usuario);
            escolherMenu();
            return 1;
        }
    }
    printf("|\tLogin invalido, tente novamente.\n");
    system("cls");
    return 0;
}

// Função de login
void login() {
    carregarUsuarios(); // Carregar os usuários do arquivo
    int tentativas = 3;
    while (tentativas > 0) {
        if (loginAux()) {
            // Se o login for bem-sucedido, sair da função
            return;
        } else {
            tentativas--;
            printf("|\t\tVoce tem %d tentativas restantes.\n\n", tentativas);
        }
    }
    printf("|\tNumero maximo de tentativas excedido. Saindo...\n");
    system("PAUSE");
    exit(1);
}

