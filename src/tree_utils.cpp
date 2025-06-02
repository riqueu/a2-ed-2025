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
  for (int i = 0; i < size - 1; i++) {
    std::cout << node->documentIds[i] << ", ";
  }
  std::cout << node->documentIds[size - 1];
  std::cout << "\n";

  // Recursão para os nós a esquerda
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
