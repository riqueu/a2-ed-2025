#ifndef RBT_H
#define RBT_H

#include "tree_utils.h"

namespace RBT {

/**
 * @brief Cria uma nova árvore binária rpt vazia.
 *
 * @return Ponteiro para a nova árvore criada.
 */
BinaryTree *create();

/**
 * @brief Cria um novo nó com uma palavra e um ID de documento.
 *
 * Inicializa o nó com a palavra, insere o ID no vetor e define ponteiros nulos. Inicializa a cor do node como vermelho.
 *
 * @param word Palavra a ser inserida no nó.
 * @param documentId ID do documento onde a palavra aparece.
 * @return Ponteiro para o novo nó criado.
 */
Node *createNode(const std::string &word, int documentId);

/**
 * @brief Obtém a altura de um nó.
 *
 * Retorna -1 se o nó for nulo, caso contrário, retorna a altura do nó.
 *
 * @param node Ponteiro para o nó cuja altura será obtida.
 * @return Altura do nó ou -1 se o nó for nulo.
 */
int getHeight(Node *node);

/**
 * @brief Realiza uma rotação à direita em um nó.
 *
 * Função auxiliar usada para balancear a árvore quando ocorre um
 * desbalanceamento à esquerda.
 *
 * @param node Ponteiro para o nó que será rotacionado.
 * @return Novo nó que se torna a raiz da subárvore após a rotação.
 */
Node *rotateRight(Node *node);

/**
 * @brief Realiza uma rotação à esquerda em um nó.
 *
 * Função auxiliar usada para balancear a árvore quando ocorre um
 * desbalanceamento à direita.
 *
 * @param node Ponteiro para o nó que será rotacionado.
 * @return Novo nó que se torna a raiz da subárvore após a rotação.
 */
Node *rotateLeft(Node *node);

/**
 * @brief Libera recursivamente a memória de todos os nós da subárvore.
 *
 * Esta função percorre a árvore em pós-ordem e deleta todos os nós alocados
 * dinamicamente.
 *
 * @param root Ponteiro para a raiz da árvore a ter seus nós deletados.
 */
void deleteNodes(Node *root);

/**
 * @brief Libera a memória ocupada por toda a árvore.
 *
 * Percorre a árvore e deleta todos os nós dinamicamente alocados.
 *
 * @param tree Ponteiro para a árvore a ser deletada.
 */
void destroy(BinaryTree *tree);

}

#endif