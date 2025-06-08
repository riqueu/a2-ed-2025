#include "data.h"
#include "tree_utils.h"
#include "bst.h"
#include "avl.h"
#include "export_stats.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;
using namespace DocReading;

int main(int argc, char *argv[]) {
    // Verifica se o número de argumentos é suficiente
    if (argc < 4) {
    cout << "Erro: Comando inválido.\nUso: ./tree_stats <arvore> <n_max_docs> <n_points> <diretorio>" << endl;
    return 1;
    }

    // Salva os argumentos em variáveis
    string treeType = argv[1];
    int n_max_docs = stoi(argv[2]);
    int n_points = stoi(argv[3]);
    string path = argv[4];

    // Lê documentos do diretório especificado
    Doc **docs = readDocuments(n_max_docs, path);
    if (docs == nullptr) {
        cout << "Erro ao ler documentos do diretório: " << path << endl;
        return 1;
    }

    // Inicializa a árvore
    BinaryTree *tree = nullptr;
    // Vetor para armazenar o número de documentos a serem inseridos
    std::vector<int> n_docs;
    // Vetor para armazenar estatísticas das árvores
    std::vector<stats::TreeStats> stats;

    // Gera os números de documentos que serão inseridos, distribuindo-os uniformemente, tendo um total de 25 
    int step = std::max(1, n_max_docs / n_points); // Define o passo
    for (int i = 1; i <= n_points; ++i) {
        int value = i * step;
        if (value > n_max_docs) {
            break;
        };
        n_docs.push_back(value);
    }
    if (n_docs.back() != n_max_docs) {
        n_docs.push_back(n_max_docs); // Garante que o último ponto seja exatamente n_max_docs
    };

    // Seleciona o tipo de árvore
    if (treeType == "bst") {
        // Cria as n_points árvores binária de busca
        cout << "Criando arvore binaria de busca (BST)..." << endl;
        for (int n : n_docs) {
            tree = BST::create();

            stats::TreeStats s = {n, 0, 0.0, 0.0, 0, 0, 0.0, 0.0, 0};

            // Insere palavras dos documentos na árvore
            for (int i = 0; i < n && i < n_max_docs; i++) {
                for (size_t j = 0; j < docs[i]->content->size(); j++) {
                    InsertResult result = BST::insert(tree, docs[i]->content->at(j), docs[i]->docID);
                    s.numComparisonsInsertion += result.numComparisons;
                    s.executionTimeInsertion += result.executionTime;
                }
            }

            s.executionTimeInsertionMean = s.executionTimeInsertion / n; // Calcula o tempo médio de inserção

            vector<string> search_words = {"exemplo", "palavra", "busca", "arvore", "documento"}; // Palavras a serem buscadas
            // Busca cada palavra do vetor search_words na árvore
            for (const string& word : search_words) {
                SearchResult search = BST::search(tree, word);
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

            // Pega a altura da árvore
            int tree_height = stats::get_tree_height(tree->root);
            s.treeHeight = tree_height; // Armazena a altura da árvore

            // Armazena as estatísticas da árvore
            stats.push_back(s); // Adiciona as estatísticas ao vetor
            
            // Libera a memória da árvore atual
            BST::destroy(tree);
        }
    } else if (treeType == "avl") {
        // Cria as n_points árvores binária de busca
        cout << "Criando arvore binaria de busca (AVL)..." << endl;
        for (int n : n_docs) {
            tree = AVL::create();

            stats::TreeStats s = {n, 0, 0.0, 0.0, 0, 0, 0.0, 0.0, 0};

            // Insere palavras dos documentos na árvore
            for (int i = 0; i < n && i < n_max_docs; i++) {
                for (size_t j = 0; j < docs[i]->content->size(); j++) {
                    InsertResult result = AVL::insert(tree, docs[i]->content->at(j), docs[i]->docID);
                    s.numComparisonsInsertion += result.numComparisons;
                    s.executionTimeInsertion += result.executionTime;
                }
            }

            s.executionTimeInsertionMean = s.executionTimeInsertion / n; // Calcula o tempo médio de inserção

            vector<string> search_words = {"exemplo", "palavra", "busca", "arvore", "documento"}; // Palavras a serem buscadas
            // Busca cada palavra do vetor search_words na árvore
            for (const string& word : search_words) {
                SearchResult search = AVL::search(tree, word);
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

            // Pega a altura da árvore
            s.treeHeight = tree->root->height; // Armazena a altura da árvore

            // Armazena as estatísticas da árvore
            stats.push_back(s); // Adiciona as estatísticas ao vetor
            
            // Libera a memória da árvore atual
            AVL::destroy(tree);
        }
    } else {
        cout << "Erro: Tipo de arvore invalido. Use 'bst' ou 'avl'." << endl;
        return 1;
    }

    // Libera a memória dos documentos lidos
    deleteDocs(docs, n_max_docs);

    // Gera o arquivo CSV com as estatísticas
    string title = "dados_" + treeType + ".csv";
    exportToCSV(stats, title);

    return 0;
}

// Comando para rodar o programa: ./src/output/tree_stats avl 1000 25 data/
// Comando para rodar o programa: ./src/output/tree_stats bst 1000 25 data/