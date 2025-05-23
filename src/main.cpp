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
    int *num_fields;
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
    int deposito;
    std::string deposito_cpf;
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
                if (escolha<1 or escolha>4)  {
                    break; 
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
            
            case 1:  //tela de registro
                
                system("clear");
                std::cout << "--TELA DE REGISTRO--\n";
                std::cout << "nome: ";

                std::getline(std::cin >> std::ws, cliente.nome);

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
                tela_atual = 0;
                break;
            
            case 2: //tela de login
                system("clear");
                std::cout << "--TELA DE LOGIN--\n";
                std::cout << "cpf: ";
                std::cin >> cliente.cpf;
                std::cout << "senha: ";
                std::cin >> cliente.senha;

                query_str = std::format(
                    "SELECT * FROM Clientes WHERE cpf = '{}' AND senha = '{}'", cliente.cpf, cliente.senha);
                if (mysql_real_query(conn, query_str.c_str(), query_str.length())) {
                    std::cerr << "a query falhou: " << mysql_error(conn) << "\n";
                    mysql_close(conn);
                    exit(1);
                }

                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                if (row==NULL) {
                    std::cout << "senha ou cpf invalidos\n";
                    std::cin >> std::ws;
                } else {

                    cliente.uuid = row[0];
                    cliente.nome = row[1];
                    cliente.email = row[2];
                    cliente.senha = row[3];
                    cliente.data_nascimento = row[4];
                    cliente.saldo = std::stoi(row[5]);
                    cliente.cpf = row[6];
                    tela_atual = 4;
                }
                mysql_free_result(res);
                break;
            
            case 3: //tela de deposito
                std::cout << "--TELA DE DEPOSITO--\n";
                std::cout << "valor em centavos\n";
                std::cout << "cpf: ";
                std::cin >> deposito_cpf;
                std::cout << "deposito: ";
                std::cin >> deposito;
                query_str = std::format("UPDATE Clientes SET saldo = saldo+{} WHERE cpf='{}' ", deposito, deposito_cpf);
                if (mysql_real_query(conn, query_str.c_str(), query_str.length())) {
                    std::cerr << "a querry falhou: " << mysql_error(conn) << "\n";
                    mysql_close(conn);
                    exit(1);
                }
                tela_atual = 0; //tela inicial
                break;
            
            case 4: //tela do cliente
                std::cout << "--TELA DO CLIENTE--" << std::endl;
                std::cout << "bem vindo " << cliente.nome << std::endl;
                std::cout <<  std::format("saldo: ${},{}", cliente.saldo/100, cliente.saldo%100) << std::endl;

                std::cin >> std::ws;
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
