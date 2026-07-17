#include "TuplaOrdenacao.h"

TuplaOrdenacao::TuplaOrdenacao() : acao(nullptr), valor(0) {}

void TuplaOrdenacao::setValor(float valor) {
    this->valor = valor;
}

float TuplaOrdenacao::getValor() const {
    return valor;
}

void TuplaOrdenacao::setAcao(Acao* acao) {
    this->acao = acao;
}

Acao* TuplaOrdenacao::getAcao() const {
    return acao;
}