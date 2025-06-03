#include "bst.h"
#include "tree_utils.h"
#include <vector>

namespace BST {
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

Node *insertNode(Node *root, const std::string &word, int documentId,
                 int &numComparisons) {
  // Caso ainda não haja um nó com a palavra
  if (root == nullptr) {
    return createNode(word, documentId);
  }

  // Incrementa o número de comparações
  numComparisons++;

  // Caso onde se encontra o nó com a palavra
  if (root->word == word) {
    root->documentIds.push_back(documentId);
  } else if (root->word > word) { // Caso onde a palavra a ser inserida esta a
                                  // esquerda do nó atual
    Node *left = insertNode(root->left, word, documentId, numComparisons);
    root->left = left;
    left->parent = root;
  } else { // Caso análogo, só que para a direita
    Node *right = insertNode(root->right, word, documentId, numComparisons);
    root->right = right;
    right->parent = root;
  }

  return root;
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

  delete tree;
  return;
}
} // namespace BST
