#include <iostream>
#include <string>
#include <format>
#include <stdlib.h>
#include <mysql.h>
#include "cliente.h"
#include "chave_pix.h"

int main (int argc, char* argv[])
{

   // Initialize Connection
    MYSQL *conn;
    MYSQL_RES *res = new MYSQL_RES;
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

    Cliente cliente;
    int tela_atual = 0; //0=tela inicial
    bool rodando = true;
    int escolha;
    std::string query_str;

    while (rodando) {
        switch (tela_atual) {
            case 0: //tela inicial
                system("clear");
                printf("--SISTEMA DE BANCO--\n");
                printf("1) registrar conta.\n");
                printf("2) entrar em uma conta.\n");
                printf("3) depositar dinheiro.\n");
                printf("4) sair.\n");

                std::cin >> escolha;
                while (escolha<1 or escolha>4)  {
                    
                    
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
                    
                    case 4: //tela sair
                        system("clear");
                        std::cout << "realmente deseja sair?\n";
                        std::cout << "1) sim.\n";
                        std::cout << "2) nao.\n";
                        std::cin >> escolha;
                        if (escolha==1) {
                            rodando = false;
                        } else if (escolha==2) {
                            tela_atual = 0;
                        } else {
                            std::cout << "escolha invalida\n";
                        }
                        break;
                    
                    default:

                        break;
                }
                break;
            
            case 1:
                
                system("clear");
                std::cout << "--TELA DE REGISTRO--\n";
                std::cout << "nome: ";
                std::cin >> cliente.nome;

                std::cout << "cpf: ";
                std::cin >> cliente.cpf;

                std::cout << "email: ";
                std::cin >> cliente.email;

                std::cout << "senha: ";
                std::cin >> cliente.senha;

                std::cout << "data de nascimento(ano-mes-dia): ";
                std::cin >> cliente.data_nascimento;

                std::cout << "deposito inicial: ";
                std::cin >> cliente.saldo;
                query_str = std::format(
                    "INSERT INTO Clientes VALUES (UUID(), '{}', '{}', '{}', '{}', '{}', '{}')",
                    cliente.nome, cliente.email, cliente.senha, cliente.data_nascimento,
                    cliente.saldo, cliente.cpf);
                if (mysql_real_query(conn, query_str.c_str(), query_str.length())) {
                    std::cerr << "a querry falhou: " << mysql_error(conn) << "\n";
                    mysql_close(conn);
                    exit(1);
                }
                break;
            default:
                std::cerr << "tela atual invalida: " << tela_atual << std::endl;
                exit(1);
                break;
        }
    }

    mysql_free_result(res);
    mysql_close(conn);
   return 0;
}
