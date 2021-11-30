#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <string>
#include "grafo.hpp"
#include "arvore_precedencia_ra170442.hpp"
using namespace std;

// Leitura de um arquivo txt e retorno do grafo descrito neste arquivo.
Grafo criarGrafo(string file)
{
    ifstream inFile(file.c_str());
    string line;

    // Caso exista algum problema na leitura, um erro será disparado.
    if (!inFile.is_open())
    {
        cout << "Erro: Problema na leitura do grafo." << endl;
        return Grafo(0, 0, 0);
    }

    getline(inFile, line);
    istringstream ss(line);

    // Identificação da quantidade de vértices e arestas contidos na primeira linha do arquivo.
    int n, m, W;
    ss >> n >> m >> W;

    // Criação do objeto tipo Grafo.
    Grafo grafo(n, m, W);

    while (getline(inFile, line))
    {
        istringstream ss(line);
        int v1, v2, cust;
        ss >> v1 >> v2 >> cust;
        // Criação das arestas contidas nas demais linhas do arquivo.
        grafo.adicionarAresta(v1, v2, cust);
    }

    return grafo;
}

int main()
{
    string file = "teste/teste_6_nos.txt";

    Grafo grafo = criarGrafo(file);

    //Inicializem as variáveis
    int pred[grafo.V]; // Lista contendo os vértices antes de v na árvore de precedência;
    int dist[grafo.V]; // Lista contendo a distância de s para v;
    string mensagem;   // String que retorna algum erro no momento da criação da trilha.
    int RA = -1;       // RA do aluno que deve ser preenchido na função que irá criar.

    // PARA EXECUTAR O CÓDIGO: g++ -std=c++11 arvore_precedencia_principal.cpp grafo.cpp arvore_precedencia_ra170442.cpp && ./executor.exe

    bool tem_arvore = arvore_precedencia(grafo.V, grafo.M, grafo.W, grafo, &mensagem, &RA, dist, pred);

    if (RA == -1)
        cout << "Erro: RA informado eh invalido." << endl;
    else if (!tem_arvore)
        cout << mensagem << endl;
    else
        for (int i = 0; i < grafo.V; i++)
            printf("Vértice: %d -> distância: %d\n", i, dist[i]);

    return 0;
}
