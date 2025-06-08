#include "export_stats.h"
#include "tree_stats.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void exportToCSV(const std::vector<TreeStats>& stats) {
    ofstream arquivo("dados.csv");
    // Cabeçalho
    arquivo << "N_docs,NumComparisons,ExecutionTime,TreeHeight\n";
    for (const auto& s : stats) {
        arquivo << s.n_docs << "," << s.numComparisons << "," << s.executionTime << "," << s.treeHeight << "\n";
    }
    arquivo.close();
    cout << "Dados exportados para dados.csv com sucesso!" << endl;
}