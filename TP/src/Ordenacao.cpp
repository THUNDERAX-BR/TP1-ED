#include "Ordenacao.h"

//Compara duas tuplas, verificando o valor e o id da acao em caso de empate, retorna true se a deve vir antes de b
bool comparar(const TuplaOrdenacao& a, const TuplaOrdenacao& b) {
    float valorA = a.getValor();
    float valorB = b.getValor();

    //Compara os valores
    if (valorA > valorB)
        return true;
    if (valorA < valorB)
        return false;

    //Desempate pelo id da acao
    int idA = a.getAcao()->getId();
    int idB = b.getAcao()->getId();

    return idA < idB;
}

//Troca dois elementos do vetor
void trocar(TuplaOrdenacao& a, TuplaOrdenacao& b) {
    TuplaOrdenacao temp = a;
    a = b;
    b = temp;
}

//Particao do QuickSort
void particao(TuplaOrdenacao* vetor, int inicio, int fim, int* i, int* j) {
    *i = inicio; *j = fim;
    TuplaOrdenacao pivo = vetor[(*i + *j) / 2];

    do {
        while (comparar(vetor[*i], pivo)) (*i)++;
        while (comparar(pivo, vetor[*j])) (*j)--;

        if (*i <= *j) {
            trocar(vetor[*i], vetor[*j]);
            (*i)++; (*j)--;
        }
    } while (*i <= *j);
}

//Recursao do QuickSort
void ordena(TuplaOrdenacao* vetor, int inicio, int fim) {
    int i, j;

    particao(vetor, inicio, fim, &i, &j);

    if (inicio < j) ordena(vetor, inicio, j);
    if (i < fim) ordena(vetor, i, fim);
}

void quickSort(TuplaOrdenacao* vetor, int tamanho) {
    ordena(vetor, 0, tamanho - 1);
}