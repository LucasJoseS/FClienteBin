struct CLIENTE {
    unsigned short int indentificador;
    char nome[32];
    char status;
    float salario;
};

struct FCLIENTE {
    unsigned short int ccliente;
    char* filename;
};

struct CLIENTE cliente(unsigned short int indentificador, char nome[32], char status, float salario);
struct FCLIENTE fcliente(char* filename);

struct CLIENTE fcliente_create_cliente(struct FCLIENTE* fcliente, char* nome, char staus, float salario);
struct CLIENTE* fcliente_list_clientes(struct FCLIENTE* fcliente);
void fcliente_append_cliente(struct FCLIENTE* fcliente, struct CLIENTE cliente);
void fcliente_edit_cliente(struct FCLIENTE* fcliente, struct CLIENTE cliente);
void fcliente_remove_cliente(struct FCLIENTE* fcliente, int pos);
