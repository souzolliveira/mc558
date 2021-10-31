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
// Função para verificar o grau dos vértices
bool mesmo_grau_entrada_saida(int n, Grafo g)
{
    int grau[n];                            // Inicializa um vetor com o tamanho dos vértices
    for (int i = 0; i < n; i++)             // Percorre todas posições para iniciar com 0
        grau[i] = 0;                        //
    for (int i = 0; i < n; i++)             // Percorre todos os vértices
    {                                       //
        grau[i] -= g.vizinhos[i].size();    // Subtrai de cada vértice a quantidade de arestas que saem dele
        for (auto const &v : g.vizinhos[i]) // Percorre as arestas adjacentes de cada vértice
            grau[v] += 1;                   // Soma à cada vértice adjacente uma aresta que chega nele
    }                                       //
    for (int i = 0; i < n; i++)             // Percorre todos vértices para ver se o grau resultante é 0 -> número de arestas que entram e saem seja igual
        if (grau[i] != 0)                   //
            return false;                   // Se alguma vértice tiver grau diferente de 0, retorna false
    return true;                            // Caso contrário retorna true
}

// Função recursiva de busca em profundidade
void DFS(int index, bool visitados[], Grafo g)
{
    visitados[index] = true;                // Marca o primeiro vértice como visitado
    for (auto const &v : g.vizinhos[index]) // Passa por todos os vértices adjacentes de cada vértice
        if (!visitados[v])                  // Se ainda não tiver sido visitado, faz a DFS nele
            DFS(v, visitados, g);
}

// Função que constrói um grafo transposto a partir de um grafo dado
Grafo transposto(int n, int m, Grafo g)
{
    Grafo gt(n, m);
    for (int i = 0; i < n; i++)
        for (auto const &v : g.vizinhos[i])
            gt.adicionarAresta(v, i);
    return gt;
}

// Função para inicializar todos vértices como não visitados
void inicializa_false(int n, bool visitados[])
{
    for (int i = 0; i < n; i++) // Percorre todos vértices para marcar como false
        visitados[i] = false;
}

// FUnção para verificar se todos vértices foram visitados
bool todos_visitados(int n, bool visitados[])
{
    for (int i = 0; i < n; i++)    // Percorre os vértices para verificar se algum está false
        if (visitados[i] == false) //
            return false;          // Retorna false caso algum vértice não tenha sido visitado
    return true;                   // Caso contrário retorna true
}

// Função para verificar se o grafo é fortemente conexo fazendo:
// - uma DFS no Grafo original, e
// - uma DFS no Grafo transposto.
// Caso alguma DFS retorne um vértice não visitado, o Grafo não é fortemente conexo
bool grafo_fortemente_conexo(int n, int m, Grafo g)
{
    bool visitados[n];                  // Inicializa um vetor de vértices visitados de tamanho n = número de vértices
    inicializa_false(n, visitados);     // Inicializa todos vértices como não visitados
    DFS(0, visitados, g);               // Faz uma busca em profundidade para ver se passou por todos os vértices
    if (!todos_visitados(n, visitados)) // Se tiver algum vértice não visitado, retorna false
        return false;                   //
    Grafo gt = transposto(n, m, g);     // Cria um grafo transposto
    inicializa_false(n, visitados);     // Inicializa todos vértices como não visitados novamente
    DFS(0, visitados, gt);              // Faz uma busca em profundidade no grafo transposto para ver se passou por todos os vértices
    if (!todos_visitados(n, visitados)) // Se tiver algum vértice não visitado, retorna false
        return false;                   //
    return true;                        // Caso o grafo seja fortemente conexo, retorna true
}

// Função para montar a trilha euleriana
bool monta_trilha(int n, int m, Grafo g, int origem[], int destino[], int trilha[])
{
    Grafo copia_g(n, m);                                                  // Faz uma cópia do grafo original para poder manipular as arestas
    for (int i = 0; i < n; i++)                                           //
        for (auto const &v : g.vizinhos[i])                               //
            copia_g.adicionarAresta(i, v);                                //
    int quantidade_arestas[n];                                            // Inicializa um array com a quantidade de arestas adjacentes para cada vértice
    for (int i = 0; i < n; i++)                                           //
        quantidade_arestas[i] = copia_g.vizinhos[i].size();               //
    stack<int> pilha_vertices;                                            // Inicializa uma pilha para percorrer o grafo
    int vertice_atual = rand() % n;                                       // Inicializa uma variável para receber um vértice aleatório para começar o loop
    pilha_vertices.push(vertice_atual);                                   // Empilha o primeiro vértice
    int i = m;                                                            // Inicializa uma variável para colocar os vértices em trilha, origem e destino
    while (!pilha_vertices.empty())                                       // Enquanto a pilha não for vazia, passa pelas arestas adjacentes
    {                                                                     //
        if (quantidade_arestas[vertice_atual] > 0)                        // Se o vértice atual tiver arestas adjacentes
        {                                                                 //
            pilha_vertices.push(vertice_atual);                           // Adiciona vértice à pilha
            int proximo_vertice = copia_g.vizinhos[vertice_atual].back(); // Inicializa próximo vértice como sendo o vértice da última aresta adjacente do vértice atual
            quantidade_arestas[vertice_atual]--;                          // Decresce uma aresta adjacente na quantidade de arestas adjacentes do vértice atual
            copia_g.vizinhos[vertice_atual].pop_back();                   // Remove a última aresta adjacente do vértice atual
            vertice_atual = proximo_vertice;                              // Próximo vértice atual passa a ser o vértice atual
        }                                                                 //
        else                                                              // Caso o vértice atual não tenha arestas adjacentes
        {                                                                 //
            trilha[i] = vertice_atual;                                    // Adiciona o vértice atual à trilha
            if (i > 0)                                                    // Destino não recebe o primeiro vértice
                destino[i - 1] = vertice_atual;                           // Adiciona vértice atual ao destino
            if (i <= m)                                                   // Origem não recebe o último vértice
                origem[i] = vertice_atual;                                // Adiciona vértice atual à origem
            i--;                                                          // Decrementa variável de posição i
            vertice_atual = pilha_vertices.top();                         // Vértice atual passa a ser o próximo da lista de vértices do grafo
            pilha_vertices.pop();                                         // Remove o vértice atual da pilha
        }
    }
    return true;
}

bool trilha_euleriana(int n, int m, Grafo g, int origem[], int destino[], int trilha[], string &mensagem, int *RA)
{
    if (!mesmo_grau_entrada_saida(n, g))                   // Verifica se todos vértices tem os mesmos graus de entrada e saída
    {                                                      //
        mensagem = "Erro: Existe vértice inviável.";       // Retorna mensagem coerente
        return false;                                      //
    }                                                      //
    if (!grafo_fortemente_conexo(n, m, g))                 // Verifica se o grafo é fortemente conexo
    {                                                      //
        mensagem = "Erro: Grafo não é fortemente conexo."; // Retorna mensagem coerente
        return false;                                      //
    }                                                      //
    monta_trilha(n, m, g, origem, destino, trilha);        // Monta a trilha

    return true;
}
