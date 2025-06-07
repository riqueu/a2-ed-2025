#include "avl.h"
#include "tree_utils.h"
#include <vector>

namespace AVL {
BinaryTree *create() {
  // Criação da árvore
  BinaryTree *binaryTree = new BinaryTree;
  binaryTree->root = nullptr;
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

  return node;
}

int getHeight(Node *node) { return node == nullptr ? -1 : node->height; }

int getBalanceFactor(Node *node) {
  return node == nullptr ? 0 : getHeight(node->left) - getHeight(node->right);
}

Node *rotateRight(Node *node) {
  Node *newRoot = node->left;
  node->left = newRoot->right;
  newRoot->right = node;

  // atualizar alturas dos nós
  node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
  newRoot->height =
      std::max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

  return newRoot;
}

Node *rotateLeft(Node *node) {
  Node *newRoot = node->right;
  node->right = newRoot->left;
  newRoot->left = node;

  // atualizar alturas dos nós
  node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
  newRoot->height =
      std::max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

  return newRoot;
}

Node *balance(Node *node) {
  int balanceFactor = getBalanceFactor(node);

  // caso de desbalanceamento à esquerda (rotação à direita)
  if (balanceFactor > 1) {
    // verifica desbalanceamento no filho esquerdo
    if (getBalanceFactor(node->left) < 0) {
      // rotação dupla (esquerda-direita)
      node->left = rotateLeft(node->left);
    }
    return rotateRight(node); // rotação simples
  }

  // caso de desbalanceamento à direita (rotação à esquerda)
  if (balanceFactor < -1) {
    // verifica desbalanceamento no filho direito
    if (getBalanceFactor(node->right) > 0) {
      // rotação dupla (direita-esquerda)
      node->right = rotateRight(node->right);
    }
    return rotateLeft(node); // rotação simples
  }

  return node; // nó balanceado (caso balanceFactor in [-1, 1])
}

Node *insertNode(Node *root, const std::string &word, int documentId,
                 int &numComparisons) {
  // Caso ainda não haja um nó com a palavra
  if (root == nullptr) {
    return createNode(word, documentId);
  }

  // Incrementa o número de comparações
  numComparisons++;

  // insert recursivo
  if (word < root->word) { // está a esquerda do nó atual
    root->left = insertNode(root->left, word, documentId, numComparisons);
  } else if (word > root->word) { // está a direita do nó atual
    root->right = insertNode(root->right, word, documentId, numComparisons);
  } else { // palavra já existe na árvore, adiciona o ID do documento
    root->documentIds.push_back(documentId);
    return root;
  }

  // Atualiza a altura do nó atual
  // e então balanceia o nó atual (única parte diferente da BST)
  root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
  return balance(root);
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
  tree->root = insertNode(tree->root, word, documentId, result.numComparisons);
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
  while (current != nullptr) {
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
void deleteNodes(Node *root) {
  if (root == nullptr) {
    return;
  }

  // Recursão para deletar os nós, não tem necessidade de verificar se são
  // nullptr, pois a recursão já faz isso
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

  delete tree;
  return;
}
} // namespace AVL
