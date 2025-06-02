#include <iostream>
#include <fstream>
#include <filesystem>
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

    void printDocs(Doc** documents, int numDocs) {
        for (int i=0; i<numDocs; i++) {
            // Para cada documento, imprime o id
            cout << "Documento " << i << ": ";
            for (int j=0; j<documents[i]->content->size(); j++) {
                // Para cada palavra, imprime a palavra
                cout << documents[i]->content->at(j) << " ";
            }
            cout << endl;
        }
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

    Doc** readDocuments(int numDocs, string dirPath) {
        // Inicializa o array de documentos
        Doc** Docs = new Doc*[numDocs];

        // Cria o iterador do diretorio
        filesystem::directory_iterator dir(dirPath);

        for(int i=0; i<numDocs; i++) {
            // Verifica se o iterador nao esta vazio
            if (dir != filesystem::directory_iterator()) {

                // Coleta o caminho para o proximo arquivo
                filesystem::path path = dir->path();

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

                // Avanca um arquivo no diretorio
                ++dir;
            }
        }

        // Retorna os documentos
        return Docs;
    };
    
}
