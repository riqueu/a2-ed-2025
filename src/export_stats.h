#ifndef EXPORT_STATS_H
#define EXPORT_STATS_H

#include "tree_stats.h"
#include <vector>

/**
 * @brief Cria e exporta o csv
 * 
 * @param data Dados a serem exportados
 */
void exportToCSV(const std::vector<TreeStats>& stats);

#endif