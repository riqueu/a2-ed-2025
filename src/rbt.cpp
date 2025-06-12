#include "rbt.h"
#include "tree_utils.h"
#include <vector>

namespace RBT {

BinaryTree *create() {
  // Criação da árvore
  BinaryTree *binaryTree = new BinaryTree;
  binaryTree->root = nullptr;

  // Criação do NIL
  Node* nil = new Node;
  nil->isRed = false;
  binaryTree->NIL = nil;
  return binaryTree;
}

Node *createNode(const std::string &word, int documentId) {
  // Criação e definições iniciais de um nó
  Node *node = new Node;
  node->word = word;
  node->documentIds.push_back(documentId);
  node->parent = nullptr;
  node->left = nullptr;
  node->right = nullptr;
  node->height = 0;

  // Cor inicial é vermelho
  node->isRed = true;

  return node;
}

int getHeight(Node *node) { return node == nullptr ? -1 : node->height; }

Node *rotateRight(Node *node) {
  Node *newRoot = node->left;
  node->left = newRoot->right;

  if (newRoot->right != nullptr) {
    newRoot->right->parent = node;
  }

  newRoot->right = node;
  newRoot->parent = node->parent;
  node->parent = newRoot;

  // Atualizar alturas dos nós
  node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
  newRoot->height =
      std::max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

  return newRoot;
}

Node *rotateLeft(Node *node) {
  Node *newRoot = node->right;
  node->right = newRoot->left;

  if (newRoot->left != nullptr) {
    newRoot->left->parent = node;
  }

  newRoot->left = node;
  newRoot->parent = node->parent;
  node->parent = newRoot;

  // Atualizar alturas dos nós
  node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
  newRoot->height =
      std::max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

  return newRoot;
}

void deleteNodes(Node *root) {
  if (root == nullptr) {
    return;
  } else if (root->left == nullptr) {
    return;
  }

  // Recurção para deletar os nós, não tem necessidade de verificar se são
  // nullptr, pois a recurção já faz isso
  deleteNodes(root->left);
  deleteNodes(root->right);

  delete root;
  return;
}

void destroy(BinaryTree *tree) {
  if (tree == nullptr) {
    return;
  }

  // Deleta todos os nós da árvore recursivamente
  deleteNodes(tree->root);

  delete tree->NIL;

  delete tree;
  return;
}

}