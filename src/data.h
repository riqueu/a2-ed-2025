#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>

namespace DocReading {
    // Define as estruturas

    /**
     * @brief Estrutura do Documento
     * 
     * Essa estrutura armazena o id do documento e seu conteudo
     */
    struct Doc
    {
        /**
         * @brief ID do documento
         */
        int docID;
        /**
         * @brief Vetor com todas as palavras do documento
         */
        std::vector<std::string>* content;
    };

    // Define as funcoes

    /**
     * @brief Inicializa um documento
     * 
     * Essa funcao inicializa um instacia da estrutura documento e o vetor de conteudo do documento
     * 
     * @param id ID do documento
     * @return Ponteiro do documento inicializado
     */
    Doc* createDoc(int id);

    /**
     * @brief Imprime o array de documentos
     * 
     * Essa funcao imprime o array de documentos, palavra por palavra
     * 
     * @param documents Array de documentos
     * @param numDocs Numero de documentos
     */
    void printDocs(Doc** documents, int numDocs);

    /**
     * @brief Deleta o array de documentos
     * 
     * Essa funcao deleta o array de documentos, cada documento, e o vetor de palavras
     * 
     * @param documents Array de documentos
     * @param numDocs Numero de documentos
     */
    void deleteDocs(Doc** documents, int numDocs);

    /**
     * @brief Verifica se uma palavra esta em um documento
     * 
     * Retorna True se a palavra estiver no documento e False se nao estiver
     * 
     * @param document Documento
     * @param word Palavra procurada
     * @return Boleano que indica se a palavra esta ou nao no documento
     */
    bool wordInDocumentCheck(Doc* document, std::string word);
    
    /**
     * @brief Extrai as palavras da quantidade de documentos solicitada
     * 
     * Essa funcao processa cada um dos documentos, coloca seu conteudo na estrutura Doc e retorna um array com o conteudo de todos os documentos solicitados
     * 
     * @param numDocs Numero de documentos a serem lidos
     * @param dirPath Caminho para a pasta com os arquivos
     * @return Array de documentos
     */
    Doc** readDocuments(int numDocs, std::string dirPath);

};

#endif