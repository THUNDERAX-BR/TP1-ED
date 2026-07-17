#ifndef CONJUNTOACOES_H
#define CONJUNTOACOES_H

#include "Acao.h"
#include "TuplaOrdenacao.h"
#include <stdexcept>

//Lista com todas as acoes e vetores para ordenacoes com base nas matricas
class ConjuntoAcoes {
    private:
        //Classe interna exclusiva para armazenar acoes
        class NodeConjuntoAcoes {
            public:
                Acao* dado;
                NodeConjuntoAcoes* anterior;
                NodeConjuntoAcoes* proximo;

                NodeConjuntoAcoes(Acao* a);
        };

        NodeConjuntoAcoes* inicio;
        NodeConjuntoAcoes* fim;
        int tamanho;

        bool fechado;

        //Vetores para ordenacao dos rankings de metricas
        TuplaOrdenacao* rankingRet;
        TuplaOrdenacao* rankingAvgret;
        TuplaOrdenacao* rankingStab;
        TuplaOrdenacao* rankingCons;

        //Obtem o node com indice informado
        NodeConjuntoAcoes* obterNode(int indice) const;
        //Obtem o node que contem acao com o id informado
        NodeConjuntoAcoes* buscarPorId(int id) const;

        //Atualiza o valor da tupla com valor da funcao de metrica, returna true se foi alterado
        bool atualizarTupla(int w, TuplaOrdenacao& tupla, float (Acao::*funcMetrica)(int)) const;

        //Funcao com o procedimento padrao para ordenar o vetor com base na funcao da matrica e atribuir a pontuacao em cada acao, recebe w e os parametros de uma unica metrica
        void ordenarEPontuarMetrica(int w, TuplaOrdenacao* ranking, float (Acao::*funcMetrica)(int), void (Acao::*setPontuacao)(int));

    public:
        //Cria um conjunto vazio
        ConjuntoAcoes();
        //Limpa o conjunto e desaloca os vetores de ranking
        ~ConjuntoAcoes();

        //Insere uma acao alocada no heap no conjunto
        void inserir(Acao* acao);

        //Cria os vetores de ordenacao com base no numero de acoes atuais e impede novas acoes de serem adicionadas,
        //so pode ser chamado uma vez apos todas as linhas A terem sido lidas
        void fecharConjunto();

        //Busca a acao com base no id e a retorna se existir
        Acao* buscar(int id) const;

        //Define o operador [] com base no indice para facilidade
        Acao* operator[](int indice);
        //Define o operador [] const com base no indice para facilidade
        const Acao* operator[](int indice) const;

        //Retona o numero de acoes armazenadas
        int getTamanho() const;
        //Retorna true se vazio
        bool vazio() const;

        //Desaloca as acoes e nodes da memoria e remove todos do conjunto
        void limpar();

        //Atualiza os valores das tuplas e ordena o vetor da metrica RET caso tenha mudado, atualizando a pontuacao em cada acao
        void ordenarRet(int w);
        //Atualiza os valores das tuplas e ordena o vetor da metrica AVGRET caso tenha mudado, atualizando a pontuacao em cada acao
        void ordenarAvgret(int w);
        //Atualiza os valores das tuplas e ordena o vetor da metrica STAB caso tenha mudado, atualizando a pontuacao em cada acao
        void ordenarStab(int w);
        //Atualiza os valores das tuplas e ordena o vetor da metrica CONS caso tenha mudado, atualizando a pontuacao em cada acao
        void ordenarCons(int w);
};

#endif