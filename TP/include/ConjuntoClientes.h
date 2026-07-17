#ifndef CONJUNTOCLIENTES_H
#define CONJUNTOCLIENTES_H

#include "Cliente.h"
#include <stdexcept>

//Lista com todos os clientes
class ConjuntoClientes {
    private:
        //Classe interna exclusiva para armazenar clientes
        class NodeConjuntoClientes {
            public:
                Cliente* dado;
                NodeConjuntoClientes* anterior;
                NodeConjuntoClientes* proximo;

                NodeConjuntoClientes(Cliente* c);
        };

        NodeConjuntoClientes* inicio;
        NodeConjuntoClientes* fim;
        int tamanho;

        bool fechado;

        //Obtem o node do indice informado
        NodeConjuntoClientes* obterNode(int indice) const;
        //Obtem o node que contem acao com o id informado
        NodeConjuntoClientes* buscarPorId(int id) const;

    public:
        //Cria um conjunto vazio
        ConjuntoClientes();
        //Limpa o conjunto
        ~ConjuntoClientes();

        //Insere um cliente alocado no heap no conjunto
        void inserir(Cliente* cliente);

        //Impede novos clientes de serem adicionadas,
        //so pode ser chamado uma vez apos todas as linhas U terem sido lidas
        void fecharConjunto();

        //Busca o cliente com base no id e o retorna se existir
        Cliente* buscar(int id) const;

        //Define o operador [] com base no indice para facilidade
        Cliente& operator[](int indice);
        //Define o operador [] const com base no indice para facilidade
        const Cliente& operator[](int indice) const;

        //Retona o numero de acoes armazenadas
        int getTamanho() const;
        //Retorna true se vazio
        bool vazio() const;

        //Desaloca os clientes e nodes da memoria e remove todos do conjunto
        void limpar();
};

#endif