#include <vector>
#include <string>

#ifndef DATA_H
#define DATA_H

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
     * @brief Extrai as palavras da quantidade de documentos solicitada
     * 
     * Essa funcao processa cada um dos documentos, coloca seu conteudo na estrutura Doc e retorna um array com o conteudo de todos os documentos solicitados
     * 
     * @param numDocs Numero de documentos a serem lidos
     * @return Array de documentos
     */
    Doc* readDocuments(int numDocs);

};

#endif