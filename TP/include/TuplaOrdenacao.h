#ifndef TUPLAORDENACAO_H
#define TUPLAORDENACAO_H

#include "Acao.h"

//Par ordenado com um valor para criterio da ordenacao e a respectiva acao
class TuplaOrdenacao {
    private:
        Acao* acao;
        float valor;
    public:
        //Cria um objeto com valores nulos
        TuplaOrdenacao();

        //Altera o valor para o informado
        void setValor(float valor);
        //Retorna o valor a ser ordenado
        float getValor() const;
        
        //Altera a acao para a informada
        void setAcao(Acao* acao);
        //Retorna a respectiva acao
        Acao* getAcao() const;
};

#endif