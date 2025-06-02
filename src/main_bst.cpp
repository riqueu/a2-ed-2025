#include <iostream>
#include <ostream>
#include "bst.h"
#include "data.h"

using namespace std;
using namespace DocReading;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Erro: Nenhum comando fornecido. Estrutura esperada: ./<arvore> <comando> <n_docs> <diretório>" << endl;
    return 1;
  }

  string command = argv[1];

  if (command == "search") {

    if (argc != 4) {
      cout << "Erro, estrutura esperada: " << endl << "./<arvore> search <n_docs> <diretório>";
      return 0;
    }

    string n = argv[2];
    int n_docs = stoi(n);
    string path = argv[3];

    Doc** docs = readDocuments(n_docs, path);
    BinaryTree* bst = BST::create();


    // Itera sobre cada palavra no documento e insere ela na árvore
    for (int i = 0; i < n_docs; i++) {
      // cout << "Palavras do Documento com ID: " << docs[i]->docID << endl;
      for (size_t j = 0; j < docs[i]->content->size(); j++) {
        BST::insert(bst, docs[i]->content->at(j), docs[i]->docID); 
        // cout << docs[i]->content->at(j) << endl;
       }
     }          

    //printTree(bst);

    string repeat = "s";
    while(repeat == "s") {

      string word;
      cout << "Indexação das palavras concluídas!" << endl << "Digite a que você quer buscar: ";
      cin >> word;

      SearchResult search = BST::search(bst, word);

      cout << "Encontrou? ";
      if (search.found == 1) {
        cout << "SIM! ;)" << endl << "IDs dos documentos: { ";
        for (size_t i = 0; i < search.documentIds.size(); i++) {
          cout << search.documentIds[i];
          if (i < search.documentIds.size() - 1) cout << ", ";
        }
        cout << " }" << endl;
      } else {
        cout << "NÃO! :/" << endl;
      }

      cout << "Tempo de execução: " << search.executionTime << endl << "Número de comparações: " << search.numComparisons << endl;

      cout << "Deseja continuar buscando? digite: 's' para sim ou 'n' para sair: " << endl;
      cin >> repeat;
    }
  }
}
