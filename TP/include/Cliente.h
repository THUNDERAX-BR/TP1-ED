#ifndef CLIENTE_H
#define CLIENTE_H

#include "Carteira.h"

//Representa um cliente com id e carteira
class Cliente {
    private:
        int id;
        Carteira carteira;
        
    public:
        //Cria um objeto cliente com o id informado
        Cliente(int id);
        //Retorna o id do cliente
        int getId() const;
        //Retorna referencia para a carteira do cliente
        Carteira& getCarteira();
};

#endif