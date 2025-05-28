#include "bst.h"
#include "tree_utils.h"
#include <iostream>


int main() {
    // Criando a árvore
    BinaryTree* tree = BST::create();

    // Inserindo palavras com diferentes documentIds
    BST::insert(tree, "banana", 1);
    BST::insert(tree, "morango", 2);
    BST::insert(tree, "cereja", 3);
    BST::insert(tree, "banana", 4);
    BST::insert(tree, "abobora", 5);
    BST::insert(tree, "morango", 6);

    // Imprimindo a árvore
    std::cout << "Arvore:\n";
    printTree(tree);
    printIndex(tree);

    // Limpando a memória
    delete tree;

    return 0;
}
