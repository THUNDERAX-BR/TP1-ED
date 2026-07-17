#ifndef CARTEIRA_H
#define CARTEIRA_H

#include "Acao.h"
#include "TuplaOrdenacao.h"
#include <stdexcept>

//Representa a carteira do cliente como uma lista com referencias as acoes disponiveis no conjunto
class Carteira {
    private:
        //Classe interna exclusiva para armazenar referencias para acoes
        class NodeCarteira {
            public:
                Acao* dado;
                NodeCarteira* anterior;
                NodeCarteira* proximo;

                NodeCarteira(Acao* a);
        };

        NodeCarteira* inicio;
        NodeCarteira* fim;
        int tamanho;

        //Obtem o node do indice informado
        NodeCarteira* obterNode(int indice) const;
        //Obtem o node que contem acao com o id informado
        NodeCarteira* buscarPorId(int id) const;

    public:
        //Cria uma carteira vazia
        Carteira();
        //Limpa a carteira
        ~Carteira();

        //Insere a acao na carteira por referencia (presume-se que esteja alocada no conjunto geral)
        void comprar(Acao* acao);
        //Remove a referencia para a acao da carteira e desaloca o node utilizado
        void vender(int id);

        //Busca a acao com base no id e a retorna se estiver na carteira
        Acao* buscar(int id) const;

        //Define o operador [] com base no indice
        Acao* operator[](int indice);
        //Define o operador [] const com base no indic
        const Acao* operator[](int indice) const;

        //Retona o numero de acoes na carteira
        int getTamanho() const;
        //Retorna true se vazio
        bool vazio() const;

        //Remove todas as referencias para acoes da carteira e desaloca os nodes utilizados
        void limpar();

        //Retorna o vetor ordenado com base nos pesos e pontuacoes em cada metrica das acoes da carteira
        TuplaOrdenacao* ordenarCarteira(float pesoRet, float pesoAvgret, float pesoStab, float pesoCons);
};

#endif