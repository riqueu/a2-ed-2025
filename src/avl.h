#ifndef AVL_H
#define AVL_H

#include "tree_utils.h"

namespace AVL {
/**
 * @brief Cria uma nova árvore binária avl vazia.
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
 * @brief Obtém a altura de um nó.
 *
 * Retorna -1 se o nó for nulo, caso contrário, retorna a altura do nó.
 *
 * @param node Ponteiro para o nó cuja altura será obtida.
 * @return Altura do nó ou -1 se o nó for nulo.
 */
int getHeight(Node *node);

/**
 * @brief Calcula o fator de balanceamento de um nó.
 *
 * O fator de balanceamento é a diferença entre a altura da subárvore esquerda
 * e a altura da subárvore direita.
 *
 * @param node Ponteiro para o nó cujo fator de balanceamento será calculado.
 * @return Fator de balanceamento do nó.
 */
int getBalanceFactor(Node *node);

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
 * @brief Balanceia um nó da árvore AVL.
 *
 * Verifica o fator de balanceamento do nó e realiza rotações para garantir que
 * a árvore permaneça balanceada. Pode realizar rotações simples ou duplas.
 *
 * @param node Ponteiro para o nó que será balanceado.
 * @return Novo nó que se torna a raiz da subárvore após o balanceamento.
 */
Node *balance(Node *node);

/**
 * @brief Insere uma palavra na árvore AVL recursivamente.
 *
 * Adiciona a palavra na árvore; se já existir, insere o ID no vetor, se não,
 * cria um novo nó. A função também garante que a árvore permaneça balanceada.
 *
 * @param root Raiz da árvore onde a palavra será inserida.
 * @param word Palavra a ser inserida.
 * @param documentId ID do documento associado.
 * @return Nova raiz da árvore após a inserção.
 */
Node *insertNode(Node *root, const std::string &word, int documentId,
                 int &numComparisons);

/**
 * @brief Insere uma palavra na árvore binária AVL.
 *
 * Atualiza a raiz da árvore caso seja a primeira inserção (e retorna
 * estatísticas sobre a performance).
 *
 * @param tree Ponteiro para a árvore.
 * @param word Palavra a ser inserida.
 * @param documentId ID do documento associado.
 * @return Estrutura InsertResult contendo tempo de inserção e comparaçõelse {
 * realizadas.
 */
InsertResult insert(BinaryTree *tree, const std::string &word, int documentId);

/**
 * @brief Busca uma palavra na árvore binária AVL.
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

} // namespace AVL

#endif
