#include "rbt.h"
#include "tree_utils.h"
#include <iostream>
#include <string>
#include <vector>

int testPrintTree() {
  // Cria arvore teste
  BinaryTree *tree = RBT::create();

  // Inserindo palavras com diferentes documentIds
  RBT::insert(tree, "banana", 1);
  RBT::insert(tree, "morango", 2);
  RBT::insert(tree, "cereja", 3);
  RBT::insert(tree, "banana", 4);
  RBT::insert(tree, "abobora", 5);
  RBT::insert(tree, "morango", 6);

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
  RBT::destroy(tree);
  return 0;
}

void testCreateTree() {
  // Cria arvore teste
  std::cout << "=== Teste RBT::create() ===" << std::endl;
  BinaryTree *tree = RBT::create();

  // Verifica se a arvore foi criada corretamente
  if (tree != nullptr && tree->root == nullptr) {
    std::cout << "SUCESSO: Arvore criada corretamente" << std::endl;
  } else {
    std::cout << "FALHA: Problema ao criar arvore" << std::endl;
  }

  // Libera memoria
  RBT::destroy(tree);
  std::cout << std::endl;
}

void testCreateNode() {
  // Inicia atributos do node
  std::cout << "=== Teste RBT::createNode() ===" << std::endl;
  std::string word = "morango";
  int docId = 1;

  // Cria node teste
  BinaryTree *tree = RBT::create();
  Node *node = RBT::createNode(word, docId, tree->NIL);

  // Testa se o node foi iniciado corretamente
  if (node != nullptr && node->word == word && node->documentIds.size() == 1 &&
      node->documentIds[0] == docId && node->parent == nullptr &&
      node->left == tree->NIL && node->right == tree->NIL && node->isRed == true) {
    std::cout << "SUCESSO: Node criado corretamente" << std::endl;
  } else {
    std::cout << "FALHA: Problema ao criar node" << std::endl;
  }

  // Libera memoria
  delete node;
  std::cout << std::endl;
}

void testSearch() {
  // Cria arvore teste
  std::cout << "=== Teste RBT::search() ===" << std::endl;
  BinaryTree *tree = RBT::create();

  // Inserções
  RBT::insert(tree, "banana", 1);
  RBT::insert(tree, "morango", 2);
  RBT::insert(tree, "abacaxi", 3);
  RBT::insert(tree, "banana", 4);

  // Buscas
  SearchResult result1 = RBT::search(tree, "banana");
  SearchResult result2 = RBT::search(tree, "morango");
  SearchResult result3 = RBT::search(tree, "abacaxi");
  SearchResult result4 = RBT::search(tree, "nao_existe");

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
  RBT::destroy(tree);
  std::cout << std::endl;
}

void testInsertNode() {
  std::cout << "=== Teste RBT::insertNode() ===" << std::endl;
  BinaryTree *tree = RBT::create();
  int comparisons = 0;

  // Inserções
  RBT::insertNode(tree->root, tree, "damasco", 1, comparisons);
  RBT::insertNode(tree->root, tree, "damasco", 4, comparisons);
  RBT::insertNode(tree->root, tree, "cereja", 2, comparisons);
  RBT::insertNode(tree->root, tree, "kiwi", 3, comparisons);

  // Caso 1: Tio vermelho (recoloração)
  RBT::insertNode(tree->root, tree, "abobora", 4, comparisons);

  // Caso 2: Tio preto, z é filho à direita (rotação à esquerda)
  RBT::insertNode(tree->root, tree, "banana", 4, comparisons);

  RBT::insertNode(tree->root, tree, "jaca", 4, comparisons);

  // Caso 3: Tio preto, z é filho à esquerda (rotação à direita)
  RBT::insertNode(tree->root, tree, "goiaba", 4, comparisons);

  // Verificações
  bool success = true;

  if (tree->root == nullptr) {
    std::cout << "FALHA: Raiz nao foi criada" << std::endl;
    success = false;
  }
  // Confere para "damasco"
  if (tree->root->word != "damasco") {
    std::cout << "FALHA: Raiz incorreta" << std::endl;
    success = false;
  }
  // Confere para "banana"
  if (tree->root->left->isRed == true || tree->root->left->word != "banana") {
    std::cout << "FALHA: Node banana incorreto" << std::endl;
    success = false;
  }
  // Confere para "jaca"
  if (tree->root->right->isRed == true || tree->root->left->word != "jaca") {
    std::cout << "FALHA: Node jaca incorreto" << std::endl;
    success = false;
  }
  // Confere para "abobora"
  if (tree->root->left->left->isRed == false || tree->root->left->left->word != "abobora") {
    std::cout << "FALHA: Node abobora incorreto" << std::endl;
    success = false;
  }
  // Confere para "cereja"
  if (tree->root->left->right->isRed == false || tree->root->left->right->word != "cereja") {
    std::cout << "FALHA: Node cereja incorreto" << std::endl;
    success = false;
  }
  // Confere para "goiaba"
  if (tree->root->right->left->isRed == false || tree->root->right->left->word != "goiaba") {
    std::cout << "FALHA: Node goiaba incorreto" << std::endl;
    success = false;
  }
  // Confere para "kiwi"
  if (tree->root->right->right->isRed == false || tree->root->right->right->word != "kiwi") {
    std::cout << "FALHA: Node kiwi incorreto" << std::endl;
    success = false;
  }

  // Confere documentIds para "banana"
  if (tree->root->documentIds.size() != 2 ||
      tree->root->documentIds[0] != 1 ||
      tree->root->documentIds[1] != 4) {
    std::cout << "FALHA: DocumentIds duplicados nao foram adicionados corretamente para 'damasco'" << std::endl;
    success = false;
  }

  if (success) {
    std::cout << "SUCESSO: Nodes inseridos corretamente, incluindo palavras duplicadas com todos os documentIds" << std::endl;
  }
  // Libera memoria
  RBT::destroy(tree);
  std::cout << std::endl;
}

bool colorCheck(Node *node, BinaryTree *tree) {
  // Verifica se o nó é o NIL (nó sentinela)
  if (node == tree->NIL) {
    return true;
  }

  // Verifica se o nó vermelho tem filhos vermelhos
  if (node->isRed) {
    if (node->left->isRed || node->right->isRed) {
      std::cout << "FALHA: Dois vermelhos em sequencia encontrados" << std::endl;
      return false;
    }
  }
  
  // Verifica os filhos recursivamente
  return colorCheck(node->left, tree) && colorCheck(node->right, tree);
}

bool checkBlackHeight(Node *node, BinaryTree *tree, int &blackHeight) {
  // Verifica se o nó é o NIL
  if (node == tree->NIL) {
    blackHeight++;
    return true;
  }

  // Se o nó é vermelho, não incrementa a altura preta
  if (!node->isRed) {
    blackHeight++;
  }

  // Verifica os filhos recursivamente
  int leftBlackHeight = 0;
  int rightBlackHeight = 0;
  bool leftCheck = checkBlackHeight(node->left, tree, leftBlackHeight);
  bool rightCheck = checkBlackHeight(node->right, tree, rightBlackHeight);

  // Verifica se as alturas pretas dos filhos são iguais
  if (leftBlackHeight != rightBlackHeight) {
    std::cout << "FALHA: Altura preta diferente nos filhos" << std::endl;
    return false;
  }

  return leftCheck && rightCheck;
}

void testColor() {
  std::cout << "=== Teste RBT::testColor() ===" << std::endl;
  BinaryTree *tree = RBT::create();
  int comparisons = 0;

  // Inserções
  RBT::insertNode(tree->root, tree, "banana", 1, comparisons);   // 3ª (banana)
  RBT::insertNode(tree->root, tree, "abacaxi", 2, comparisons);  // 1ª (abacaxi)
  RBT::insertNode(tree->root, tree, "morango", 3, comparisons);  // 9ª (morango)
  RBT::insertNode(tree->root, tree, "cereja", 4, comparisons);   // 4ª (cereja)
  RBT::insertNode(tree->root, tree, "uva", 5, comparisons);      // 14ª (uva)
  RBT::insertNode(tree->root, tree, "banana", 6, comparisons);   // 3ª (banana, repetida)
  RBT::insertNode(tree->root, tree, "laranja", 7, comparisons);  // 7ª (laranja)
  RBT::insertNode(tree->root, tree, "abacaxi", 8, comparisons);  // 1ª (abacaxi, repetida)
  RBT::insertNode(tree->root, tree, "pera", 9, comparisons);     // 11ª (pera)
  RBT::insertNode(tree->root, tree, "kiwi", 10, comparisons);    // 6ª (kiwi)
  RBT::insertNode(tree->root, tree, "morango", 11, comparisons); // 9ª (morango, repetida)
  RBT::insertNode(tree->root, tree, "cereja", 12, comparisons);  // 4ª (cereja, repetida)
  RBT::insertNode(tree->root, tree, "manga", 13, comparisons);   // 8ª (manga)
  RBT::insertNode(tree->root, tree, "goiaba", 14, comparisons);  // 5ª (goiaba)
  RBT::insertNode(tree->root, tree, "banana", 15, comparisons);  // 3ª (banana, repetida)

  // Verificações
  bool success = true;
  if (tree->root->isRed == true) {
    std::cout << "FALHA: Raiz nao e preta" << std::endl;
    success = false;
  }

  if (tree->NIL->isRed == true) {
    std::cout << "FALHA: NIL nao e preta" << std::endl;
    success = false;
  }

  // Verifica se todos os nós estão com a cor correta
  success = success && colorCheck(tree->root, tree);

  int blackHeight = 0;
  // Verifica se a altura preta é consistente
  success = success && checkBlackHeight(tree->root, tree, blackHeight);

}

void testDestroyTree() {
  std::cout << "=== Teste RBT::destroy() ===" << std::endl;
  BinaryTree *tree = RBT::create();

  // Inserir alguns dados
  RBT::insert(tree, "banana", 1);
  RBT::insert(tree, "morango", 2);
  RBT::insert(tree, "abacaxi", 3);

  // Destruir a árvore
  RBT::destroy(tree);
  tree = nullptr; // Garantir que o ponteiro não seja usado após a destruição

  // Informar que a árvore foi destruída corretamente
  std::cout << "SUCESSO: Arvore destruida corretamente" << std::endl;
}

int main() {
  std::cout << "INICIANDO TESTES UNITARIOS PARA RBT\n" << std::endl;

  testCreateTree();
  testCreateNode();
  testInsertNode();
  testPrintTree();
  testSearch();
  testColor();
  testDestroyTree();

  std::cout << "TESTES CONCLUIDOS" << std::endl;
  return 0;
}
