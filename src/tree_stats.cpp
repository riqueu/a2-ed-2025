#include "data.h"
#include "export_stats.h"
#include "tree_utils.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace DocReading;

int main(int argc, char *argv[]) {
  // Verifica se o número de argumentos é suficiente
  if (argc < 5) {
    cout << "Erro: Comando invalido.\nUso: ./src/output/tree_stats <arvore> "
            "<n_max_docs> <n_points> <diretorio>"
         << endl;
    return 1;
  }

  // Salva os argumentos em variáveis
  string treeType = argv[1];
  int n_max_docs = stoi(argv[2]);
  int n_points = stoi(argv[3]);
  string path = argv[4];

  // Verifica se o número de documentos é válido
  int max_docs = 0;
  try {
    max_docs = distance(filesystem::directory_iterator(path),
                        filesystem::directory_iterator{});
  } catch (const filesystem::filesystem_error &e) {
    cout << "Erro ao acessar o diretorio: " << e.what() << endl;
    return 1;
  }

  if (n_max_docs < 1 || n_max_docs > max_docs) {
    cout << "Erro: O numero de documentos deve ser entre 1 e " << max_docs
         << "." << endl;
    return 0;
  }

  if (n_points < 1 || n_points > n_max_docs) {
    cout << "Erro: O numero de pontos deve ser pelo menos 1 e no maximo igual "
            "ao numero de documentos ("
         << n_max_docs << ")." << endl;
    return 0;
  }

  // Verifica se o tipo de árvore é válido antes de ler os dados
  if (treeType != "bst" && treeType != "avl" && treeType != "rbt") {
    cout << "Erro: Tipo de arvore invalido. Use 'bst', 'avl' ou 'rbt'." << endl;
    return 0;
  }

  // Lê documentos do diretório especificado (callback para acompanhar
  // progresso)
  cout << "Leitura dos documentos iniciada..." << endl;
  Doc **docs = readDocuments(n_max_docs, path, [](int current, int total) {
    displayProgressBar(current, total, "Lendo documentos");
  });
  cout << endl;

  // Vetor para armazenar o número de documentos a serem inseridos
  std::vector<int> n_docs;
  // Vetor para armazenar estatísticas das árvores
  std::vector<stats::TreeStats> stats;

  // Gera os números de documentos que serão inseridos, distribuindo-os
  // uniformemente, tendo um total de 25
  int step = std::max(1, n_max_docs / n_points); // Define o passo
  for (int i = 1; i <= n_points; ++i) {
    int value = i * step;
    if (value > n_max_docs) {
      break;
    };
    n_docs.push_back(value);
  }
  if (n_docs.back() != n_max_docs) {
    n_docs.push_back(
        n_max_docs); // Garante que o último ponto seja exatamente n_max_docs
  };

  // Seleciona o tipo de árvore
  if (treeType == "bst" || treeType == "avl" || treeType == "rbt") {
    // Cria as n_points árvores binária de busca
    cout << "Criando arvores binarias de busca (" << treeType << ")..." << endl;
    for (size_t i = 0; i < n_docs.size(); ++i) {
      int n = n_docs[i];
      // Cria a árvore de busca e gera as estatísticas
      stats::TreeStats s = stats::get_tree_stats(treeType, n, n_max_docs,
                                                 vector<Doc *>(docs, docs + n));
      // Armazena as estatísticas da árvore
      stats.push_back(s);

      // Exibe progresso da criação das árvores
      displayProgressBar(i + 1, n_docs.size(), "Coletando dados da arvore");
    }
    cout << endl; // Move to the next line after progress bar
  } else {
    cout << "Erro: Tipo de arvore invalido. Use 'bst', 'avl' ou 'rbt'." << endl;
    return 1;
  }

  // Libera a memória dos documentos lidos
  deleteDocs(docs, n_max_docs);

  // Gera o arquivo CSV com as estatísticas
  string title = "dados_" + treeType + ".csv";
  exportToCSV(stats, title);

  return 0;
}
