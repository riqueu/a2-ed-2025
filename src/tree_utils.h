#ifndef TREEUTILS_H
#define TREEUTILS_H

#include "data.h"
#include <chrono>
#include <string>
#include <vector>

struct Node {
  std::string word;
  std::vector<int> documentIds;
  Node *parent;
  Node *left;
  Node *right;
  int height; // usado na AVL
  int isRed;  // usado na RBT
};

struct BinaryTree {
  Node *root;
  Node *NIL; // usado na RBT (Opcional)
};

struct InsertResult {
  int numComparisons;
  double executionTime;
  //<Possíveis outras variáveis>
};

struct SearchResult {
  int found;
  std::vector<int> documentIds;
  double executionTime;
  int numComparisons;
  //<Possíveis outras variáveis>
};

/**
 * @brief Imprime recursivamente o índice invertido a partir de um nó.
 *
 * Esta função percorre a árvore em ordem (in-order), imprimindo cada palavra e
 * os IDs dos documentos em que essa palavra aparece.
 *
 * @param node Ponteiro para o nó atual da árvore.
 * @param NIL Ponteiro de parada para RBT, default = nullptr
 */
void printIndexRec(Node *node, Node *NIL);

/**
 * @brief Imprime todo o índice invertido da árvore fornecida.
 *
 * Esta função chama printIndexRec a partir da raiz da árvore, imprimindo todas
 * as palavras e seus respectivos documentos.
 *
 * @param tree Ponteiro para árvore.
 */
void printIndex(BinaryTree *tree);

/**
 * @brief Imprime recursivamente a estrutura da árvore.
 *
 * Esta função exibe visualmente a estrutura da árvore.
 *
 * @param node Ponteiro para o nó atual da árvore.
 * @param prefix Espaço acumulado para identação do nó na árvore.
 * @param linePrefix Símbolo usado antes do nó, fornecendo a informação se é um nó a esquerda (---) ou a direita (+--).
 * @param NIL Ponteiro de parada para RBT, default = nullptr

 */
void printTreeRec(Node *node, Node *NIL, std::string prefix, std::string linePrefix);

/**    
 * @brief Imprime a estrutura visual da árvore fornecida.
 *
 * Esta função chama printTreeRec a partir da raiz da árvore, imprimindo a
 * estrutura completa da árvore.
 *
 * @param tree Ponteiro para árvore que será impressa.
 */
void printTree(BinaryTree *tree);

namespace stats {
struct TreeStats {
  int n_docs; // Número de documentos inseridos na árvore

  int numComparisonsInsertionMean; // Número médio de comparações realizadas
                                   // durante as inserções

  int numComparisonsInsertion; // Número total de comparações realizadas durante
                               // as inserções

  double executionTimeInsertionMean; // Tempo médio de execução das inserções em
                                     // milissegundos

  double executionTimeInsertion; // Tempo total de execução das inserções em
                                 // milissegundos

  int numComparisonsSearchMean; // Número médio de comparações realizadas
                                // durante as buscas

  int numComparisonsSearchMax; // Número máximo de comparações realizadas
                               // durante as buscas
                                  // milissegundos
  int treeHeight; // Altura da árvore após as inserções
  
  
  int minBranch; // Comprimento do menor galho
  
  
  int numNodes; // Número total de nós na árvore
  
  
  double executionTimeSearchMax; // Tempo máximo de execução das buscas em
                                 // milissegundos

  double executionTimeSearchMean; // teste
  
  
  size_t size; // tamanho em Bytes da árvore
};

/**
 * @brief Obtém a altura da árvore binária de busca.
 *
 * Calcula a altura da árvore a partir de um nó dado, considerando que a altura
 *
 * @param node Nó raiz da árvore ou subárvore a partir do qual a altura será calculada.
 * @param NIL Ponteiro de parada para RBT, default = nullptr
 * @return Altura da árvore a partir do nó raiz.
 */
int get_tree_height(Node *node, Node *NIL);

/**
 * @brief Encontra o comprimento do menor galho
 *
 * Testa todos os caminhos da raiz ate as folhas e retorna o caminho do menor no
 * min_branch
 *
 * @param node Nó raiz da árvore ou subárvore a partir do qual o menor galho
 * será calculado.
 * @param currentLen Comprimento do caminho na recursão atual (INICIALIZE COM 0)
 * @param minBranch Comprimento do menor galho que será retornado (INICIALIZE
 * COM A ALTURA DA ARVORE + 1)
 * @param NIL Ponteiro de parada para RBT, default = nullptr
 */
void get_min_branch(Node *node, int currentLen, int *minBranch, Node *NIL);

/**
 * @brief Coleta todas as palavras de uma árvore binária de busca.
 *
 * Esta função percorre a árvore em ordem (in-order) e coleta todas as palavras
 * presentes nos nós, armazenando elas em um vetor.
 *
 * @param node Ponteiro para o nó atual da árvore.
 * @param words Vetor onde as palavras coletadas serão armazenadas.
 * @param NIL Ponteiro de parada para RBT, default = nullptr
 * @return Número total de palavras coletadas.
 */
void collect_words(Node *node, std::vector<std::string> &words, Node *NIL);

/**
 * @brief Calcula o tamanho de memória ocupada pela árvore:
 *
 * Esta função percorre a árvore somando a memória alocada dinamicamente
 *
 * @param node Ponteiro para o nó atual da árvore.
 * @param NIL Ponteiro de parada para RBT, default = nullptr
 * @return Tamanho da árvore em bytes
 */
size_t get_tree_size(Node* node, Node* NIL);

/**
 * @brief Obtém estatísticas de uma árvore binária de busca.
 *
 * Esta função cria uma árvore do tipo especificado (BST, AVL ou RBT), insere
 * palavras de documentos nela, realiza buscas por palavras e coleta
 * estatísticas sobre inserções e buscas.
 *
 * @param tree_type Tipo da árvore ("bst", "avl" ou "rbt").
 * @param n_docs Número de documentos a serem processados.
 * @param n_max_doc Número máximo de documentos a serem processados.
 * @param docs Vetor de ponteiros para os documentos a serem processados.
 * @param search_words Vetor de palavras a serem buscadas na árvore.
 * @return Estrutura TreeStats contendo as estatísticas coletadas.
 */
TreeStats get_tree_stats(const std::string &tree_type, int n_docs,
                         int n_max_doc,
                         const std::vector<DocReading::Doc *> &docs);

/**
 * @brief Verifica se todos os nós da árvore estão balanceados.
 *
 * @param root Raiz da árvore a ser verificada.
 * @param NIL Ponteiro de parada para RBT, default = nullptr
 * @return true se todos os nós estão balanceados, ou seja, se o fator de
 * balanceamento de cada nó está entre -1 e 1.
 * @return false se algum nó não está balanceado.
 */
bool all_balanced(Node *root, Node *NIL);

} // namespace stats

#endif
