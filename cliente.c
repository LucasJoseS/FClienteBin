#include "cliente.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct CLIENTE cliente(unsigned short int indentificador, char nome[32], char status, float salario) {
    struct CLIENTE cliente;

    cliente.indentificador = indentificador;
    strcpy(cliente.nome, nome);
    cliente.status = status;
    cliente.salario = salario;

    return cliente;
}

void test_fcliente_file(char* filename, int create_if_not_exist) {
    FILE* fp = fopen(filename, "r");
    unsigned short int header = 0;

    if(fp == NULL && create_if_not_exist) {
        fp = fopen(filename, "w");
        fwrite((void*) &header, sizeof(unsigned short int), 1, fp);
    }

    fclose(fp);
}

int get_ccliente(char* filename) {
    FILE* fp = fopen(filename, "r");
    unsigned short int ccliente;

    fread((void*) &ccliente, sizeof(unsigned short int), 1, fp);
    fclose(fp);

    return ccliente;
}

struct FCLIENTE fcliente(char* filename) {
    struct FCLIENTE fcliente;

    test_fcliente_file(filename, 1);

    fcliente.ccliente = get_ccliente(filename);
    fcliente.filename = filename;

    return fcliente;
}

struct CLIENTE fcliente_create_cliente(struct FCLIENTE* fcliente, char* nome, char status, float salario) {
    struct CLIENTE cliente;

    cliente.indentificador = fcliente->ccliente+1;
    strcpy(cliente.nome, nome);
    cliente.status = status;
    cliente.salario = salario;

    return cliente;
}

void fcliente_append_cliente(struct FCLIENTE* fcliente, struct CLIENTE cliente) {
    FILE* fp = fopen(fcliente->filename, "r+");

    fwrite((void*) &cliente.indentificador, sizeof(unsigned short int), 1, fp);
    fcliente->ccliente=cliente.indentificador;

    fseek(fp, 0, SEEK_END);
    fwrite((void*) &cliente, sizeof(struct CLIENTE),1 , fp);

    fclose(fp);
}

struct CLIENTE fcliente_get_cliente(struct FCLIENTE* fcliente, unsigned short int N) {
    struct CLIENTE cliente;
    FILE* fp = fopen(fcliente->filename, "r");
    int pos = 2+sizeof(struct CLIENTE)*N;

    fseek(fp, pos, SEEK_SET);
    fread((void*) &cliente, sizeof(struct CLIENTE), 1, fp);
    fclose(fp);

    return cliente;
}

struct CLIENTE* fcliente_list_clientes(struct FCLIENTE* fcliente) {
    unsigned short int ccliente = fcliente->ccliente;
    struct CLIENTE* clientes = (struct CLIENTE*) malloc(sizeof(struct CLIENTE)*ccliente);

    for(int i=0; i<ccliente; i++) {
        clientes[i] = (struct CLIENTE) fcliente_get_cliente(fcliente, i);
    }

    return clientes;
}

void fcliente_edit_cliente(struct FCLIENTE* fcliente, struct CLIENTE cliente) {
    FILE* fp = fopen(fcliente->filename, "r+");
    int pos = 2+sizeof(struct CLIENTE)*(cliente.indentificador-1);

    fseek(fp, pos, SEEK_SET);
    fwrite((void*) &cliente, sizeof(struct CLIENTE), 1, fp);
    fclose(fp);
}

void fcliente_remove_cliente(struct FCLIENTE* fcliente, int indentificador) {
    struct CLIENTE* clientes = fcliente_list_clientes(fcliente);
    unsigned short int header = fcliente->ccliente-1;
    FILE* fp = fopen(fcliente->filename, "w");
    fcliente->ccliente-=1;
    
    fwrite((void*) &header, sizeof(unsigned short int), 1, fp);
    for(int i=0; i<fcliente->ccliente; i++) {
        if(clientes[i].indentificador != indentificador) {
            fwrite((void*) &clientes[i], sizeof(struct CLIENTE), 1, fp);
        }
    }

    fclose(fp);
}
