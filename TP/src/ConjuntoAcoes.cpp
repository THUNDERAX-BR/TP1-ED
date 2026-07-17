#include "ConjuntoAcoes.h"
#include "Ordenacao.h"

//Node
ConjuntoAcoes::NodeConjuntoAcoes::NodeConjuntoAcoes(Acao* a) : dado(a), anterior(nullptr), proximo(nullptr) {}

//ConjuntoAcoes
ConjuntoAcoes::ConjuntoAcoes() : inicio(nullptr), fim(nullptr), tamanho(0), fechado(false) {}

ConjuntoAcoes::~ConjuntoAcoes() {
    if (rankingRet) delete[] rankingRet;
    if (rankingAvgret) delete[] rankingAvgret;
    if (rankingStab) delete[] rankingStab;
    if (rankingCons) delete[] rankingCons;
    limpar();
}

void ConjuntoAcoes::inserir(Acao* acao) {
    if (fechado) {
        throw std::invalid_argument("Conjunto de acoes fechado!");
    }

    if (!acao) {
        throw std::invalid_argument("Acao nula!");
    }

    if (acao->getId() != tamanho) {
        throw std::runtime_error("Acao com id invalido!");
    }

    NodeConjuntoAcoes* novo = new NodeConjuntoAcoes(acao);

    if (!inicio) {
        inicio = fim = novo;
    } else {
        fim->proximo = novo;
        novo->anterior = fim;
        fim = novo;
    }

    tamanho++;
}

void ConjuntoAcoes::fecharConjunto() {
    if (fechado) {
        throw std::invalid_argument("Conjunto de acoes ja esta fechado!");
    }

    if (tamanho == 0) {
        throw std::invalid_argument("Nao e possivel fechar conjunto de acoes vazio!");
    }

    rankingRet = new TuplaOrdenacao[tamanho];
    for (int i = 0; i < tamanho; i++) {
        rankingRet[i].setAcao((*this)[i]);
    }

    rankingAvgret = new TuplaOrdenacao[tamanho];
    for (int i = 0; i < tamanho; i++) {
        rankingAvgret[i].setAcao((*this)[i]);
    }

    rankingStab = new TuplaOrdenacao[tamanho];
    for (int i = 0; i < tamanho; i++) {
        rankingStab[i].setAcao((*this)[i]);
    }

    rankingCons = new TuplaOrdenacao[tamanho];
    for (int i = 0; i < tamanho; i++) {
        rankingCons[i].setAcao((*this)[i]);
    }

    fechado = true;
}

ConjuntoAcoes::NodeConjuntoAcoes* ConjuntoAcoes::buscarPorId(int id) const {
    NodeConjuntoAcoes* atual = inicio;

    while (atual) {
        if (atual->dado->getId() == id)
            return atual;
        atual = atual->proximo;
    }

    return nullptr;
}

Acao* ConjuntoAcoes::buscar(int id) const {
    NodeConjuntoAcoes* no = buscarPorId(id);
    if (!no) {
        throw std::runtime_error("Acao nao encontrada!");
    }
    return no->dado;
}

ConjuntoAcoes::NodeConjuntoAcoes* ConjuntoAcoes::obterNode(int indice) const {
    if (indice < 0 || indice >= tamanho) {
        throw std::out_of_range("Indice fora dos limites!");
    }

    NodeConjuntoAcoes* atual;

    //Busca bidirecional
    if (indice < tamanho / 2) {
        atual = inicio;
        for (int i = 0; i < indice; i++)
            atual = atual->proximo;
    } else {
        atual = fim;
        for (int i = tamanho - 1; i > indice; i--)
            atual = atual->anterior;
    }

    return atual;
}

Acao* ConjuntoAcoes::operator[](int indice) {
    return obterNode(indice)->dado;
}

const Acao* ConjuntoAcoes::operator[](int indice) const {
    return obterNode(indice)->dado;
}

void ConjuntoAcoes::limpar() {
    NodeConjuntoAcoes* atual = inicio;

    while (atual) {
        NodeConjuntoAcoes* temp = atual;
        atual = atual->proximo;

        delete temp->dado;
        delete temp;
    }

    inicio = fim = nullptr;
    tamanho = 0;
}

int ConjuntoAcoes::getTamanho() const {
    return tamanho;
}

bool ConjuntoAcoes::vazio() const {
    return tamanho == 0;
}


bool ConjuntoAcoes::atualizarTupla(int w, TuplaOrdenacao& tupla, float (Acao::*funcMetrica)(int)) const {
    float atual = tupla.getValor();
    float novo = (tupla.getAcao()->*funcMetrica)(w);

    if (novo != atual) {
        tupla.setValor(novo);
        return true;
    }

    return false;
}


void ConjuntoAcoes::ordenarEPontuarMetrica(int w, TuplaOrdenacao* ranking, float (Acao::*funcMetrica)(int), void (Acao::*setPontuacao)(int)) {
    if (tamanho < 1) {
        return;
    }

    bool alterado = false;

    //Atualiza todas as tuplas e verifica se houve mudancas
    for (int i = 0; i < tamanho; i++) {
        if (atualizarTupla(w, ranking[i], funcMetrica)) {
            alterado = true;
        }
    }

    //Ordena se houve mudancas
    if (alterado) {
        quickSort(ranking, tamanho);

        //Atualiza a pontuacao
        for (int i = 0; i < tamanho; i++) {
            (ranking[i].getAcao()->*setPontuacao)(tamanho - i);
        }
    }
}

void ConjuntoAcoes::ordenarRet(int w) {
    ordenarEPontuarMetrica(w, rankingRet, &Acao::ret, &Acao::setPontuacaoRet);
}

void ConjuntoAcoes::ordenarAvgret(int w) {
    ordenarEPontuarMetrica(w, rankingAvgret, &Acao::avgret, &Acao::setPontuacaoAvgret);
}

void ConjuntoAcoes::ordenarStab(int w) {
    ordenarEPontuarMetrica(w, rankingStab, &Acao::stab, &Acao::setPontuacaoStab);
}

void ConjuntoAcoes::ordenarCons(int w) {
    ordenarEPontuarMetrica(w, rankingCons, &Acao::cons, &Acao::setPontuacaoCons);
}