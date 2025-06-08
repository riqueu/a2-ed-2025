#include "bst.h"
#include "data.h"
#include "tree_utils.h"
#include <iostream>
#include <ostream>

using namespace std;
using namespace DocReading;

int main(int argc, char *argv[]) {

  // verifica se foi passado um número suficiente de parâmetros
  if (argc < 2) {
    cout << "Erro: Nenhum comando fornecido. Estrutura esperada: ./<arvore> "
            "<comando> <n_docs> <diretorio>"
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

    // ler os documentos e cria a árvore
    Doc **docs = readDocuments(n_docs, path);
    BinaryTree *bst = BST::create();

    // Itera sobre cada palavra no documento e insere ela na árvore
    for (int i = 0; i < n_docs; i++) {
      for (size_t j = 0; j < docs[i]->content->size(); j++) {
        BST::insert(bst, docs[i]->content->at(j), docs[i]->docID);
      }
    }

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
  if (command == "stats") {
    if (argc != 4) {
      cout << "Erro, estrutura esperada: " << endl
           << "./<arvore> stats <n_docs> <diretorio>" << endl;
      return 0;
    }

    string n = argv[2];
    int n_docs = stoi(n);
    string path = argv[3];

    // mede o tempo de leitura dos documentos
    auto startRead = std::chrono::high_resolution_clock::now();
    Doc **docs = readDocuments(n_docs, path);
    auto endRead = std::chrono::high_resolution_clock::now();
    double readTime = std::chrono::duration<double, std::milli>(endRead - startRead).count();

    BinaryTree *bst = BST::create();

    stats::TreeStats s = {1, 0, 0.0, 0.0, 0, 0, 0.0, 0.0, 0};

    int numWords = 0; // Inicializa o contador de palavras

    for (int i = 0; i < n_docs; i++) {
      for (size_t j = 0; j < docs[i]->content->size(); j++) {
        InsertResult result =
            BST::insert(bst, docs[i]->content->at(j), docs[i]->docID);
        s.numComparisonsInsertion += result.numComparisons;
        s.executionTimeInsertion += result.executionTime;
        numWords += 1; // Incrementa o contador de palavras inseridas
      }
    }

    s.executionTimeInsertionMean = s.executionTimeInsertion / numWords; // Calcula o tempo médio de inserção


    vector<string> search_words = {"exemplo", "palavra", "busca", "arvore", "documento"}; // Palavras a serem buscadas
    // Busca cada palavra do vetor search_words na árvore
    for (const string& word : search_words) {
      SearchResult search = BST::search(bst, word);
      s.numComparisonsSearchMean += search.numComparisons;
      s.executionTimeSearchMean += search.executionTime;

      // Atualiza o número máximo de comparações
      if (search.numComparisons > s.numComparisonsSearchMax) {
        s.numComparisonsSearchMax = search.numComparisons;
      }
      // Atualiza o tempo máximo de execução
      if (search.executionTime > s.executionTimeSearchMax) {
        s.executionTimeSearchMax = search.executionTime;
      }
    }
    s.numComparisonsSearchMean = s.numComparisonsSearchMean / search_words.size(); // Calcula o número médio de comparações
    s.executionTimeSearchMean = s.executionTimeSearchMean / search_words.size(); // Calcula o tempo médio de busca

    // Print das estatísticas
    cout << "=========Estatisticas=========" << endl;
    cout << "Tempo de leitura dos documentos: " << readTime << " ms" << endl;
    cout << "==========Insercao==========" << endl;
    cout << "Tempo total de insercao: " << s.executionTimeInsertion << " ms"
         << endl;
    cout << "Tempo medio de insercao: " << s.executionTimeInsertionMean << " ms" 
         << endl;
    cout << "Numero total de comparacoes para insercao: " << s.numComparisonsInsertion
         << endl;
    cout << "===========Busca===========" << endl;
    cout << "Numero medio de comparacoes para busca: " << s.numComparisonsSearchMean
         << endl;
    cout << "Numero maximo de comparacoes para busca: " << s.numComparisonsSearchMax
         << endl;
    cout << "Tempo medio de busca: " << s.executionTimeSearchMean << " ms" 
         << endl;
    cout << "Tempo maximo de busca: " << s.executionTimeSearchMax << " ms" 
         << endl;
    cout << "===========Outros===========" << endl;
    cout << "Altura da arvore: " << stats::get_tree_height(bst->root) << endl;

    // free memory
    BST::destroy(bst);
    deleteDocs(docs, n_docs);
  }
}
