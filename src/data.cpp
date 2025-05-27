#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "data.h"

using namespace DocReading;
using namespace std;

namespace DocReading {
    Doc* createDoc(int id) {
        // Inicializa a estrutura
        Doc* newDoc = new Doc;

        // Inicializa o id e o vetor de palavras
        newDoc->docID = id;
        newDoc->content = new vector<string>;
        
        // Retorna o ponteiro da estrutura
        return newDoc;
    };

    bool wordInDocumentCheck(Doc* document, string word) {
        // Inicializa o boleano que indica se a palavra esta no documento
        bool wordInDocument = false;

        // Para cada palavra no documento, verifica se ela e a palavra procurada
        for (int i=0; i<document->content->size(); i++) {
            if (document->content->at(i) == word) {
                // Se encontrar a palavra para o loop
                wordInDocument = true;
                break;
            }
        }

        // Retorna o boleano
        return wordInDocument;
    }
    
}