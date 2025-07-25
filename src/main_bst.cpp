#include "bst.h"
#include "data.h"
#include "tree_utils.h"
#include <filesystem>
#include <iostream>
#include <ostream>

using namespace std;
using namespace DocReading;

int main(int argc, char *argv[]) {

  // verifica se foi passado um número suficiente de parâmetros
  if (argc < 2) {
    cout << "Erro: Nenhum comando fornecido. Estrutura esperada: ./<arvore> "
            "<comando(search/stats/print> <n_docs> <diretorio>"
         << endl;
    return 1;
  }
  string command = argv[1];

  // se o comando for o search
  if (command == "search") {

    // se a estrutura não for a esperada para search
    if (argc != 4) {
      cout << "Erro, estrutura esperada: " << endl
           << "./<arvore> search <n_docs> <diretorio>";
      return 0;
    }

    // parâmetros -> variáveis de entrada
    string n = argv[2];
    int n_docs = stoi(n);
    string path = argv[3];

    // Verifica se o número de documentos é válido
    int max_docs = 0;
    try {
      max_docs = distance(filesystem::directory_iterator(path),
                          filesystem::directory_iterator{});
    } catch (const filesystem::filesystem_error &e) {
      cout << "Erro ao acessar o diretorio: " << e.what() << endl;
      return 1;
    }

    if (n_docs < 1 || n_docs > max_docs) {
      cout << "Erro: O numero de documentos deve ser entre 1 e " << max_docs
           << "." << endl;
      return 0;
    }

    // ler os documentos e cria a árvore
    cout << "Leitura dos documentos iniciada..." << endl;
    Doc **docs = readDocuments(n_docs, path, [](int current, int total) {
      displayProgressBar(current, total, "Lendo documentos");
    });
    cout << endl;
    BinaryTree *bst = BST::create();

    // Itera sobre cada palavra no documento e insere ela na árvore
    for (int i = 0; i < n_docs; i++) {
      // exibe o progresso da leitura
      displayProgressBar(i + 1, n_docs, "Indexando documentos");
      for (size_t j = 0; j < docs[i]->content->size(); j++) {
        BST::insert(bst, docs[i]->content->at(j), docs[i]->docID);
      }
    }
    cout << endl;

    // loop para iterar por mais palavras na mesma indexação
    string repeat = "s";
    while (repeat == "s") {
      string word;
      cout << "Indexacao das palavras concluida!" << endl
           << "Digite a que voce quer buscar: ";
      cin >> word;

      // chama a função de busca
      SearchResult search = BST::search(bst, word);

      // exibe os dados do result
      cout << "Encontrou? ";
      if (search.found == 1) {
        cout << "SIM! ;)" << endl << "IDs dos documentos: { ";
        for (size_t i = 0; i < search.documentIds.size(); i++) {
          cout << search.documentIds[i];
          if (i < search.documentIds.size() - 1)
            cout << ", ";
        }
        cout << " }" << endl;
      } else {
        cout << "NAO! :/" << endl;
      }

      cout << "Tempo de execucao: " << search.executionTime << " ms" << endl
           << "Numero de comparacoes: " << search.numComparisons << endl;

      cout << "Deseja continuar buscando? digite: 's' para sim ou 'n' para "
              "sair: "
           << endl;
      cin >> repeat;
    }

    // free memory
    BST::destroy(bst);
    deleteDocs(docs, n_docs);
  }

  // se o comando for stats
  else if (command == "stats") {
    if (argc != 4) {
      cout << "Erro, estrutura esperada: " << endl
           << "./<arvore> stats <n_docs> <diretorio>" << endl;
      return 0;
    }

    string n = argv[2];
    int n_docs = stoi(n);
    string path = argv[3];

    // Verifica se o número de documentos é válido
    int max_docs = 0;
    try {
      max_docs = distance(filesystem::directory_iterator(path),
                          filesystem::directory_iterator{});
    } catch (const filesystem::filesystem_error &e) {
      cout << "Erro ao acessar o diretorio: " << e.what() << endl;
      return 1;
    }

    if (n_docs < 1 || n_docs > max_docs) {
      cout << "Erro: O numero de documentos deve ser entre 1 e " << max_docs
           << "." << endl;
      return 0;
    }

    // mede o tempo de leitura dos documentos
    cout << "Leitura dos documentos iniciada..." << endl;
    auto startRead = std::chrono::high_resolution_clock::now();
    Doc **docs = readDocuments(n_docs, path, [](int current, int total) {
      displayProgressBar(current, total, "Lendo documentos");
    });
    cout << endl;
    auto endRead = std::chrono::high_resolution_clock::now();

    cout << "Coletando estatísticas..." << endl;

    double readTime =
        std::chrono::duration<double, std::milli>(endRead - startRead).count();

    // Cria a árvore binária de busca e obtém as estatísticas
    stats::TreeStats s = stats::get_tree_stats(
        "bst", n_docs, n_docs, vector<Doc *>(docs, docs + n_docs));

    // Print das estatísticas
    cout << "=========Estatisticas=========" << endl;
    cout << "Tempo de leitura dos documentos: " << readTime << " ms" << endl;
    cout << "==========Insercao==========" << endl;
    cout << "Tempo total de insercao: " << s.executionTimeInsertion << " ms"
         << endl;
    cout << "Tempo medio de insercao: " << s.executionTimeInsertionMean << " ms"
         << endl;
    cout << "Numero total de comparacoes para insercao: "
         << s.numComparisonsInsertion << endl;
    cout << "Numero medio de comparacoes para insercao: "
         << s.numComparisonsInsertionMean << endl;
    cout << "===========Busca===========" << endl;
    cout << "Numero medio de comparacoes para busca: "
         << s.numComparisonsSearchMean << endl;
    cout << "Numero maximo de comparacoes para busca: "
         << s.numComparisonsSearchMax << endl;
    cout << "Tempo medio de busca: " << s.executionTimeSearchMean << " ms"
         << endl;
    cout << "Tempo maximo de busca: " << s.executionTimeSearchMax << " ms"
         << endl;
    cout << "===========Outros===========" << endl;
    cout << "Altura da arvore: " << s.treeHeight << endl;
    cout << "Comprimento do maior galho: " << s.treeHeight << endl;
    cout << "Comprimento do menor galho: " << s.minBranch << endl;
    cout << "Quantidade de palavras/nodes: " << s.numNodes << endl;
    cout << "===========Palavras que Aparecem em Mais Documentos==========="
         << endl;
    size_t limit =
        std::min(s.mostFrequentNodes.size(), static_cast<size_t>(20));
    for (size_t i = 0; i < limit; ++i) {
      const Node &node = s.mostFrequentNodes[i];
      if (node.word.empty()) {
        cout << i + 1 << " letras - (nenhuma palavra encontrada)" << endl;
        continue;
      }
      cout << i + 1 << " letras - " << node.word << " - "
           << node.documentIds.size() << " documentos;" << endl;
    }
    if (limit < 20) {
      for (size_t i = limit; i < 20; ++i) {
        cout << i + 1 << " letras - (nenhuma palavra encontrada)" << endl;
      }
    }

    // free memory
    deleteDocs(docs, n_docs);
  }

  // se o comando for o print
  else if (command == "print") {

    // se a estrutura não for a esperada para search
    if (argc != 4) {
      cout << "Erro, estrutura esperada: " << endl
           << "./<arvore> print <n_docs> <diretorio>";
      return 0;
    }

    // parâmetros -> variáveis de entrada
    string n = argv[2];
    int n_docs = stoi(n);
    string path = argv[3];

    // Verifica se o número de documentos é válido
    int max_docs = 0;
    try {
      max_docs = distance(filesystem::directory_iterator(path),
                          filesystem::directory_iterator{});
    } catch (const filesystem::filesystem_error &e) {
      cout << "Erro ao acessar o diretorio: " << e.what() << endl;
      return 1;
    }

    if (n_docs < 1 || n_docs > max_docs) {
      cout << "Erro: O numero de documentos deve ser entre 1 e " << max_docs
           << "." << endl;
      return 0;
    }

    // ler os documentos e cria a árvore
    cout << "Leitura dos documentos iniciada..." << endl;
    Doc **docs = readDocuments(n_docs, path, [](int current, int total) {
      displayProgressBar(current, total, "Lendo documentos");
    });
    cout << endl;
    BinaryTree *bst = BST::create();

    // Itera sobre cada palavra no documento e insere ela na árvore
    for (int i = 0; i < n_docs; i++) {
      // exibe o progresso da leitura
      displayProgressBar(i + 1, n_docs, "Indexando documentos");
      for (size_t j = 0; j < docs[i]->content->size(); j++) {
        BST::insert(bst, docs[i]->content->at(j), docs[i]->docID);
      }
    }
    cout << endl;

    string print_type;
    cout << "Digite o que tu quer printar!" << endl
         << "1 para printar o index, 2 para printar a árvore: ";
    cin >> print_type;
    int print_t = stoi(print_type);

    if (print_t == 1) {
      printIndex(bst);
    } else if (print_t == 2) {
      printTree(bst);
    }

    // free memory
    BST::destroy(bst);
    deleteDocs(docs, n_docs);
  } else {
    cout << "Comando invalido. Estrutura esperada: ./<arvore> "
            "<comando(search/stats/print)> <n_docs> <diretorio>"
         << endl;
    return 1;
  }
}
