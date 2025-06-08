#include "tree_utils.h"
#include "data.h"
#include "bst.h"
#include "avl.h"
#include <iostream>
#include <algorithm>

void printIndexRec(Node *node) {
  if (node == nullptr) {
    return;
  }

  // Recursão para os nós a esquerda
  printIndexRec(node->left);

  // Exibe a palavra e os IDs dos documentos em que ela aparece
  std::cout << node->word << ": ";
  int size = node->documentIds.size();
  if (size > 0) {
    for (int i = 0; i < size - 1; i++) {
      std::cout << node->documentIds[i] << ", ";
    }
    std::cout << node->documentIds[size - 1];
    std::cout << "\n";
  };

  // Recursão para os nós a direita
  printIndexRec(node->right);
}

void printIndex(BinaryTree *tree) {
  if (tree == nullptr) {
    return;
  }

  // Chamada da função recursiva
  printIndexRec(tree->root);
}

void printTreeRec(Node *node, std::string prefix = "",
                  std::string linePrefix = "") {
  if (node == nullptr) {
    return;
  }

  // Exibe o nó atual na árvore
  std::cout << prefix << linePrefix;
  std::cout << node->word << std::endl;

  // Recursão caso haja um nó a esquerda
  if (node->left) {
    printTreeRec(node->left, prefix + "    ", "--- ");
  }

  // Recursão caso haja um nó a direita
  if (node->right) {
    printTreeRec(node->right, prefix + "    ", "+-- ");
  }
}

void printTree(BinaryTree *tree) {
  if (tree == nullptr) {
    return;
  }

  // Chamada da função recursiva
  printTreeRec(tree->root);
}

namespace stats {
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

TreeStats get_tree_stats(const std::string &tree_type, int n_docs, int n_max_doc, const std::vector<DocReading::Doc*>& docs, const std::vector<std::string>& search_words) {
    BinaryTree* tree = nullptr;
    TreeStats s = {n_docs, 0, 0.0, 0.0, 0, 0, 0.0, 0.0, 0};

    if (tree_type == "bst") {
        tree = BST::create();
    } else if (tree_type == "avl") {
        tree = AVL::create();
    } else {
        return s;
    }

    int numWords = 0;

    // Insere palavras dos documentos na árvore
    for (int i = 0; i < n_docs && i < n_max_doc; i++) {
        for (size_t j = 0; j < docs[i]->content->size(); j++) {
            InsertResult result;
            if (tree_type == "bst") {
                result = BST::insert(tree, docs[i]->content->at(j), docs[i]->docID);
            } else {
                result = AVL::insert(tree, docs[i]->content->at(j), docs[i]->docID);
            }
            s.numComparisonsInsertion += result.numComparisons;
            s.executionTimeInsertion += result.executionTime;
            numWords += 1;
        }
    }

    s.executionTimeInsertionMean = s.executionTimeInsertion / numWords; // Calcula o tempo médio de inserção

    // Busca cada palavra do vetor search_words na árvore
    for (const std::string& word : search_words) {
        SearchResult search;
        if (tree_type == "bst") {
            search = BST::search(tree, word);
        } else {
            search = AVL::search(tree, word);
        }
        s.numComparisonsSearchMean += search.numComparisons;
        s.executionTimeSearchMean += search.executionTime;
        // Atualiza o número máximo de comparações
        if (search.numComparisons > s.numComparisonsSearchMax) {
            s.numComparisonsSearchMax = search.numComparisons;
        }
        if (search.executionTime > s.executionTimeSearchMax) {
            s.executionTimeSearchMax = search.executionTime;
        }
    }
    // Calcula o número médio de comparações e o tempo médio de busca
    s.numComparisonsSearchMean /= search_words.size();
    s.executionTimeSearchMean /= search_words.size();

    // Pega a altura da árvore
    if (tree_type == "avl") {
        s.treeHeight = tree->root->height; // Armazena a altura da árvore AVL
    } else {
        // Para as outras, calcula a altura usando a função auxiliar
        s.treeHeight = get_tree_height(tree->root);
    }

    // Libera a memória da árvore atual
    if (tree_type == "bst") {
        BST::destroy(tree);
    } else if( tree_type == "avl") {
        AVL::destroy(tree);
    }

    return s;
}
} // namespace stats
