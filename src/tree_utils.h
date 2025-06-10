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
 */
void printIndexRec(Node *node);

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
 * @param linePrefix Símbolo usado antes do nó, fornecendo a informação se é um
 * nó a esquerda (---) ou a direita (+--).
 */
void printTreeRec(Node *node, std::string prefix, std::string linePrefix);

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

    int numComparisonsInsertion; // Número total de comparações realizadas durante as inserções

    double executionTimeInsertionMean; // Tempo médio de execução das inserções em milissegundos
    double executionTimeInsertion; // Tempo total de execução das inserções em milissegundos

    int numComparisonsSearchMean; // Número médio de comparações realizadas durante as buscas
    int numComparisonsSearchMax; // Número máximo de comparações realizadas durante as buscas

    double executionTimeSearchMean; // Tempo médio de execução das buscas em milissegundos
    double executionTimeSearchMax; // Tempo máximo de execução das buscas em milissegundos

    int treeHeight; // Altura da árvore após as inserções
};

/**
 * @brief Obtém a altura da árvore binária de busca.
 *
 * Calcula a altura da árvore a partir de um nó dado, considerando que a altura
 *
 * @param root Nó raiz da árvore ou subárvore a partir do qual a altura será calculada.
 * @return Altura da árvore a partir do nó raiz.
 */
int get_tree_height(Node *root);

/**
 * @brief Obtém estatísticas de uma árvore binária de busca.
 *
 * Esta função cria uma árvore do tipo especificado (BST ou AVL), insere palavras
 * de documentos nela, realiza buscas por palavras e coleta estatísticas sobre
 * inserções e buscas.
 *
 * @param tree_type Tipo da árvore ("bst" ou "avl").
 * @param n_docs Número de documentos a serem processados.
 * @param n_max_doc Número máximo de documentos a serem processados.
 * @param docs Vetor de ponteiros para os documentos a serem processados.
 * @param search_words Vetor de palavras a serem buscadas na árvore.
 * @return Estrutura TreeStats contendo as estatísticas coletadas.
 */
TreeStats get_tree_stats(const std::string &tree_type, int n_docs, int n_max_doc, const std::vector<DocReading::Doc*>& docs, const std::vector<std::string>& search_words);

}

#endif
