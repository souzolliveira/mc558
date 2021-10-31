#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>
#include "grafo.hpp"
#include "trilha_euleriana_ra170442.hpp"

using namespace std;

// Verifica se a trilha que o algoritmo encontrou é uma trilha euleriana.
bool verificarTrilha(int n, int m, int origem[], int destino[], Grafo g1)
{

    if (g1.M != m) // Quantidade de arestas deve ser a mesma
        return false;
    else
    {
        for (int i = 0; i < m; i++)
        {
            // Para cada posição i nos vetores origem e destino, verifica se existe
            // a aresta (origem[i], destino[i]) em G.
            int o_i = origem[i];
            int d_i = destino[i];
            if (!g1.existeAresta(o_i, d_i))
                return false;
        }
        if (destino[m - 1] != origem[0])
            return false;
    }
    return true;
}

// Leitura de um arquivo txt e retorno do grafo descrito neste arquivo.
Grafo criarGrafo(string file)
{
    ifstream inFile(file.c_str());
    string line;

    // Caso exista algum problema na leitura, um erro será disparado.
    if (!inFile.is_open())
    {
        cout << "Erro: Problema na leitura do grafo." << endl;
        return Grafo(0, 0);
    }

    getline(inFile, line);
    istringstream ss(line);

    // Identificação da quantidade de vértices e arestas contidos na primeira linha do arquivo.
    int n, m;
    ss >> n >> m;

    // Criação do objeto tipo Grafo.
    Grafo grafo(n, m);

    while (getline(inFile, line))
    {
        istringstream ss(line);
        int v1, v2;
        ss >> v1 >> v2;
        // Criação das arestas contidas nas demais linhas do arquivo.
        grafo.adicionarAresta(v1, v2);
    }

    return grafo;
}

int main()
{
    string file = "file.txt";

    Grafo grafo = criarGrafo(file);

    // Inicializem as variáveis
    int origem[grafo.M];     // Lista contendo os vértices de origem de cada aresta na trilha.
    int destino[grafo.M];    // Lista contendo os vértices de destino de cada aresta na trilha.
    int trilha[grafo.M + 1]; // Lista contendo a ordem dos vértices na trilha.
    string mensagem;         // String que retorna algum erro no momento da criação da trilha.
    int RA = -1;             // RA do aluno que deve ser preenchido na função que irá criar.

    if (RA == -1)
        cout << "Erro: RA informado eh invalido." << endl;

    // Para compilar esse projeto, utilizar: g++ -std=c++11 trilha_euleriana_principal.cpp grafo.cpp trilha_euleriana_ra170442.cpp
    if (!trilha_euleriana(grafo.V, grafo.M, grafo, origem, destino, trilha, mensagem, &RA))
        cout << mensagem << endl;

    else if (verificarTrilha(grafo.V, grafo.M, origem, destino, grafo))
    {
        printf("Trilha: ");
        for (int i = 0; i < grafo.M + 1; i++)
        {
            printf("%d ", trilha[i]);
            if (i < grafo.M)
                printf("-> ");
        }
    }
    return 0;
}