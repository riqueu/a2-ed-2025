#include "export_stats.h"
#include "tree_utils.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void exportToCSV(const std::vector<stats::TreeStats>& stats, std::string title) {
    // Cria o arquivo CSV
    ofstream arquivo(title);

    // Cabeçalho
    arquivo << "N_docs,NumComparisonsInsertion,ExecutionTimeInsertionMean,ExecutionTimeInsertion,NumComparisonsSearchMean,NumComparisonsSearchMax,ExecutionTimeSearchMean,ExecutionTimeSearchMax,TreeHeight\n";
    

    // Preenche as linhas
    for (const auto& s : stats) {
        arquivo << s.n_docs << "," << s.numComparisonsInsertion << "," << s.executionTimeInsertionMean << "," << s.executionTimeInsertion << "," << s.numComparisonsSearchMean << "," << s.numComparisonsSearchMax << "," << s.executionTimeSearchMean << "," << s.executionTimeSearchMax << "," << s.treeHeight << "\n";
    }

    // Fecha o arquivo
    arquivo.close();
    cout << "Dados exportados para dados.csv com sucesso!" << endl;
}