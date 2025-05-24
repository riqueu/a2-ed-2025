#ifndef TREEUTILS_H
#define TREEUTILS_H

#include <string>
#include <vector>

struct Node {
    std::string word;
    std::vector<int> documentIds;
    Node* parent;
    Node* left;
    Node* right;
    int height;    // usado na AVL
    int isRed;     // usado na RBT
};

struct BinaryTree {
    Node* root;
    Node* NIL;  // usado na RBT (Opcional)
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
 * Esta função percorre a árvore em ordem (in-order), imprimindo cada palavra e os IDs dos documentos em que essa palavra aparece.
 * 
 * @param node Ponteiro para o nó atual da árvore.
 */
void printIndexRec(Node* node);

/**
 * @brief Imprime todos o índice invertido da árvore fornecida.
 * 
 * Esta função chama printIndexRec a partir da raiz da árvore, imprimindo todas as palavras e seus respectivos documentos.
 * 
 * @param tree Ponteiro para árvore.
 */
void printIndex(BinaryTree* tree);

/**
 * @brief Imprime recursivamente a estrutura da árvore.
 * 
 * Esta função exibe visualmente a estrutura da árvore.
 * 
 * @param node Ponteiro para o nó atual da árvore.
 * @param prefix Espaço acumulado para identação do nó na árvore.
 * @param linePrefix Símbolo usado antes do nó, fornecendo a informação se é um nó a esquerda (---) ou a direita (+--).
 */
void printTreeRec(Node* node, std::string prefix, std::string linePrefix);

/**
 * @brief Imprime a estrutura visual da árvore fornecida.
 * 
 * Esta função chama printTreeRec a partir da raiz da árvore, imprimindo a estrutura completa da árvore.
 * 
 * @param tree Ponteiro para árvore que será impressa.
 */
void printTree(BinaryTree* tree);

#endif