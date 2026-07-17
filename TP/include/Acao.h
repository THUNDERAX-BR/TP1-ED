#ifndef ACAO_H
#define ACAO_H

#include <stdexcept>

//Representa uma acao, matendo as cotacoes e pontuacoes em cada metrica
class Acao {
    private:
        int id;
        float* cotacoes;
        int alteracoes;

        int pontuacaoRet;
        int pontuacaoAvgret;
        int pontuacaoStab;
        int pontuacaoCons;
        
    public:
        //Recebe o valor de w e o id e cria uma Acao, aloca um vetor de tamanho w para armazenar as cotacoes, inicia cada valor com 0
        Acao(int w, int id);
        //Desaloca o vetor de cotacoes
        ~Acao();

        //Retorna o id
        int getId() const;

        //Retorna a pontuacao da acao para a metrica RET
        int getPontuacaoRet() const;
        //Define a pontuacao da acao para a metrica RET
        void setPontuacaoRet(int pontuacaoRet);
        //Retorna a pontuacao da acao para a metrica AVGRET
        int getPontuacaoAvgret() const;
        //Define a pontuacao da acao para a metrica AVGRET
        void setPontuacaoAvgret(int pontuacaoAvgret);
        //Retorna a pontuacao da acao para a metrica STAB
        int getPontuacaoStab() const;
        //Define a pontuacao da acao para a metrica STAB
        void setPontuacaoStab(int pontuacaoStab);
        //Retorna a pontuacao da acao para a metrica CONS
        int getPontuacaoCons() const;
        //Define a pontuacao da acao para a metrica CONS
        void setPontuacaoCons(int pontuacaoCons);

        //Adiciona a cotacao na ultima posição do vetor circular, substituindo a cotacao mais antiga usando alteracoes mod (w), incrementa alteracoes em 1
        void addCotacao(int w, float cotacao);
        
        //Calcula a metrica AVGRET com base em w e nas cotacoes
        float avgret(int w);
        //Calcula a metrica STAB com base em w e nas cotacoes
        float stab(int w);
        //Calcula a metrica RET com base em w e nas cotacoes
        float ret(int w);
        //Calcula a metrica CONS com base em w e nas cotacoes
        float cons(int w);
};

#endif