cmake_minimum_required(VERSION 3.27)
project(projeto_gestao_de_eventos C)

include_directories(cJSON)


set(CMAKE_C_STANDARD 11)

add_executable(projeto_gestao_de_eventos main.c
        produto.c
        produto.h
        usuario.c
        usuario.h
        venda.c
        venda.h
        evento.c
        evento.h
        menu.c
        menu.h
        venda_detalhes.c
        venda_detalhes.h
        login.c
        login.h
        cJSON/cJSON.c
        variaveis_compartilhadas.c
        variaveis_compartilhadas.h
)
