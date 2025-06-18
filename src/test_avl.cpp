#include "avl.h"
#include "tree_utils.h"
#include <iostream>
#include <string>
#include <vector>

bool testCreateTree() {
  std::cout << "=== Teste AVL::create() ===" << std::endl;
  BinaryTree *tree = AVL::create();

  bool success = true;

  // Verifica se a árvore foi criada corretamente
  if (tree != nullptr && tree->root == nullptr) {
    std::cout << "SUCESSO: Arvore AVL criada corretamente" << std::endl;
  } else {
    std::cout << "FALHA: Problema ao criar arvore AVL" << std::endl;
    success = false;
  }

  AVL::destroy(tree);
  std::cout << std::endl;

  return success;
}

bool testCreateNode() {
  // Inicia atributos do node
  std::cout << "=== Teste AVL::createNode() ===" << std::endl;
  std::string word = "morango";
  int docId = 1;

  bool success = true;

  Node *node = AVL::createNode(word, docId);

  // Verifica se o nó foi criado corretamente
  if (node != nullptr && node->word == word && node->documentIds.size() == 1 &&
      node->documentIds[0] == docId && node->parent == nullptr &&
      node->left == nullptr && node->right == nullptr && node->height == 0) {
    std::cout << "SUCESSO: Node AVL criado corretamente" << std::endl;
  } else {
    std::cout << "FALHA: Problema ao criar node AVL" << std::endl;
    success = false;
  }

  delete node;
  std::cout << std::endl;

  return success;
}

bool testRotateLeft() {
  std::cout << "=== Teste AVL::rotateLeft() ===" << std::endl;

  // Cria manualmente uma árvore desbalanceada para a rotação à esquerda
  Node *root = AVL::createNode("banana", 1);
  root->right = AVL::createNode("morango", 2);
  root->right->parent = root;

  bool success = true;

  // Realiza a rotação à esquerda
  Node *newRoot = AVL::rotateLeft(root);

  // Verifica se a rotação foi realizada corretamente
  if (newRoot->word == "morango" && newRoot->left->word == "banana" &&
      newRoot->left->parent == newRoot && newRoot->right == nullptr) {
    std::cout << "SUCESSO: Rotacao a esquerda realizada corretamente"
              << std::endl;
  } else {
    std::cout << "FALHA: Problema na rotacao a esquerda" << std::endl;
    success = false;
  }

  // Libera memória
  delete newRoot->left;
  delete newRoot;
  std::cout << std::endl;

  return success;
}

bool testRotateRight() {
  std::cout << "=== Teste AVL::rotateRight() ===" << std::endl;

  // Cria manualmente uma árvore desbalanceada para a rotação à direita
  Node *root = AVL::createNode("morango", 1);
  root->left = AVL::createNode("banana", 2);
  root->left->parent = root;

  bool success = true;

  // Realiza a rotação à direita
  Node *newRoot = AVL::rotateRight(root);

  // Verifica se a rotação foi realizada corretamente
  if (newRoot->word == "banana" && newRoot->right->word == "morango" &&
      newRoot->right->parent == newRoot && newRoot->left == nullptr) {
    std::cout << "SUCESSO: Rotacao a direita realizada corretamente"
              << std::endl;
  } else {
    std::cout << "FALHA: Problema na rotação à direita" << std::endl;
    success = false;
  }

  // Libera memória
  delete newRoot->right;
  delete newRoot;
  std::cout << std::endl;

  return success;
}

bool testBalanceFactor() {
  std::cout << "=== Teste AVL::getBalanceFactor() ===" << std::endl;

  // Cria manualmente uma árvore para testar o fator de balanceamento
  Node *root = AVL::createNode("banana", 1);
  root->left = AVL::createNode("abacaxi", 2);
  root->right = AVL::createNode("morango", 3);

  bool success = true;

  // Calcula o fator de balanceamento
  int balanceFactor = AVL::getBalanceFactor(root);

  // Verifica se o fator de balanceamento está correto
  if (balanceFactor == 0) {
    std::cout << "SUCESSO: Fator de balanceamento calculado corretamente"
              << std::endl;
  } else {
    std::cout << "FALHA: Problema no calculo do fator de balanceamento"
              << std::endl;
    success = false;
  }

  // Libera memória
  delete root->left;
  delete root->right;
  delete root;
  std::cout << std::endl;

  return success;
}

bool testInsertAndBalance() {
  std::cout << "=== Teste AVL::insert() e balanceamento ===" << std::endl;
  BinaryTree *tree = AVL::create();

  // Muitas inserções para verificar o balanceamento no print
  AVL::insert(tree, "banana", 1);
  AVL::insert(tree, "morango", 2);
  AVL::insert(tree, "morango", 3);
  AVL::insert(tree, "cereja", 3);
  AVL::insert(tree, "abacaxi", 4);
  AVL::insert(tree, "uva", 5);
  AVL::insert(tree, "laranja", 6);
  AVL::insert(tree, "manga", 7);
  AVL::insert(tree, "kiwi", 8);
  AVL::insert(tree, "pera", 9);
  AVL::insert(tree, "ameixa", 10);
  AVL::insert(tree, "figo", 11);
  AVL::insert(tree, "goiaba", 12);
  AVL::insert(tree, "limao", 13);
  AVL::insert(tree, "melancia", 14);
  AVL::insert(tree, "pessego", 15);
  AVL::insert(tree, "tangerina", 16);

  std::vector<std::string> words;
  stats::collect_words(tree->root, words, nullptr);

  std::cout << "Estrutura da arvore AVL apos insercoes:\n";
  printTree(tree);
  std::cout << "Altura da Arvore AVL: " << tree->root->height << std::endl;
  std::cout << "Numero de nodes: " << words.size() << std::endl;

  std::cout << std::endl;

  bool success = true;
  Node *root = tree->root;

  // Verifica se todos os nós estão balanceados
  if (!stats::all_balanced(root, nullptr)) {
    std::cout << "FALHA: Arvore AVL nao esta balanceada" << std::endl;
    success = false;
  }

  // Printa caso a árvore esteja balanceada
  if (success) {
    std::cout << "SUCESSO: Arvore AVL balanceada corretamente apos insercoes"
              << std::endl;
  }

  AVL::destroy(tree);
  std::cout << std::endl;

  return success;
}

bool testSearch() {
  std::cout << "=== Teste AVL::search() ===" << std::endl;
  BinaryTree *tree = AVL::create();

  // Inserções para testar busca
  AVL::insert(tree, "banana", 1);
  AVL::insert(tree, "morango", 2);
  AVL::insert(tree, "abacaxi", 3);

  // Buscas
  SearchResult result1 = AVL::search(tree, "banana");
  SearchResult result2 = AVL::search(tree, "morango");
  SearchResult result3 = AVL::search(tree, "abacaxi");
  SearchResult result4 = AVL::search(tree, "nao_existe");

  bool success = true;

  // Verificações dos resultados
  if (result1.found != 1 || result1.documentIds.size() != 1 ||
      result1.documentIds[0] != 1) {
    std::cout << "FALHA: Problema ao buscar 'banana'" << std::endl;
    success = false;
  }
  if (result2.found != 1 || result2.documentIds.size() != 1 ||
      result2.documentIds[0] != 2) {
    std::cout << "FALHA: Problema ao buscar 'morango'" << std::endl;
    success = false;
  }
  if (result3.found != 1 || result3.documentIds.size() != 1 ||
      result3.documentIds[0] != 3) {
    std::cout << "FALHA: Problema ao buscar 'abacaxi'" << std::endl;
    success = false;
  }
  if (result4.found != 0 || !result4.documentIds.empty()) {
    std::cout << "FALHA: Problema ao buscar palavra inexistente" << std::endl;
    success = false;
  }

  // Informa sucesso caso todas as buscas tenham retornado resultados esperados
  if (success) {
    std::cout << "SUCESSO: Todas as buscas retornaram resultados esperados"
              << std::endl;
  }

  AVL::destroy(tree);
  std::cout << std::endl;

  return success;
}

void testDestroyTree() {
  std::cout << "=== Teste AVL::destroy() ===" << std::endl;
  BinaryTree *tree = AVL::create();

  AVL::insert(tree, "banana", 1);
  AVL::insert(tree, "morango", 2);
  AVL::insert(tree, "abacaxi", 3);

  AVL::destroy(tree);
  tree = nullptr;

  // Informar que a árvore foi destruída corretamente
  std::cout << "SUCESSO: Arvore AVL destruida corretamente" << std::endl;
  std::cout << std::endl;
}

int main() {
  std::cout << "INICIANDO TESTES UNITARIOS PARA AVL\n" << std::endl;

  bool success = true;

  // Chama as funções de teste
  success &= testCreateTree();
  success &= testCreateNode();
  success &= testRotateLeft();
  success &= testRotateRight();
  success &= testBalanceFactor();
  success &= testInsertAndBalance();
  success &= testSearch();
  testDestroyTree();

  std::cout << "=== TESTES CONCLUIDOS ===" << std::endl;
  if (success) {
    std::cout << "Todos os testes passaram com sucesso!" << std::endl;
  } else {
    std::cout << "Alguns testes falharam." << std::endl;
  }
  return 0;
}
