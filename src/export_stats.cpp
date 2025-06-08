#include "export_stats.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void exportToCSV(std::vector<std::vector<float>> data) {
    // Criando o arquivo CSV
    ofstream arquivo("dados.csv");

    // Escrevendo os dados
    for (size_t i = 0; i < data.size(); i++) { // Itera nas linhas
        for (size_t j = 0; j < data[i].size(); j++) { // Itera nas colunas
            arquivo << data[i][j];
            if (j != data[i].size() - 1) {
                arquivo << ",";
            }
        }   
        arquivo << "\n";
    }

    // Fecha o arquivo e retorna
    arquivo.close();
    cout << "Dados exportados para dados.csv com sucesso!" << endl;
}