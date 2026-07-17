#include "Carteira.h"
#include "Ordenacao.h"

//Node
Carteira::NodeCarteira::NodeCarteira(Acao* a) : dado(a), anterior(nullptr), proximo(nullptr) {}

//Carteira
Carteira::Carteira() : inicio(nullptr), fim(nullptr), tamanho(0) {}

Carteira::~Carteira() {
    limpar();
}

void Carteira::comprar(Acao* acao) {
    if (!acao) {
        throw std::invalid_argument("Acao nula!");
    }

    if (buscarPorId(acao->getId())) {
        throw std::runtime_error("Acao com id duplicado!");
    }

    NodeCarteira* novo = new NodeCarteira(acao);

    if (!inicio) {
        inicio = fim = novo;
    } else {
        fim->proximo = novo;
        novo->anterior = fim;
        fim = novo;
    }

    tamanho++;
}

void Carteira::vender(int id) {
    NodeCarteira* atual = inicio;

    while (atual) {
        if (atual->dado->getId() == id) {
            //Remove da lista
            if (atual->anterior)
                atual->anterior->proximo = atual->proximo;
            else
                inicio = atual->proximo;

            if (atual->proximo)
                atual->proximo->anterior = atual->anterior;
            else
                fim = atual->anterior;

            delete atual;
            tamanho--;
            return;
        }
        atual = atual->proximo;
    }

    throw std::runtime_error("Acao nao encontrada na carteira!");
}

Carteira::NodeCarteira* Carteira::buscarPorId(int id) const {
    NodeCarteira* atual = inicio;

    while (atual) {
        if (atual->dado->getId() == id)
            return atual;
        atual = atual->proximo;
    }

    return nullptr;
}

Acao* Carteira::buscar(int id) const {
    NodeCarteira* no = buscarPorId(id);
    if (!no) {
        throw std::runtime_error("Acao nao encontrada na carteira!");
    }
    return no->dado;
}

Carteira::NodeCarteira* Carteira::obterNode(int indice) const {
    if (indice < 0 || indice >= tamanho) {
        throw std::out_of_range("Indice fora dos limites!");
    }

    NodeCarteira* atual;

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

Acao* Carteira::operator[](int indice) {
    return obterNode(indice)->dado;
}

const Acao* Carteira::operator[](int indice) const {
    return obterNode(indice)->dado;
}

void Carteira::limpar() {
    NodeCarteira* atual = inicio;

    while (atual) {
        NodeCarteira* temp = atual;
        atual = atual->proximo;
        delete temp;
    }

    inicio = fim = nullptr;
    tamanho = 0;
}

int Carteira::getTamanho() const {
    return tamanho;
}

bool Carteira::vazio() const {
    return tamanho == 0;
}

TuplaOrdenacao* Carteira::ordenarCarteira(float pesoRet, float pesoAvgret, float pesoStab, float pesoCons) {
    TuplaOrdenacao* v = new TuplaOrdenacao[tamanho];

    //Constroi as tuplas para ordenacao com base na soma das pontuacoes vezes o peso em cada metrica
    for (int i = 0; i < tamanho; i++) {
        Acao* acao = (*this)[i];
        v[i].setAcao(acao);

        float pontuacao = 0;
        if (pesoRet > 0) {
            pontuacao += acao->getPontuacaoRet() * pesoRet;
        }
        if (pesoAvgret > 0) {
            pontuacao += acao->getPontuacaoAvgret() * pesoAvgret;
        }
        if (pesoStab > 0) {
            pontuacao += acao->getPontuacaoStab() * pesoStab;
        }
        if (pesoCons > 0) {
            pontuacao += acao->getPontuacaoCons() * pesoCons;
        }

        v[i].setValor(pontuacao);
    }

    //Ordena o vetor
    quickSort(v, tamanho);

    return v;
}