#pragma once
#include <string>
#include <ctime>

struct Transferencia {
    std::string uuid;
    std::string origem_nome;
    std::string origem_cpf;
    std::string destino_nome;
    std::string destino_chave;
    std::time_t data;
    std::string origem_uuid;
    std::string destino_uuid;
};