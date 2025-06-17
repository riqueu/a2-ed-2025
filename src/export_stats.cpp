#include "export_stats.h"
#include "tree_utils.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

using namespace std;

void exportToCSV(const std::vector<stats::TreeStats> &stats,
                 std::string title) {
  std::string dir = "docs";
  std::string full_path;

  fs::path final_path = fs::path(dir) / title;
  full_path = final_path.string();
  
  // Cria o arquivo CSV
  ofstream arquivo(full_path);

  // Cabeçalho
  arquivo << "N_docs,"
             "ExecutionTimeInsertionMean,ExecutionTimeInsertionTotal,"
             "ExecutionTimeSearchMean,ExecutionTimeSearchMax,"
             "NumComparisonsInsertionMean,NumComparisonsInsertionTotal,"
             "NumComparisonsSearchMean,NumComparisonsSearchMax,"
             "TreeHeight,MaxBranch,MinBranch,"
             "NumNodes,"
             "TreeSizeBytes\n";

  // Preenche as linhas
  for (const auto &s : stats) {
    arquivo << s.n_docs << "," 
            << s.executionTimeInsertionMean << "," << s.executionTimeInsertion << "," 
            << s.executionTimeSearchMean << "," << s.executionTimeSearchMax << ","
            << s.numComparisonsInsertionMean << "," << s.numComparisonsInsertion << "," 
            << s.numComparisonsSearchMean << "," << s.numComparisonsSearchMax << ","  
            << s.treeHeight << "," << s.treeHeight << "," << s.minBranch << "," 
            << s.numNodes << "," << s.size << "\n";
  }

  // Fecha o arquivo
  arquivo.close();
  cout << "Dados exportados para " << full_path << " com sucesso!" << endl;
}
