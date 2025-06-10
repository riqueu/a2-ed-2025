#ifndef EXPORT_STATS_H
#define EXPORT_STATS_H

#include "tree_utils.h"
#include <string>
#include <vector>

/**
 * @brief Cria e exporta o csv
 *
 * @param stats Dados a serem exportados
 * @param title Titulo do arquivo CSV
 */
void exportToCSV(const std::vector<stats::TreeStats> &stats, std::string title);

#endif
