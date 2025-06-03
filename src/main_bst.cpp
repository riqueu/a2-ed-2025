#include "bst.h"
#include "data.h"
#include <iostream>
#include <ostream>

using namespace std;
using namespace DocReading;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Erro: Nenhum comando fornecido. Estrutura esperada: ./<arvore> "
            "<comando> <n_docs> <diretório>"
         << endl;
    return 1;
  }

  string command = argv[1];

  if (command == "search") {

    if (argc != 4) {
      cout << "Erro, estrutura esperada: " << endl
           << "./<arvore> search <n_docs> <diretório>";
      return 0;
    }

    string n = argv[2];
    int n_docs = stoi(n);
    string path = argv[3];

    Doc **docs = readDocuments(n_docs, path);
    BinaryTree *bst = BST::create();

    // Itera sobre cada palavra no documento e insere ela na árvore
    for (int i = 0; i < n_docs; i++) {
      // cout << "Palavras do Documento com ID: " << docs[i]->docID << endl;
      for (size_t j = 0; j < docs[i]->content->size(); j++) {
        BST::insert(bst, docs[i]->content->at(j), docs[i]->docID);
        // cout << docs[i]->content->at(j) << endl;
      }
    }

    // printTree(bst);

    string repeat = "s";

    while (repeat == "s") {
      string word;
      cout << "Indexacao das palavras concluida!" << endl
           << "Digite a que você quer buscar: ";
      cin >> word;

      SearchResult search = BST::search(bst, word);

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
        cout << "NÃO! :/" << endl;
      }

      cout << "Tempo de execucaoo: " << search.executionTime << endl
           << "Número de comparacoes: " << search.numComparisons << endl;

      cout << "Deseja continuar buscando? digite: 's' para sim ou 'n' para "
              "sair: "
           << endl;
      cin >> repeat;
    }

    // free memory
    BST::destroy(bst);
    for (int i = 0; i < n_docs; i++) {
      delete docs[i];
    }
    delete[] docs;
  }

  if (command == "stats") {
    if (argc != 4) {
      cout << "Erro, estrutura esperada: " << endl
           << "./<arvore> stats <n_docs> <diretório>" << endl;
      return 0;
    }

    string n = argv[2];
    int n_docs = stoi(n);
    string path = argv[3];

    // mede o tempo de leitura dos documentos
    auto startRead = std::chrono::high_resolution_clock::now();
    Doc **docs = readDocuments(n_docs, path);
    auto endRead = std::chrono::high_resolution_clock::now();
    double readTime =
        std::chrono::duration<double, std::milli>(endRead - startRead).count();
    cout << "Tempo de leitura dos documentos: " << readTime << " ms" << endl;

    BinaryTree *bst = BST::create();

    // perform insertions
    InsertResult totalResult;
    totalResult.numComparisons = 0;
    totalResult.executionTime = 0.0;

    for (int i = 0; i < n_docs; i++) {
      for (size_t j = 0; j < docs[i]->content->size(); j++) {
        InsertResult result =
            BST::insert(bst, docs[i]->content->at(j), docs[i]->docID);
        totalResult.numComparisons += result.numComparisons;
        totalResult.executionTime += result.executionTime;
      }
    }

    cout << "Tempo total de insercaoo: " << totalResult.executionTime << " ms"
         << endl;
    cout << "Número total de comparacoes: " << totalResult.numComparisons
         << endl;

    // free memory
    BST::destroy(bst);
    for (int i = 0; i < n_docs; i++) {
      delete docs[i];
    }
    delete[] docs;
  }
}
