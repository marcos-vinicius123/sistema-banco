#pragma once
#include "chave_pix.h"
#include <string>
#include <ctime>

class Cliente {
    public:
        std::string get_nome();
        std::time_t get_data_nascimento();
        int get_saldo();

    private:
        std::string uuid;
        std::string nome;
        std::time_t data_nascimento;
        std::string cpf;
        std::string email;
        std::string senha;
        int saldo; //em centavos
};