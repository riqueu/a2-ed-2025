#ifndef TREE_STATS_H
#define TREE_STATS_H

#include "tree_utils.h"

struct TreeStats {
    int n_docs; // Número de documentos inseridos na árvore
    int numComparisons; // Número total de comparações realizadas durante as inserções
    double executionTime; // Tempo total de execução das inserções em milissegundos
    int treeHeight; // Altura da árvore após as inserções
};

#endif