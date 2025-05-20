#pragma once
#include <string>

struct Cliente {
    std::string uuid;
    std::string nome;
    std::string data_nascimento;
    std::string cpf;
    std::string email;
    std::string senha;
    int saldo; //em centavos
};