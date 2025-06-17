#include "rbt.h"
#include "tree_utils.h"
#include <vector>
#include <iostream>

namespace RBT {

BinaryTree *create() {
  // Criação da árvore
  BinaryTree *binaryTree = new BinaryTree;
  binaryTree->root = nullptr;

  // Criação do NIL
  Node* nil = new Node;
  nil->left = nullptr;
  nil->right = nullptr;
  nil->parent = nullptr;
  nil->isRed = false;
  nil->height = -1;
  binaryTree->NIL = nil;
  return binaryTree;
}

Node *createNode(const std::string &word, int documentId, Node *nil) {
  // Criação e definições iniciais de um nó
  Node *node = new Node;
  node->word = word;
  node->documentIds.push_back(documentId);
  node->parent = nullptr;
  node->left = nil;
  node->right = nil;
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

void fixInsert(Node *node, BinaryTree *tree) {
  // Se o pai for preto, não precisa consertar, inclusive caso node raiz, já que nil é preto
  if (node->parent->isRed == false) {
    return;
  }

  // Verifica se o pai é filho a esquerda
  if (node->parent == node->parent->parent->left) {
    Node* tio = node->parent->parent->right;
    Node* vo = node->parent->parent;
    // Caso 1: pai e tio vermelhos
    if (tio->isRed == true) {
      node->parent->isRed = false;
      tio->isRed = false;
      vo->isRed = true;
      fixInsert(node->parent->parent, tree);
    } else {
      // Caso 2: filho à direita → precisa girar para formar o caso filho à esquerda com tio preto → rotação e recoloração
      if (node == node->parent->right) {
        node = node->parent;
        vo->left = rotateLeft(node);
      } 
      // Caso 3: filho à esquerda com tio preto → rotação e recoloração
      node->parent->isRed = false;
      vo->isRed = true;
      // Verifica se o vô não era a raiz, se for altera para o pai do vô
      // Rotaciona o vô
      if (vo == tree->root) {
        rotateRight(vo);
        tree->root = vo->parent;
      } else if (vo == vo->parent->left) {
        vo->parent->left = rotateRight(vo);
      } else {
        vo->parent->right = rotateRight(vo);
      }
    }

  // Verifica se o pai é filho a direita
  } else {
    Node* tio = node->parent->parent->left;
    Node* vo = node->parent->parent;
    // Caso pai e tio vermelhos
    if (tio->isRed == true) {
      node->parent->isRed = false;
      tio->isRed = false;
      node->parent->parent->isRed = true;
      fixInsert(node->parent->parent, tree);
    } else {
      // Caso 2: filho à esquerda → precisa girar para formar o caso 3
      if (node == node->parent->left) {
        node = node->parent;
        vo->right = rotateRight(node);
      } 
      // Caso 3: filho à direita com tio preto → rotação e recoloração
      node->parent->isRed = false;
      vo->isRed = true;
      // Verifica se o vô não era a raiz, se for altera para o pai do vô
      // Rotaciona o vô
      if (vo == tree->root) {
        rotateLeft(vo);
        tree->root = vo->parent;
      } else if (vo == vo->parent->left) {
        vo->parent->left = rotateLeft(vo);
      } else {
        vo->parent->right = rotateLeft(vo);
      }
      }
    }
  }

void insertNode(Node *root, BinaryTree *tree, const std::string &word, int documentId,
                 int &numComparisons) {
  // Verifica se não tem raiz
  if (root == nullptr) {
    Node* newNode = createNode(word, documentId, tree->NIL);
    newNode->parent = tree->NIL;
    newNode->isRed = false;
    tree->root = newNode;
    return;
  }
  
  // Incrementa o número de comparações
  numComparisons++;

  // insert recursivo
  if (word < root->word) { // está a esquerda do nó atual
    // Se a esquerda tiver vazia, coloca o nó lá e conserta as propriedades
    if (root->left == tree->NIL) {
      Node* newNode = createNode(word, documentId, tree->NIL);
      newNode->parent = root;
      root->left = newNode;

      // Conserta as propriedades
      fixInsert(root->left, tree);
      // Garante que a raiz é preta
      tree->root->isRed = false;
    } else {
      // Se tiver ocupada avança a recursão
      insertNode(root->left, tree, word, documentId, numComparisons);
    }
  } else if (word > root->word) { // está a direita do nó atual
    // Se a direita tiver vazia, coloca o nó lá e conserta as propriedades
    if (root->right == tree->NIL) {
      Node* newNode = createNode(word, documentId, tree->NIL);
      newNode->parent = root;
      root->right = newNode;

      // Conserta as propriedades
      fixInsert(root->right, tree);
      // Garante que a raiz é preta
      tree->root->isRed = false;
    } else {
      // Se tiver ocupada avança a recursão
      insertNode(root->right, tree, word, documentId, numComparisons);
    }
  } else { // palavra já existe na árvore, adiciona o ID do documento
    root->documentIds.push_back(documentId);
  }

  // Atualiza a altura do nó atual
  root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
}

InsertResult insert(BinaryTree *tree, const std::string &word, int documentId) {
  InsertResult result;
  result.numComparisons = 0;
  result.executionTime = 0;

  if (tree == nullptr) {
    return result;
  }

  // Mede o tempo de execução da inserção
  auto start = std::chrono::high_resolution_clock::now();
  // Insere o nó
  insertNode(tree->root, tree, word, documentId, result.numComparisons);
  // Garante que a raiz é preta
  tree->root->isRed = false;
  auto end = std::chrono::high_resolution_clock::now();

  // Calcula o tempo gasto para inserir o nó (em milissegundos)
  result.executionTime =
      std::chrono::duration<double, std::milli>(end - start).count();

  return result;
}

SearchResult search(BinaryTree *tree, const std::string &word) {
  if (tree == nullptr || tree->root == nullptr) {
    return {0, {}, 0.0, 0};
  }

  // inicializa as variáveis
  auto start = std::chrono::high_resolution_clock::now();
  int numComparisons = 0;
  Node *current = tree->root;
  SearchResult result;
  result.found = 0;

  // verifica se o nó atual é a palavra que busco
  // se não é, atualiza o current
  while (current != nullptr && current != tree->NIL) {
    numComparisons++;
    if (word == current->word) {
      result.documentIds = current->documentIds;
      result.found = 1;
      break;
    } else if (word > current->word) {
      current = current->right;
    } else {
      current = current->left;
    }
  }

  // insere os resultados obtidos
  result.numComparisons = numComparisons;
  auto end = std::chrono::high_resolution_clock::now();
  result.executionTime =
      std::chrono::duration<double, std::milli>(end - start).count();

  return result;
}

void deleteNodes(Node *root, Node *nil) {
  if (root == nullptr or root == nil) {
    return;
  }

  // Recurção para deletar os nós, não tem necessidade de verificar se são
  // nullptr, pois a recurção já faz isso
  deleteNodes(root->left, nil);
  deleteNodes(root->right, nil);

  delete root;
  return;
}

void destroy(BinaryTree *tree) {
  if (tree == nullptr) {
    return;
  }

  // Deleta todos os nós da árvore recursivamente
  deleteNodes(tree->root, tree->NIL);

  delete tree->NIL;

  delete tree;
  return;
}

}
