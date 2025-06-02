#ifndef BST_H
#define BST_H

#include "tree_utils.h"

namespace BST {
/**
 * @brief Cria uma nova árvore binária de busca vazia.
 *
 * @return Ponteiro para a nova árvore criada.
 */
BinaryTree *create();

/**
 * @brief Cria um novo nó com uma palavra e um ID de documento.
 *
 * Inicializa o nó com a palavra, insere o ID no vetor e define ponteiros nulos.
 *
 * @param word Palavra a ser inserida no nó.
 * @param documentId ID do documento onde a palavra aparece.
 * @return Ponteiro para o novo nó criado.
 */
Node *createNode(const std::string &word, int documentId);

/**
 * @brief Insere uma palavra na árvore recursivamente.
 *
 * Adiciona a palavra na árvore;, se já existir, insere o ID no vetor, se não,
 * cria um novo nó.
 *
 * @param root Raiz da árvore onde a palavra será inserida.
 * @param word Palavra a ser inserida.
 * @param documentId ID do documento associado.
 * @return Nova raiz da árvore após a inserção.
 */
Node *insertNode(Node *root, const std::string &word, int documentId);

/**
 * @brief Insere uma palavra na árvore binária de busca.
 *
 * Atualiza a raiz da árvore caso seja a primeira inserção (e returna
 * estatísticas sobre a performance).
 *
 * @param tree Ponteiro para a árvore.
 * @param word Palavra a ser inserida.
 * @param documentId ID do documento associado.
 * @return Estrutura InsertResult contendo tempo de inserção e comparações
 * realizadas.
 */
InsertResult insert(BinaryTree *tree, const std::string &word, int documentId);

/**
 * @brief Busca uma palavra na árvore binária.
 *
 * Retorna um SearchResult contendo status da busca, documentos e comparações.
 *
 * @param tree Ponteiro para a árvore onde será feita a busca.
 * @param word Palavra a ser buscada.
 * @return Estrutura contendo o resultado da busca.
 */
SearchResult search(BinaryTree *tree, const std::string &word);

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
} // namespace BST

#endif
