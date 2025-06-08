#ifndef TREE_STATS_H
#define TREE_STATS_H

#include "tree_utils.h"

struct TreeStats {
    int n_docs; // Número de documentos inseridos na árvore
    int numComparisons; // Número total de comparações realizadas durante as inserções
    double executionTime; // Tempo total de execução das inserções em milissegundos
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


#endif