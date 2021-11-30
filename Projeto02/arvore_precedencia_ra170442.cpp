#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <string>
#include "grafo.hpp"
#include "arvore_precedencia_ra170442.hpp"
#define INF 999999
using namespace std;

int menor_dist(Grafo grafo, int dist[], bool visitados[]) // Pega vértice que tem menor distância entre os vértices já visitados
{
    int menor = INF;
    int menor_index;
    for (int v = 0; v < grafo.V; v++)
        if (visitados[v] == false && dist[v] <= menor)
        {
            menor = dist[v]; // Pega distância para comparar com demais vértices
            menor_index = v; // Pega o índice do vértice
        }
    return menor_index;
}

int pega_peso(int u, int v, Grafo grafo) // Pega o peso da aresta
{
    int peso = INF;
    for (const auto &i : grafo.adj[u])
        if (i.first == v) // Verifica se o vértice adjacente é igual ao passado como parâmetro
            peso = i.second; // Caso positivo, pega o peso
    return peso;
}

void dijkstra(int v, Grafo grafo, int dist[]) // Dijkstra comumzão mesmo
{
    bool visitados[v]; // Cria array com o vértices para ver se já foi visitado
    for (int i = 0; i < v; i++)
    {
        dist[i] = INF; // Preenche todas distâncias inicialmente como infinitas
        visitados[i] = false; // Preenche todos vértices inicialmente como não visitados
    }
    dist[0] = 0; // Coloca distância 0 para o primeiro vértice
    for (int i = 0; i < v - 1; i++)
    {
        int u = menor_dist(grafo, dist, visitados); // Procura menor distância entre os vértices adjacentes dos vértices visitados
        visitados[i] = true; // Marca o vértice de menor distância como visitado
        for (int j = 0; j < v; j++) // Faz um relax nas distâncias entre os vértices adjacentes do vértice atualmente visitado
        {
            int peso = pega_peso(u, j, grafo); // Pega peso para verificar se vai haver relax
            if (!visitados[j] && peso != INF && dist[u] != INF && dist[u] + peso < dist[j]) // Verificações para relax
                dist[j] = dist[u] + peso; // Relax
        }
    }
}

bool verifica_pesos(int v, int w, Grafo grafo)
{
    for (int i = 0; i < v; i++)
        for (const auto &j : grafo.adj[i])
            if (j.second < 0 || j.second > w) // Verifica os pesos, se for menor que 0 ou maior que o limite fornecido, retorna false
                return false;
    return true;
}

bool arvore_precedencia(int v, int m, int w, Grafo grafo, string *mensagem, int *RA, int dist[], int pred[])
{
    *RA = 170442;
    if (!verifica_pesos(v, w, grafo)) // Verifica se todas arestas têm peso dentro dos limites fornecidos
    {
        *mensagem = "Erro: Existe peso fora do intervalo.";
        return false;
    }

    dijkstra(v, grafo, dist);

    return true;
}
