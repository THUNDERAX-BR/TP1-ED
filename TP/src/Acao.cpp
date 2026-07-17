#include "Acao.h"
#include <cmath>

Acao::Acao(int w, int id) : id(id), alteracoes(0), pontuacaoRet(0), pontuacaoAvgret(0), pontuacaoStab(0), pontuacaoCons(0) {
    this->cotacoes = new float[w]{};
}

Acao::~Acao() {
    delete[] cotacoes;
}

int Acao::getId() const {
    return id;
}

int Acao::getPontuacaoRet() const {
    return pontuacaoRet;
}

void Acao::setPontuacaoRet(int pontuacaoRet) {
    this->pontuacaoRet = pontuacaoRet;
}

int Acao::getPontuacaoAvgret() const {
    return pontuacaoAvgret;
}

void Acao::setPontuacaoAvgret(int pontuacaoAvgret) {
    this->pontuacaoAvgret = pontuacaoAvgret;
}

int Acao::getPontuacaoStab() const {
    return pontuacaoStab;
}

void Acao::setPontuacaoStab(int pontuacaoStab) {
    this->pontuacaoStab = pontuacaoStab;
}

int Acao::getPontuacaoCons() const {
    return pontuacaoCons;
}

void Acao::setPontuacaoCons(int pontuacaoCons) {
    this->pontuacaoCons = pontuacaoCons;
}

void Acao::addCotacao(int w, float cotacao) {
    cotacoes[alteracoes % w] = cotacao;
    alteracoes++;
}

float Acao::avgret(int w) {
    if (alteracoes < w) {
        w = alteracoes;
    }

    int inicio = alteracoes % w;
    float somatorio = 0;

    for (int i = 0; i < w - 1; i++){
        int idAtual = (inicio + i) % w;
        int idProximo = (inicio + i + 1) % w;

        somatorio += (cotacoes[idProximo] / cotacoes[idAtual] - 1);
    }

    return somatorio / (w - 1);
}

float Acao::stab(int w) {
    if (alteracoes < w) {
        w = alteracoes;
    }

    int inicio = alteracoes % w;
    float r = avgret(w);
    float vol = 0;

    for (int i = 0; i < w - 1; i++){
        int idAtual = (inicio + i) % w;
        int idProximo = (inicio + i + 1) % w;

        float ret = cotacoes[idProximo] / cotacoes[idAtual] - 1;
        vol += pow(ret - r, 2);
    }

    vol = sqrt(vol / (w - 1));

    return 1 / (1 + vol);
}

float Acao::ret(int w) {
    if (alteracoes < w) {
        w = alteracoes;
    }

    int idAntiga = alteracoes % w;
    int idRecente = (alteracoes - 1 + w) % w;

    return cotacoes[idRecente] / cotacoes[idAntiga] - 1;
}

float Acao::cons(int w) {
    if (alteracoes < w) {
        w = alteracoes;
    }

    int inicio = alteracoes % w;
    int positivos = 0;

    for (int i = 0; i < w - 1; i++){
        int idAtual = (inicio + i) % w;
        int idProximo = (inicio + i + 1) % w;

        float ret = cotacoes[idProximo] / cotacoes[idAtual] - 1;
        if (ret > 0) {
            positivos++;
        }
    }

    if (w <= 1) {
        return 0;
    }

    return static_cast<float>(positivos) / (w - 1);
}