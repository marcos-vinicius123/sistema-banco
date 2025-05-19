#include <iostream>
#include <stdlib.h>
#include <mysql.h>

int main (int argc, char* argv[])
{

   // Initialize Connection
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    if (!(conn = mysql_init(0))) {
        std::cerr << "falha ao inicializar conexao\n";
        exit(1);
    }

   // conecta com a database
    if (!mysql_real_connect(
        conn,                 // conexao
        "127.0.0.1",// Host
        "root",            // usuario
        "root",   // senha
        "banco",               // database
        3307,                 // Porta
        NULL,                 // socket file
        0                     // opcoes
    )) {
      // erro ao conectar com o servidor
        std::cerr << "erro conectando com o servidor: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        exit(1);
    }

    int tela_atual = 0; //0=tela inicial
    bool rodando = true;
    int escolha;

    while (rodando) {
        switch (tela_atual) {
            case 0:
                system("clear");
                printf("--SISTEMA DE BANCO--\n");
                printf("1) registrar conta.\n");
                printf("2) entrar em uma conta.\n");
                printf("3) depositar dinheiro.\n");
                printf("4) sair.\n");

                std::cin >> escolha;
                while (escolha<1 or escolha>4)  {
                    std::cout << "escolha invalida\n";
                    std::cin >> escolha;
                }

                switch (escolha) {
                    case 1:
                        tela_atual = 1;//tela de registro
                        break;
                    case 2:
                        tela_atual = 2;//tela de login
                        break;
                    
                    case 3:
                        tela_atual = 3;//tela de deposito
                        break;
                    
                    case 4:
                        rodando = false;
                        break;
                }
                break;
            default:
                std::cerr << "tela atual invalida: " << tela_atual << std::endl;
                break;
        }
    }
    
    mysql_free_result(res);
    mysql_close(conn);
   return 0;
}
