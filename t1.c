#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estrutura para a aresta (enlace)
typedef struct Node {
    int dest;
    int peso;
    struct Node* next;
} Node;

// Estrutura para o Grafo
typedef struct Graph {
    int V; // Número de vértices (sensores)
    int E; // Número de arestas (enlaces)
    Node** adjList; // Vetor de ponteiros para o início de cada lista
} Graph;

// Função para criar um novo nó da lista de adjacência
Node* createNode(int dest, int peso) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->peso = peso;
    newNode->next = NULL;
    return newNode;
}

// Inicializa o grafo
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->E = 0;
    graph->adjList = (Node**)malloc(V * sizeof(Node*));
    for (int i = 0; i < V; i++) {
        graph->adjList[i] = NULL;
    }
    return graph;
}


// Adiciona aresta não direcionada
void addEdge(Graph* graph, int src, int dest, int peso) {
    // Aresta src -> dest
    Node* newNode = createNode(dest, peso);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // Aresta dest -> src
    newNode = createNode(src, peso);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
    
    graph->E++;
}

// Funcionalidade 2: Imprimir topologia
void printTopology(Graph* graph) {
    for (int i = 0; i < graph->V; i++) {
        Node* temp = graph->adjList[i];
        printf("Sensor %d", i);
        while (temp) {
            printf(" -> (%d,%d)", temp->dest, temp->peso);
            temp = temp->next;
        }
        printf("\n");
    }
}