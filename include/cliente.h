#pragma once
#include <string>
#include <ctime>

class Cliente {
    private:
        std::string uuid;
        std::string nome;
        std::time_t data_nascimento;
        std::string email;
        std::string senha;
        int balanca;
};