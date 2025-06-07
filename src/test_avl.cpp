#include "avl.h"
#include "tree_utils.h"
#include <iostream>
#include <string>
#include <vector>

void testCreateTree() {
  std::cout << "=== Teste AVL::create() ===" << std::endl;
  BinaryTree *tree = AVL::create();

  // Verifica se a árvore foi criada corretamente
  if (tree != nullptr && tree->root == nullptr) {
    std::cout << "SUCESSO: Árvore AVL criada corretamente" << std::endl;
  } else {
    std::cout << "FALHA: Problema ao criar árvore AVL" << std::endl;
  }

  AVL::destroy(tree);
  std::cout << std::endl;
}

void testCreateNode() {
  // Inicia atributos do node
  std::cout << "=== Teste AVL::createNode() ===" << std::endl;
  std::string word = "morango";
  int docId = 1;

  Node *node = AVL::createNode(word, docId);

  // Verifica se o nó foi criado corretamente
  if (node != nullptr && node->word == word && node->documentIds.size() == 1 &&
      node->documentIds[0] == docId && node->parent == nullptr &&
      node->left == nullptr && node->right == nullptr && node->height == 0) {
    std::cout << "SUCESSO: Nó AVL criado corretamente" << std::endl;
  } else {
    std::cout << "FALHA: Problema ao criar nó AVL" << std::endl;
  }

  delete node;
  std::cout << std::endl;
}

void testInsertAndBalance() {
  std::cout << "=== Teste AVL::insert() e balanceamento ===" << std::endl;
  BinaryTree *tree = AVL::create();

  // Muitas inserções para verificar o balanceamento no print
  AVL::insert(tree, "banana", 1);
  AVL::insert(tree, "morango", 2);
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
  AVL::insert(tree, "limão", 13);
  AVL::insert(tree, "melancia", 14);
  AVL::insert(tree, "pêssego", 15);

  std::cout << "Estrutura da árvore AVL após inserções:\n";
  printTree(tree);

  bool success = true;
  Node *root = tree->root;
  // Verifica se a árvore está balanceada (|fator de balanceamento| <= 1)
  if (root == nullptr || std::abs(AVL::getBalanceFactor(root)) > 1) {
    std::cout << "FALHA: Árvore AVL não está balanceada" << std::endl;
    success = false;
  }

  // Printa caso a árvore esteja balanceada
  if (success) {
    std::cout << "SUCESSO: Árvore AVL balanceada corretamente após inserções"
              << std::endl;
  }

  AVL::destroy(tree);
  std::cout << std::endl;
}

void testSearch() {
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
  std::cout << "SUCESSO: Árvore AVL destruída corretamente" << std::endl;
}

int main() {
  std::cout << "INICIANDO TESTES UNITÁRIOS PARA AVL\n" << std::endl;

  // Chama as funções de teste
  testCreateTree();
  testCreateNode();
  testInsertAndBalance();
  testSearch();
  testDestroyTree();

  std::cout << "TESTES CONCLUÍDOS" << std::endl;
  return 0;
}
