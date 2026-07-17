#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdexcept>
#include <exception>
#include "ConjuntoClientes.h"
#include "ConjuntoAcoes.h"
#include "Ordenacao.h"

using namespace std;

//Valida se o nome informado corresponde a uma metrica
bool isMetricaValida(const string& m) {
    return (m == "RET" || m == "AVGRET" || m == "STAB" || m == "CONS");
}

//Registra a metrica como ativa para uso
void registrarMetrica(bool& variavelMetrica) {
    if (variavelMetrica) {
        throw runtime_error("Metrica duplicada na linha M!");
    }
    variavelMetrica = true;
}

//Valida se a metrica informada da consulta esta ativa e nao esta duplicada, ordena o ranking dela e atribui o peso
void processarMetricaConsulta(int w, ConjuntoAcoes& conjuntoAcoes, const string& metrica, float peso, bool variavelMetrica, float& variavelPeso) {
    if (variavelPeso != 0) {
        throw runtime_error("Metrica duplicada na linha Q!");
    }

    if (!variavelMetrica) {
        throw runtime_error("Metrica " + metrica + " nao esta ativa!");
    }

    //Ordena o vetor desta metrica no conjunto
    if (metrica == "RET")
        conjuntoAcoes.ordenarRet(w);
    else if (metrica == "AVGRET")
        conjuntoAcoes.ordenarAvgret(w);
    else if (metrica == "STAB")
        conjuntoAcoes.ordenarStab(w);
    else if (metrica == "CONS")
        conjuntoAcoes.ordenarCons(w);

    variavelPeso = peso;
}

//Main
int main(int argc, char const *argv[]) {
    try {
        int w, queryIdAtual = 0;
        bool ret = false, avgret = false, stab = false, cons = false;
        ConjuntoClientes cc;
        ConjuntoAcoes ca;

        string linha;
        bool temA = false, temU = false;

        //Definindo precisao para 2 casas decimais
        cout << fixed << setprecision(2);

        //Valida arquivo e obetem a primeira linha
        if (!getline(cin, linha)) {
            throw runtime_error("Arquivo vazio!");
        }

        //Valida a linha M (Configuracoes)
        {
            istringstream iss(linha);
            char tipo;

            if (!(iss >> tipo) || tipo != 'M') {
                throw runtime_error("Primeira linha deve ser M!");
            }

            if (!(iss >> w)) {
                throw runtime_error("Linha M invalida, valor w nao encontrado!");
            }

            if (w < 2) {
                throw runtime_error("Linha M com valor w menor que 2!");
            }

            string metrica;
            while (iss >> metrica) {
                if (!isMetricaValida(metrica)) {
                    throw runtime_error("Metrica invalida na linha M!");
                }

                if (metrica == "RET") {
                    registrarMetrica(ret);
                } else if (metrica == "AVGRET") {
                    registrarMetrica(avgret);
                } else if (metrica == "STAB") {
                    registrarMetrica(stab);
                } else if (metrica == "CONS") {
                    registrarMetrica(cons);
                }
            }
        }

        //Le as linhas A (Acoes)
        while (getline(cin, linha)) {
            if (linha.empty()) continue;

            istringstream iss(linha);
            char tipo;
            iss >> tipo;

            if (tipo != 'A') break;

            try {
                int id;
                if (!(iss >> id)) {
                    throw runtime_error("Linha A com id invalido!");
                }

                if (id < 0) {
                    throw runtime_error("Linha A com id menor que zero!");
                }

                string extra;
                if (iss >> extra) {
                    throw runtime_error("Formato invalido na linha A!");
                }

                Acao* acao = new Acao(w, id);
                ca.inserir(acao);

                temA = true;
            } catch (const exception& e) {
                cerr << "Erro na linha A: " << e.what() << endl;
            }
        }

        if (!temA) {
            throw runtime_error("Nenhuma linha A encontrada!");
        }

        ca.fecharConjunto();

        //Le as linhas U (Clientes)
        do {
            if (linha.empty()) continue;

            istringstream iss(linha);
            char tipo;
            iss >> tipo;

            if (tipo != 'U') break;

            try {
                int id;
                if (!(iss >> id)) {
                    throw runtime_error("Linha U com id invalido!");
                }

                if (id < 0) {
                    throw runtime_error("Linha U com id menor que zero!");
                }

                string extra;
                if (iss >> extra) {
                    throw runtime_error("Formato invalido na linha U!");
                }

                Cliente* cliente = new Cliente(id);
                cc.inserir(cliente);

                temU = true;
            } catch (const exception& e) {
                cerr << "Erro na linha U: " << e.what() << endl;
            }

        } while (getline(cin, linha));

        if (!temU) {
            throw runtime_error("Nenhuma linha U encontrada!");
        }

        cc.fecharConjunto();

        //Le os comandos
        do {
            if (linha.empty()) continue;

            istringstream iss(linha);
            char tipo;
            iss >> tipo;

            try {
                //Tipo P: Adiciona nova cotacao
                if (tipo == 'P') {
                    int acao;
                    float preco;

                    if (!(iss >> acao >> preco)) {
                        throw runtime_error("Linha P invalida!");
                    }

                    if (preco <= 0) {
                        throw runtime_error("Linha P deve ter preco maior que zero!");
                    }

                    string extra;
                    if (iss >> extra) {
                        throw runtime_error("Formato invalido na linha P!");
                    }

                    ca.buscar(acao)->addCotacao(w, preco);
                }

                //Tipo B: Compra acao para a carteira do cliente
                else if (tipo == 'B') {
                    int cliente, acao;

                    if (!(iss >> cliente >> acao)) {
                        throw runtime_error("Linha B invalida!");
                    }

                    string extra;
                    if (iss >> extra) {
                        throw runtime_error("Formato invalido na linha B!");
                    }

                    cc.buscar(cliente)->getCarteira().comprar(ca.buscar(acao));
                }

                //Tipo V: Vende acao da carteira do cliente
                else if (tipo == 'V') {
                    int cliente, acao;

                    if (!(iss >> cliente >> acao)) {
                        throw runtime_error("Linha V invalida!");
                    }

                    string extra;
                    if (iss >> extra) {
                        throw runtime_error("Formato invalido na linha V!");
                    }

                    cc.buscar(cliente)->getCarteira().vender(acao);
                }

                //Tipo Q: Consulta
                else if (tipo == 'Q') {
                    int id, cliente, n, m;
                    float pesoRet = 0, pesoAvgret = 0, pesoStab = 0, pesoCons = 0;

                    if (!(iss >> id >> cliente >> n >> m)) {
                        throw runtime_error("Linha Q invalida (inteiros)!");
                    }

                    if (id != queryIdAtual) {
                        throw runtime_error("Id invalido para linha Q!");
                    }
                    queryIdAtual++;

                    if (m <= 0) {
                        throw runtime_error("Linha Q com m invalido!");
                    }

                    if (n < 0) {
                        throw runtime_error("Linha Q com n invalido!");
                    }

                    //Processa os pesos de cada metrica para esta consulta
                    for (int i = 0; i < m; i++) {
                        string metrica;
                        float peso;

                        if (!(iss >> metrica >> peso)) {
                            throw runtime_error("Linha Q incompleta!");
                        }

                        if (!isMetricaValida(metrica)) {
                            throw runtime_error("Metrica invalida na linha Q!");
                        }

                        if (peso <= 0) {
                            throw runtime_error("Peso deve ser maior que zero na linha Q!");
                        }

                        //Processa a metrica
                        if (metrica == "RET") {
                            processarMetricaConsulta(w, ca, metrica, peso, ret, pesoRet);
                        } else if (metrica == "AVGRET") {
                            processarMetricaConsulta(w, ca, metrica, peso, avgret, pesoAvgret);
                        } else if (metrica == "STAB") {
                            processarMetricaConsulta(w, ca, metrica, peso, stab, pesoStab);
                        } else if (metrica == "CONS") {
                            processarMetricaConsulta(w, ca, metrica, peso, cons, pesoCons);
                        }
                    }

                    string extra;
                    if (iss >> extra) {
                        throw runtime_error("Formato invalido na linha Q!");
                    }

                    //Obtem ranking da carteira
                    Carteira& carteira = cc.buscar(cliente)->getCarteira();
                    TuplaOrdenacao* vetor = carteira.ordenarCarteira(pesoRet, pesoAvgret, pesoStab, pesoCons);
                    int tamanho = carteira.getTamanho();

                    //Imprime as n melhores acoes
                    for (int i = 0; i < tamanho && i < n; i++) {
                        cout << "R " << id << " M " << i << " " << vetor[i].getAcao()->getId() << " " << vetor[i].getValor() << endl;
                    }

                    //Imprime as n piores acoes
                    for (int i = 0; i < tamanho && i < n; i++) {
                        cout << "R " << id << " P " << i << " " << vetor[tamanho - i - 1].getAcao()->getId() << " " << vetor[tamanho - i - 1].getValor() << endl;
                    }

                    delete[] vetor;
                }

                else {
                    throw runtime_error("Comando desconhecido!");
                }
            } catch (const exception& e) {
                cerr << "Erro no comando: " << e.what() << endl;
            }

        } while (getline(cin, linha));
        
    } catch (const exception& e) {
        cerr << "Erro: " << e.what() << endl;
        return EXIT_FAILURE;
    } catch (...) {
        cerr << "Erro desconhecido!" << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}