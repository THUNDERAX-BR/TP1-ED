#include "ConjuntoClientes.h"

//Node
ConjuntoClientes::NodeConjuntoClientes::NodeConjuntoClientes(Cliente* a) : dado(a), anterior(nullptr), proximo(nullptr) {}

//ConjuntoClientes
ConjuntoClientes::ConjuntoClientes() : inicio(nullptr), fim(nullptr), tamanho(0), fechado(false) {}

ConjuntoClientes::~ConjuntoClientes() {
    limpar();
}

void ConjuntoClientes::inserir(Cliente* cliente) {
    if (fechado) {
        throw std::invalid_argument("Conjunto de clientes fechado!");
    }

    if (!cliente) {
        throw std::invalid_argument("Cliente nulo!");
    }

    if (cliente->getId() != tamanho) {
        throw std::runtime_error("Cliente com id invalido!");
    }

    NodeConjuntoClientes* novo = new NodeConjuntoClientes(cliente);

    if (!inicio) {
        inicio = fim = novo;
    } else {
        fim->proximo = novo;
        novo->anterior = fim;
        fim = novo;
    }

    tamanho++;
}

void ConjuntoClientes::fecharConjunto() {
    if (fechado) {
        throw std::invalid_argument("Conjunto de clientes ja esta fechado!");
    }

    if (tamanho == 0) {
        throw std::invalid_argument("Nao e possivel fechar conjunto de clientes vazio!");
    }

    fechado = true;
}

ConjuntoClientes::NodeConjuntoClientes* ConjuntoClientes::buscarPorId(int id) const {
    NodeConjuntoClientes* atual = inicio;

    while (atual) {
        if (atual->dado->getId() == id)
            return atual;
        atual = atual->proximo;
    }

    return nullptr;
}

Cliente* ConjuntoClientes::buscar(int id) const {
    NodeConjuntoClientes* no = buscarPorId(id);
    if (!no) {
        throw std::runtime_error("Cliente nao encontrado!");
    }
    return no->dado;
}

ConjuntoClientes::NodeConjuntoClientes* ConjuntoClientes::obterNode(int indice) const {
    if (indice < 0 || indice >= tamanho) {
        throw std::out_of_range("Indice fora dos limites!");
    }

    NodeConjuntoClientes* atual;

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

Cliente& ConjuntoClientes::operator[](int indice) {
    return *(obterNode(indice)->dado);
}

const Cliente& ConjuntoClientes::operator[](int indice) const {
    return *(obterNode(indice)->dado);
}

void ConjuntoClientes::limpar() {
    NodeConjuntoClientes* atual = inicio;

    while (atual) {
        NodeConjuntoClientes* temp = atual;
        atual = atual->proximo;

        delete temp->dado;
        delete temp;
    }

    inicio = fim = nullptr;
    tamanho = 0;
}

int ConjuntoClientes::getTamanho() const {
    return tamanho;
}

bool ConjuntoClientes::vazio() const {
    return tamanho == 0;
}