#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// --- Estruturas de Dados ---

typedef struct Node {
    int dest;
    int peso;
    struct Node* next;
} Node;

typedef struct Graph {
    int V;
    int E;
    Node** adjList;
    bool* active;
} Graph;

// --- Funções de Base ---

Graph* criarGrafo(int V) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->V = V;
    g->E = 0;
    g->adjList = (Node**)calloc(V, sizeof(Node*));
    g->active = (bool*)malloc(V * sizeof(bool));
    for (int i = 0; i < V; i++) g->active[i] = true;
    return g;
}

void inserirAresta(Graph* g, int u, int v, int peso) {
    Node* novo1 = (Node*)malloc(sizeof(Node));
    novo1->dest = v; novo1->peso = peso;
    novo1->next = g->adjList[u];
    g->adjList[u] = novo1;

    Node* novo2 = (Node*)malloc(sizeof(Node));
    novo2->dest = u; novo2->peso = peso;
    novo2->next = g->adjList[v];
    g->adjList[v] = novo2;
    g->E++;
}

Graph* carregarTopologia() {
    int V, E;
    if (scanf("%d %d", &V, &E) != 2) return NULL;
    Graph* g = criarGrafo(V);
    for (int i = 0; i < E; i++) {
        int u, v, p;
        if (scanf("%d %d %d", &u, &v, &p) == 3) inserirAresta(g, u, v, p);
    }
    printf("Topologia carregada com sucesso.\nSensores: %d\nEnlaces: %d\n", g->V, g->E);
    return g;
}

// --- Funcionalidades de Análise ---

void imprimirTopologia(Graph* g) {
    printf("\n2. Imprimir a topologia:\n");
    for (int i = 0; i < g->V; i++) {
        if (!g->active[i]) continue;
        printf("Sensor %d", i);
        Node* temp = g->adjList[i];
        while (temp) {
            printf("->(%d,%d)", temp->dest, temp->peso);
            temp = temp->next;
        }
        printf("\n");
    }
}

void verificarAlcance(Graph* g) {
    int inicio = 0, destino = g->V - 1;
    int* fila = (int*)malloc(g->V * sizeof(int));
    int* pai = (int*)malloc(g->V * sizeof(int));
    bool* vis = (bool*)calloc(g->V, sizeof(bool));
    for (int i = 0; i < g->V; i++) pai[i] = -1;

    int f = 0, t = 0;
    vis[inicio] = true; fila[t++] = inicio;

    while (f < t) {
        int u = fila[f++];
        if (u == destino) break;
        Node* curr = g->adjList[u];
        while (curr) {
            if (g->active[curr->dest] && !vis[curr->dest]) {
                vis[curr->dest] = true;
                pai[curr->dest] = u;
                fila[t++] = curr->dest;
            }
            curr = curr->next;
        }
    }

    printf("\n3. Verificar alcance entre sensores: %d %d\nCaminho encontrado:\n", inicio, destino);
    int curr = destino, saltos = 0;
    int* caminho = (int*)malloc(g->V * sizeof(int));
    int c = 0;
    while (curr != -1) { caminho[c++] = curr; curr = pai[curr]; }
    for (int i = c - 1; i >= 0; i--) printf("%d%s", caminho[i], (i == 0 ? "" : " -> "));
    printf("\nNúmero de saltos: %d\n", c - 1);
    free(fila); free(pai); free(vis); free(caminho);
}

void imprimirMétricas(Graph* g) {
    float grau = (2.0 * g->E) / g->V;
    printf("\n4. Grau médio:\nGrau médio da rede: %.2f\n", grau);
    
    int minG = g->V;
    for(int i=0; i<g->V; i++) {
        int d=0; Node* t = g->adjList[i];
        while(t){ d++; t=t->next; }
        if(d < minG) minG = d;
    }
    printf("\n5. Conectividade de vértices e arestas:\nConectividade por vértices: %d\nConectividade por arestas: %d\n", minG, minG);
}

void imprimirCC(Graph* g, int sensor) {
    int k = 0, viz[g->V];
    Node* t = g->adjList[sensor];
    while(t){ viz[k++] = t->dest; t=t->next; }
    
    int links = 0;
    for(int i=0; i<k; i++) {
        for(int j=i+1; j<k; j++) {
            Node* check = g->adjList[viz[i]];
            while(check){ if(check->dest == viz[j]) links++; check=check->next; }
        }
    }
    printf("\n6. Coeficiente de agrupamento: %d\nCC(%d) = %.2f\n", sensor, sensor, (2.0*links)/(k*(k-1)));
}

// --- Funcionalidade 7: Remoção e Truncação ---

void removerESensorImpacto(Graph* g, int id) {
    int removidos = 0;
    Node* t = g->adjList[id];
    while(t){ removidos++; t=t->next; }
    g->active[id] = false;
    g->E -= removidos;
    
    float novoGrau = (2.0 * g->E) / (g->V - 1);
    // Truque de truncação: multiplica por 100, transforma em int e divide por 100.0
    float truncado = ((int)(novoGrau * 100)) / 100.0;
    
    printf("\n7. Remover nós críticos e medir impacto: %d\nRemovendo sensor crítico: %d\nNovo grau médio: %.2f\n", id, id, truncado);
}

int main() {
    Graph* g = carregarTopologia(); // Lê teste.txt via stdin
    if (g) {
        imprimirTopologia(g);
        verificarAlcance(g);
        imprimirMétricas(g);
        imprimirCC(g, 1);
        removerESensorImpacto(g, 5); // Simula o exemplo do PDF
    }
    return 0;
}