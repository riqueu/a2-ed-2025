#include "export_stats.h"
#include "tree_stats.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void exportToCSV(const std::vector<TreeStats>& stats, std::string title) {
    // Cria o arquivo CSV
    ofstream arquivo(title);

    // Cabeçalho
    arquivo << "N_docs,NumComparisons,ExecutionTime,TreeHeight\n";

    // Preenche as linhas
    for (const auto& s : stats) {
        arquivo << s.n_docs << "," << s.numComparisons << "," << s.executionTime << "," << s.treeHeight << "\n";
    }

    // Fecha o arquivo
    arquivo.close();
    cout << "Dados exportados para dados.csv com sucesso!" << endl;
}