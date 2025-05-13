#include "cliente.h"
#include <string>
#include <ctime>

std::string Cliente::get_nome() {
    return nome;
}

std::time_t Cliente::get_data_nascimento() {
    return data_nascimento;
}

int Cliente::get_saldo() {
    return saldo;
}