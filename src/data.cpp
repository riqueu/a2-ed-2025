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

    void deleteDocs(Doc** documents, int numDocs) {
        // Deleta cada documento
        for (int i=0; i<numDocs; i++) {
            delete documents[i]->content;
            delete documents[i];
        }

        // Deleta o array de documentos
        delete[] documents;
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
    };

    Doc** readDocuments(int numDocs) {
        // Inicializa o array de documentos
        Doc** Docs = new Doc*[numDocs];

        for(int i=0; i<numDocs; i++) {
            // Constroi o caminho para o arquivo
            string path = "..\\data\\" + to_string(i) + ".txt";
            // Carrega o arquivo
            ifstream file(path);

            // Cria a estrutura do documento
            Doc* document = createDoc(i);

            // Coleta palavra por palavra
            std::string word;
            while (file >> word) {
                // Verifica se a palavra ja nao foi coletada
                bool word_in_document = wordInDocumentCheck(document, word);

                // Se a palavra nao for coletada, coloca ela na lista de palavras do documento
                if(!word_in_document) {
                    document->content->push_back(word);
                }
            }

            // Insere o documento no array de documentos
            Docs[i] = document;

            // Fecha o arquivo
            file.close();
        }

        // Retorna os documentos
        return Docs;
    };
    
}