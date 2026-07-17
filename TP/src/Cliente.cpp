#include "Cliente.h"

Cliente::Cliente(int id) : id(id) {}

int Cliente::getId() const {
    return id;
}

Carteira& Cliente::getCarteira() {
    return carteira;
}