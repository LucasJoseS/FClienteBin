#include "cliente.h"
#include <stdio.h>

// TODO
// [y] Adicionar registro de cliente
// [y] Listar registros cadastrados
// [y] Editar registro unico
// [y] Remover registro unico
// [y] Menu principal

void draw_sep() {
    for(int i=0; i< 74; i++) {
        printf("-");
    }
    printf("\n");
}

int menu(int n) {
    int opt = -1;
    switch(n) {
        case 1:
            printf("                            Listando registros\n");
            break;
        case 2:
            printf("            Adicionando registo\nDigite [nome] [status] [renda]\n");
            break;
        case 3:
            printf("                Qual o registro a ser editado [indentificador]\n");
            break;
        case 4:
            printf("               Qual o registro a ser removido [indentificador]\n");
            break;
        default:
            printf("O que deseja fazer?\n1 - Listar registros\n2 - Adicionar registro\n3 - Editar registro\n4 - Remover registro\n9 - Sair\nOpção?:");
            scanf("%d", &opt);
            break;

    }

    return opt;
}

int main(int argc, char** argv) {
    if(argc != 2) {
        printf("Utilize:\napp [nome do arquivo]\n");
        return -1;
    }
    struct FCLIENTE f = fcliente(argv[1]);
    struct CLIENTE c;
    unsigned short int indentificador;
    char nome[32];
    char status;
    float renda;

    int opt;
    draw_sep();
    do {
        opt = menu(0);

        switch(opt) {
            case 1:
                draw_sep();
                menu(opt);
                if(f.ccliente != 0) {
                    struct CLIENTE* clientes = fcliente_list_clientes(&f);
                    if(f.ccliente != 0) {
                        printf("| Indentificador |               Nome               | Status |   Renda   |\n");
                        for(int i=0; i<f.ccliente; i++) {
                            c = clientes[i];
                            printf("| %14hu | %32s | %6c | %9.2f |\n", c.indentificador, c.nome, c.status, c.salario);
                        }
                    }
                }
                else {
                    printf("Não há registros\n");
                }
                draw_sep();
                break;

            case 2:
                draw_sep();
                menu(opt);
                printf("Nome: ");
                getchar();
                gets(nome);

                printf("Satus: ");
                scanf("%c", &status);
                getchar();

                printf("Renda: ");
                scanf("%f", &renda);

                c = fcliente_create_cliente(&f, nome, status, renda);
                fcliente_append_cliente(&f, c);
                draw_sep();
                break;

            case 3:
                draw_sep();
                menu(opt);
                printf("Indentificador: ");
                scanf("%hu", &indentificador);

                printf("Novo Nome: ");
                getchar();
                gets(nome);

                printf("Novo Satus: ");
                scanf("%c", &status);
                getchar();

                printf("Nova Renda: ");
                scanf("%f", &renda);
                
                c = cliente(indentificador, nome, status, renda);
                fcliente_edit_cliente(&f, c);
                draw_sep();
                break;

            case 4:
                draw_sep();
                menu(opt);
                printf("Indentificador: ");
                scanf("%hu", &indentificador);
                getchar();

                fcliente_remove_cliente(&f, indentificador);
                draw_sep();
                break;
        }

    } while(opt != 9);
}
