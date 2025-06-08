#include "tree_utils.h"
#include <iostream>

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
} // namespace stats
