# Simulador de Redes de Sensores Sem Fio (RSSF)

Este projeto foi desenvolvido como parte do **Trabalho 1 da disciplina de Algoritmos e Estruturas de Dados II** no **CEFET/RJ - Campus Petrópolis**. O objetivo é implementar um sistema capaz de modelar, analisar e simular a topologia de uma rede de sensores utilizando a teoria dos grafos.

## 📌 Contexto do Problema

A rede é modelada como um **grafo ponderado e não direcionado**, onde:
*   **Vértices**: Representam os sensores e a estação base (sink node).
*   **Arestas**: Representam os enlaces de comunicação entre os dispositivos.
*   **Pesos**: Representam o custo de transmissão, como distância ou consumo de energia.
*   **Estação Base**: Definida como o último nó da rede (índice $V-1$)

## 🚀 Funcionalidades Implementadas

O sistema executa as seguintes análises de forma automatizada[cite: 1]:

1.  **Carregamento de Topologia**: Leitura dinâmica via `stdin`
2.  **Impressão da Topologia**: Exibição detalhada da lista de adjacências
3.  **Verificação de Alcance**: Encontra o caminho entre o primeiro sensor e a estação base, calculando o número de saltos via **Busca em Largura (BFS)**
4.  **Cálculo de Grau Médio**: Indica o número médio de vizinhos por sensor
5.  **Análise de Conectividade**: Determina a robustez da rede (quantos sensores ou enlaces precisam falhar para desconectá-la)
6.  **Coeficiente de Agrupamento**: Mede o nível de conexão entre os vizinhos de um nó específico
7.  **Identificação e Remoção de Nós Críticos**: Detecta sensores essenciais para a conectividade e simula o impacto de sua falha no grau médio da rede

## 🛠️ Detalhes Técnicos

*   **Linguagem**: C
*   **Estrutura de Dados**: Lista de Adjacências para otimização de memória e tempo de execução
*   **Algoritmo de Detecção Crítica**: Baseado em Pontos de Articulação (Algoritmo de Tarjan) com complexidade $O(V + E)$
*   **Tratamento de Precisão**: Implementação de truncação decimal para alinhar os resultados de saída com o gabarito oficial do curso

## 📂 Como Usar

### Pré-requisitos
Certifique-se de ter o compilador `gcc` instalado em seu ambiente (Linux/Terminal).


### Arquivo de Entrada (`teste.txt`)
O arquivo deve seguir o padrão de exemplo fornecido:
```text
8 11
0 1 2
0 2 3
...
```

### Compilação

```bash
gcc simulador.c -o simulador -Wall
```

### Execução

```
./simulador < teste.txt
```

## 🧠 Embasamento Matemático e Algorítmico

Para garantir a precisão das análises de rede, foram aplicados os seguintes conceitos da Teoria dos Grafos:

### 1. Teorema do Aperto de Mãos (Handshaking Lemma)

Utilizado para validar o cálculo do Grau Médio. Em um grafo não direcionado, a soma dos graus de todos os vértices é igual ao dobro do número de arestas:
  $$\sum_{v \in V} \text{grau}(v) = 2|E|$$
  Dessa forma, o Grau Médio ($D_{avg}$) é definido como:
  $$D_{avg} = \frac{2|E|}{|V|}$$

### 2. Coeficiente de Agrupamento Local ($CC$)
Mede a conectividade entre os vizinhos de um nó $i$. Se o nó possui $k_i$ vizinhos, o número máximo de conexões entre eles é $\frac{k_i(k_i - 1)}{2}$. A fórmula aplicada é:
  $$CC_i = \frac{2 \cdot |\text{enlaces entre vizinhos}|}{k_i(k_i - 1)}$$

### 3. Conectividade e Teorema de Menger
A robustez da rede é analisada através da conectividade de vértices ($\kappa(G)$) e arestas ($\lambda(G)$). No projeto, adotamos a relação fundamental:
  $$\kappa(G) \le \lambda(G) \le \delta_{min}(G)$$
Onde $\delta_{min}(G)$ representa o grau mínimo encontrado na topologia. 

### 4. Identificação de Pontos de Articulação
Para detectar Sensores Críticos, o sistema utiliza uma busca em profundidade (DFS) que rastreia o tempo de descoberta e o valor de low-link de cada nó. Um nó $u$ é crítico se:  
* $u$ for a raiz da DFS e tiver dois ou mais filhos.  
* $u$ não for raiz e possuir um filho $v$ tal que nenhum nó na subárvore de $v$ tenha uma aresta de retorno para um ancestral de $u$.