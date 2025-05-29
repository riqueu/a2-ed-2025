#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

  string command = argv[1];

  if (command == "search") {

    if (argc != 4) {
      cout << "Error, estrutura esperada: " << endl << "./<arvore> search <n_docs> <diretório>";
      return 0;
    }

    string n = argv[2];
    int n_docs = stoi(n);
    string path = argv[3];

    cout << "Digite a palavra para ser buscada: ";
    string word;
    cin >> word;

        
  }  
  
}
