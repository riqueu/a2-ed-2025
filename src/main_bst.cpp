#include <iostream>
#include "tmp_bst.h"
#include "data.h"

using namespace std;
using namespace DocReading;

int main(int argc, char *argv[]) {

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
    for (size_t i = 0; i < n_docs; i++) {
      // cout << "Palavras do Documento com ID: " << docs[i]->docID << endl;

      for (size_t j = 0; j < docs[i]->content->size(); j++) {
        BST::insert(bst, docs[i]->content->at(j), docs[i]->docID); 
        // cout << word << endl;
       }
     }          

    string word;
    cout << "Indexação das palavras concluídas!" << endl << "Digite a que você quer buscar: ";
    cin >> word;

    SearchResult searchRes = BST::search(bst, word);    
    

  }    

}
