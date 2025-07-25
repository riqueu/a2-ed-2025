#include "bst.h"
#include "tree_utils.h"
#include <iostream>
#include <string>
#include <vector>

int testPrintTree() {
  // Cria arvore teste
  BinaryTree *tree = BST::create();

  // Inserindo palavras com diferentes documentIds
  BST::insert(tree, "banana", 1);
  BST::insert(tree, "morango", 2);
  BST::insert(tree, "cereja", 3);
  BST::insert(tree, "banana", 4);
  BST::insert(tree, "abobora", 5);
  /* morango várias vezes de mesmo documentId
  (para testar se o mesmo documentId é adicionado apenas uma vez)
  (no código geral, essa filtragem é feita pelo leitor dos dados
  mas a função BST::insert também deve lidar com isso, apesar de
  ser mais custoso em termos de performance) */
  BST::insert(tree, "morango", 6);
  BST::insert(tree, "morango", 6);
  BST::insert(tree, "morango", 6);
  BST::insert(tree, "morango", 6);
  BST::insert(tree, "morango", 7);
  BST::insert(tree, "morango", 8);
  BST::insert(tree, "abobora", 8);

  // Testa funcao printTree
  std::cout << "=== Teste printTree ===" << std::endl;
  std::cout << "Arvore:\n";
  printTree(tree);
  std::cout << std::endl;

  // Testa funcao printindex
  std::cout << "=== Teste printIndex ===" << std::endl;
  std::cout << "Indices:\n";
  printIndex(tree);
  std::cout << std::endl;

  // Libera memoria
  BST::destroy(tree);
  return 0;
}

bool testCreateTree() {
  // Cria arvore teste
  std::cout << "=== Teste BST::create() ===" << std::endl;
  BinaryTree *tree = BST::create();

  bool success = true;

  // Verifica se a arvore foi criada corretamente
  if (tree != nullptr && tree->root == nullptr) {
    std::cout << "SUCESSO: Arvore criada corretamente" << std::endl;
  } else {
    std::cout << "FALHA: Problema ao criar arvore" << std::endl;
    success = false;
  }

  // Libera memoria
  BST::destroy(tree);
  std::cout << std::endl;

  return success;
}

bool testCreateNode() {
  // Inicia atributos do node
  std::cout << "=== Teste BST::createNode() ===" << std::endl;
  std::string word = "morango";
  int docId = 1;

  bool success = true;

  // Cria node teste
  Node *node = BST::createNode(word, docId);

  // Testa se o node foi iniciado corretamente
  if (node != nullptr && node->word == word && node->documentIds.size() == 1 &&
      node->documentIds[0] == docId && node->parent == nullptr &&
      node->left == nullptr && node->right == nullptr) {
    std::cout << "SUCESSO: Node criado corretamente" << std::endl;
  } else {
    std::cout << "FALHA: Problema ao criar node" << std::endl;
    success = false;
  }

  // Libera memoria
  delete node;
  std::cout << std::endl;

  return success;
}

bool testInsertAndSearch() {
  // Cria arvore teste
  std::cout << "=== Teste BST::insert() e BST::search() ===" << std::endl;
  BinaryTree *tree = BST::create();

  // Inserções
  BST::insert(tree, "banana", 1);
  BST::insert(tree, "morango", 2);
  BST::insert(tree, "abacaxi", 3);
  BST::insert(tree, "banana", 4);

  // Buscas
  SearchResult result1 = BST::search(tree, "banana");
  SearchResult result2 = BST::search(tree, "morango");
  SearchResult result3 = BST::search(tree, "abacaxi");
  SearchResult result4 = BST::search(tree, "nao_existe");

  // Verificações
  bool success = true;

  // Confere para "banana"
  if (result1.found != 1 || result1.documentIds.size() != 2 ||
      result1.documentIds[0] != 1 || result1.documentIds[1] != 4) {
    std::cout << "FALHA: Problema ao buscar 'banana'" << std::endl;
    success = false;
  }
  // Confere para "morango"
  if (result2.found != 1 || result2.documentIds.size() != 1 ||
      result2.documentIds[0] != 2) {
    std::cout << "FALHA: Problema ao buscar 'morango'" << std::endl;
    success = false;
  }
  // Confere para "abacaxi"
  if (result3.found != 1 || result3.documentIds.size() != 1 ||
      result3.documentIds[0] != 3) {
    std::cout << "FALHA: Problema ao buscar 'abacaxi'" << std::endl;
    success = false;
  }
  // Confere para "nao_existe"
  if (result4.found != 0 || !result4.documentIds.empty()) {
    std::cout << "FALHA: Problema ao buscar palavra inexistente" << std::endl;
    success = false;
  }

  if (success) {
    std::cout << "SUCESSO: Todas as buscas retornaram resultados esperados"
              << std::endl;
  }

  // Libera memoria
  BST::destroy(tree);
  std::cout << std::endl;

  return success;
}

bool testInsertNode() {
  std::cout << "=== Teste BST::insertNode() ===" << std::endl;
  BinaryTree *tree = BST::create();
  int comparisons = 0;

  // Inserções
  tree->root = BST::insertNode(tree->root, "banana", 1, comparisons);
  tree->root = BST::insertNode(tree->root, "abacaxi", 2, comparisons);
  tree->root = BST::insertNode(tree->root, "morango", 3, comparisons);
  tree->root = BST::insertNode(tree->root, "banana", 4, comparisons);

  // Verificações
  bool success = true;

  if (tree->root == nullptr) {
    std::cout << "FALHA: Raiz nao foi criada" << std::endl;
    success = false;
  }
  // Confere para "banana"
  if (tree->root->word != "banana") {
    std::cout << "FALHA: Raiz incorreta" << std::endl;
    success = false;
  }
  // Confere para "abacaxi"
  if (tree->root->left == nullptr || tree->root->left->word != "abacaxi") {
    std::cout << "FALHA: Node esquerdo incorreto" << std::endl;
    success = false;
  }
  // Confere para "morango"
  if (tree->root->right == nullptr || tree->root->right->word != "morango") {
    std::cout << "FALHA: Node direito incorreto" << std::endl;
    success = false;
  }
  // Confere documentIds para "banana"
  if (tree->root->documentIds.size() != 2 ||
      tree->root->documentIds[0] != 1 ||
      tree->root->documentIds[1] != 4) {
   std::cout << "FALHA: DocumentIds duplicados nao foram adicionados "
                 "corretamente para 'banana'"
              << std::endl;
    success = false;
  }

  // Testa inserção de múltiplos documentIds duplicados
  tree->root = BST::insertNode(tree->root, "banana", 42, comparisons);
  tree->root = BST::insertNode(tree->root, "banana", 99, comparisons);

  if (tree->root->documentIds.size() != 4 || tree->root->documentIds[2] != 42 ||
      tree->root->documentIds[3] != 99) {
    std::cout << "FALHA: DocumentIds adicionais não foram inseridos "
                 "corretamente para 'banana'"
              << std::endl;
    success = false;
  }

  if (success) {
    std::cout << "SUCESSO: Nodes inseridos corretamente, incluindo palavras "
                 "duplicadas com todos os documentIds"
              << std::endl;
  }
  // Libera memoria
  BST::destroy(tree);
  std::cout << std::endl;

  return success;
}

void testDestroyTree() {
  std::cout << "=== Teste BST::destroy() ===" << std::endl;
  BinaryTree *tree = BST::create();

  // Inserir alguns dados
  BST::insert(tree, "banana", 1);
  BST::insert(tree, "morango", 2);
  BST::insert(tree, "abacaxi", 3);

  // Destruir a árvore
  BST::destroy(tree);
  tree = nullptr; // Garantir que o ponteiro não seja usado após a destruição

  // Informar que a árvore foi destruída corretamente
  std::cout << "SUCESSO: Arvore destruida corretamente" << std::endl;
  std::cout << std::endl;
}

int main() {
  std::cout << "INICIANDO TESTES UNITARIOS PARA BST\n" << std::endl;

  bool success = true;

  success &= testCreateTree();
  success &= testCreateNode();
  success &= testInsertNode();
  testPrintTree();
  success &= testInsertAndSearch();
  testDestroyTree();

  std::cout << "=== TESTES CONCLUIDOS ===" << std::endl;
  if (success) {
    std::cout << "Todos os testes passaram com sucesso!" << std::endl;
  } else {
    std::cout << "Alguns testes falharam." << std::endl;
  }
  return 0;
}
