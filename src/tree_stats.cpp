#include "tree_stats.h"
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
    std::vector<TreeStats> stats;

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
            InsertResult totalResult;
            totalResult.numComparisons = 0;
            totalResult.executionTime = 0.0;

            // Insere palavras dos documentos na árvore
            for (int i = 0; i < n && i < n_max_docs; i++) {
                for (size_t j = 0; j < docs[i]->content->size(); j++) {
                    InsertResult result = BST::insert(tree, docs[i]->content->at(j), docs[i]->docID);
                    totalResult.numComparisons += result.numComparisons;
                    totalResult.executionTime += result.executionTime;
                }
            }

            // Pega a altura da árvore
            int tree_height = get_tree_height(tree->root);

            // Armazena as estatísticas da árvore
            TreeStats s;
            s.n_docs = n;
            s.numComparisons = totalResult.numComparisons;
            s.executionTime = totalResult.executionTime;
            s.treeHeight = tree_height;
            stats.push_back(s); // Adiciona as estatísticas ao vetor
            
            // Libera a memória da árvore atual
            BST::destroy(tree);
        }
    } else if (treeType == "avl") {
        // Cria as n_points árvores binária de busca
        cout << "Criando arvore binaria de busca (AVL)..." << endl;
        for (int n : n_docs) {
            tree = AVL::create();
            InsertResult totalResult;
            totalResult.numComparisons = 0;
            totalResult.executionTime = 0.0;

            // Insere palavras dos documentos na árvore
            for (int i = 0; i < n && i < n_max_docs; i++) {
                for (size_t j = 0; j < docs[i]->content->size(); j++) {
                    InsertResult result = AVL::insert(tree, docs[i]->content->at(j), docs[i]->docID);
                    totalResult.numComparisons += result.numComparisons;
                    totalResult.executionTime += result.executionTime;
                }
            }

            // Pega a altura da árvore
            int tree_height = tree->root->height;

            // Armazena as estatísticas da árvore
            TreeStats s;
            s.n_docs = n;
            s.numComparisons = totalResult.numComparisons;
            s.executionTime = totalResult.executionTime;
            s.treeHeight = tree_height;
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

int get_tree_height(Node *root){
    if (root == nullptr) {
        return 0; // A altura de uma árvore vazia é 0
    }

    // Calcula a altura das subárvores esquerda e direita
    int leftHeight = get_tree_height(root->left);
    int rightHeight = get_tree_height(root->right);

    // A altura da árvore é o máximo entre as alturas das subárvores, mais 1 para o nó atual
    return std::max(leftHeight, rightHeight) + 1;
}

// TODO: Fazer a criação do .exe desse arquivo no Makefile: g++ -Wall -Wextra -g3 src/tree_stats.cpp src/bst.cpp src/avl.cpp src/data.cpp src/tree_utils.cpp src/export_stats.cpp -o src/output/tree_stats.exe
// lembrando que falta a rbt
// Comando para rodar o programa: ./src/output/tree_stats avl 1000 25 data/
// Comando para rodar o programa: ./src/output/tree_stats bst 1000 25 data/