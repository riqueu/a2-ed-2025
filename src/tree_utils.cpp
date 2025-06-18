#include "tree_utils.h"
#include "avl.h"
#include <cstddef>
#include "bst.h"
#include "rbt.h"
#include "data.h"
#include <algorithm>
#include <iostream>

void printIndexRec(Node *node, Node *NIL = nullptr) {
  if (node == nullptr || node == NIL) {
    return;
  }
  // Recursão para os nós à esquerda
  printIndexRec(node->left, NIL);

  // Exibe a palavra e os IDs dos documentos em que ela aparece
  std::cout << node->word << ": ";
  int size = node->documentIds.size();
  if (size > 0) {
    for (int i = 0; i < size - 1; i++) {
      std::cout << node->documentIds[i] << ", ";
    }
    std::cout << node->documentIds[size - 1];
    std::cout << "\n";
  }

  // Recursão para os nós à direita
  printIndexRec(node->right, NIL);
}

void printIndex(BinaryTree *tree) {
  if (tree == nullptr || tree->root == nullptr) {
    return;
  }

  // Chamada da função recursiva
  printIndexRec(tree->root, tree->NIL);
}

void printTreeRec(Node* node, Node* NIL = nullptr, 
                  const std::string& prefix = "", bool left = false) {
    if (node == nullptr ||  node == NIL) {
        return;
    }

    // imprime o nó atual
    std::cout << prefix;
    std::cout << (left ? "├── " : "└── ");
    std::cout << node->word << std::endl;

    // calcula o novo prefix
    std::string newPrefix;
    if (left) {
        newPrefix = prefix + "│   ";
    } else {
        newPrefix = prefix + "    ";
    }

    // recursão para os filhos
    printTreeRec(node->left, NIL, newPrefix, true);
    printTreeRec(node->right, NIL, newPrefix, false);
}


void printTree(BinaryTree *tree) {
  if (tree == nullptr || tree->root == nullptr) {
    return;
  }

  // Chamada da função recursiva
  printTreeRec(tree->root, tree->NIL);
}

namespace stats {
int get_tree_height(Node *node, Node *NIL = nullptr) {
  if (node == nullptr || node == NIL) {
    return -1; // A altura de uma árvore vazia é -1
  }

  // Calcula a altura das subárvores esquerda e direita
  int leftHeight = get_tree_height(node->left, NIL);
  int rightHeight = get_tree_height(node->right, NIL);

  // A altura da árvore é o máximo entre as alturas das subárvores + 1
  return std::max(leftHeight, rightHeight) + 1;
}

void get_min_branch(Node *node, int currentLen, int *minBranch, 
                    Node *NIL = nullptr) {
  // Verifica se o node atual é inválido (nullptr ou NIL)
  if (node == nullptr || node == NIL) {
    return;
  }

  if ((node->left == nullptr || node->left == NIL) && 
      (node->right == nullptr || node->right == NIL)) {
    *minBranch = std::min(currentLen, *minBranch);
    return;
  }

  // Recursão para os filhos
  get_min_branch(node->left, currentLen + 1, minBranch, NIL);
  get_min_branch(node->right, currentLen + 1, minBranch, NIL);
}

void collect_words(Node *node, std::vector<std::string> &words, Node *NIL = nullptr) {
  if (node == nullptr || node == NIL) {
    return;
  }

  // Recursão para os nós à esquerda
  collect_words(node->left, words, NIL);
  // Adiciona a palavra do nó atual à lista
  words.push_back(node->word);
  // Recursão para os nós à direita
  collect_words(node->right, words, NIL);
}

void most_frequent_words(Node* node,
                              std::vector<Node*>& mostFrequentNodes,
                              std::vector<int>& maxCounts,
                              Node* NIL = nullptr) {
  if (node == nullptr || node == NIL) {
    return;
  }

  // Visita esquerda
  most_frequent_words(node->left, mostFrequentNodes, maxCounts, NIL);

  // Verifica a palavra atual
  int length = node->word.size();
  int count = node->documentIds.size();

  if (length >= 1 && length <= 15) {
    int index = length - 1; // índice entre 0 e 14

    if (count > maxCounts[index]) {
      maxCounts[index] = count;
      mostFrequentNodes[index] = node;
    }
  }

  // Visita direita
  most_frequent_words(node->right, mostFrequentNodes, maxCounts, NIL);
}



// calcula tamanho de memória ocupada pela árvore:
size_t get_tree_size(Node* node, Node* NIL = nullptr) {
    if (node == nullptr || node == NIL) {
        return 0;
    }
    // soma os dados da estrutura do nó
    size_t size = sizeof(Node);

    // soma a memória alocada dinamicamente
    size += node->word.capacity() * sizeof(char);
    size += node->documentIds.capacity() * sizeof(int);

    // recursão
    size += get_tree_size(node->right, NIL);
    size += get_tree_size(node->left, NIL);

    // retorna o valor em bytes
    return size;
}

TreeStats get_tree_stats(const std::string &tree_type, int n_docs, int n_max_doc,
                         const std::vector<DocReading::Doc *> &docs) {
  BinaryTree *tree = nullptr;
  TreeStats s = {n_docs, 0,   0,   0.0, 0.0, 0,
                 0,      0, 0, 0,   0,   0, 0, {}}; // Inicializa as estatísticas

  if (tree_type == "bst") {
    tree = BST::create();
  } else if (tree_type == "avl") {
    tree = AVL::create();
  } else if (tree_type == "rbt") {
    tree = RBT::create();
  } else {
    return s; // Retorna estatísticas vazias se o tipo de árvore não for válido
  }

  int numInsertion = 0;

  // Insere palavras dos documentos na árvore
  for (int i = 0; i < n_docs && i < n_max_doc; i++) {
    for (size_t j = 0; j < docs[i]->content->size(); j++) {
      InsertResult result;
      if (tree_type == "bst") {
        result = BST::insert(tree, docs[i]->content->at(j), docs[i]->docID);
      } else if (tree_type == "avl") {
        result = AVL::insert(tree, docs[i]->content->at(j), docs[i]->docID);
      } else {
        result = RBT::insert(tree, docs[i]->content->at(j), docs[i]->docID);
      }
      s.numComparisonsInsertion += result.numComparisons;
      s.executionTimeInsertion += result.executionTime;
      numInsertion += 1;
    }
  }

  // Calcula o tempo médio de inserção
  s.executionTimeInsertionMean = s.executionTimeInsertion / numInsertion; 
  // Calcula o número médio de comparações de inserção
  s.numComparisonsInsertionMean = s.numComparisonsInsertion / numInsertion; 

  // Pega as palavras inseridas na árvore
  std::vector<std::string> search_words;
  // Coleta as palavras
  collect_words(tree->root, search_words, tree->NIL); 

  // Armazena o número de nós na árvore
  s.numNodes = search_words.size();

  // Busca cada palavra do vetor search_words na árvore
  for (const std::string &word : search_words) {
    SearchResult search; // Inicializa a estrutura de busca

    int j = 0; // Contador de tentativas
    int j_max = (n_docs < 800) ? 50 : 1; 
    // Se o número de documentos for menor que 800, repete
    // a busca 50 vezes, caso contrário, apenas uma vez
    int totalComparisons = 0;
    double totalTime = 0.0;

    // Realiza a busca na árvore, repetindo até 50 vezes para cada palavra com
    // menos 800 documentos
    for (int i = 0; i < j_max; ++i) {
      // Realiza a busca na árvore, dependendo do tipo de árvore
      if (tree_type == "bst") {
        search = BST::search(tree, word);
      } else if (tree_type == "avl") {
        search = AVL::search(tree, word);
      } else if (tree_type == "rbt") {
        search = RBT::search(tree, word);
      } else {
        return s; // Retorna estatísticas vazias se o tipo de árvore não for
                  // válido
      }
      totalComparisons += search.numComparisons;
      totalTime += search.executionTime;
      j++;
    }

    // Calcula o número médio de comparações
    search.numComparisons = totalComparisons / j; 
    // Calcula o tempo médio de execução
    search.executionTime = totalTime / j; 

    // Atualiza as estatísticas de busca
    s.numComparisonsSearchMean += search.numComparisons;
    s.executionTimeSearchMean += search.executionTime;
    // Atualiza o número máximo de comparações
    if (search.numComparisons > s.numComparisonsSearchMax) {
      s.numComparisonsSearchMax = search.numComparisons;
    }
    if (search.executionTime > s.executionTimeSearchMax) {
      s.executionTimeSearchMax = search.executionTime;
    }
  }
  // Calcula o número médio de comparações e o tempo médio de busca
  s.numComparisonsSearchMean /= search_words.size();
  s.executionTimeSearchMean /= search_words.size();

  size_t size_bytes = get_tree_size(tree->root, tree->NIL);
  s.size = size_bytes;

  // Pega a altura da árvore
  if (tree_type == "avl") {
    s.treeHeight = tree->root->height; // Armazena a altura da árvore AVL
  } else {
    // Para as outras, calcula a altura usando a função auxiliar
    s.treeHeight = get_tree_height(tree->root, tree->NIL);
  }

  // Inicializa o comprimento do menor galho como a altura da arvore + 1
  int minBranch = s.treeHeight + 1;

  // Calcula o comprimento do menor galho e coloca na estrutura
  get_min_branch(tree->root, 0, &minBranch, tree->NIL);
  s.minBranch = minBranch;

  std::vector<Node*> mostFrequentNodes(15, nullptr);
  std::vector<int> maxCounts(15, -1);  

  if (tree_type == "rbt") {
      most_frequent_words(tree->root, mostFrequentNodes, maxCounts, tree->NIL);
  } else {
      most_frequent_words(tree->root, mostFrequentNodes, maxCounts, nullptr);
  }

  for (int i = 0; i < 15; ++i) {
    if (mostFrequentNodes[i]) {
      s.mostFrequentNodes.push_back(*mostFrequentNodes[i]);
    } else {
      s.mostFrequentNodes.push_back(Node()); // node vazio
    }
  }

  // Libera a memória da árvore atual
  if (tree_type == "bst") {
    BST::destroy(tree);
  } else if (tree_type == "avl") {
    AVL::destroy(tree);
  } else if (tree_type == "rbt") {
    RBT::destroy(tree);
  }

  return s;
}

bool all_balanced(Node *root, Node *NIL = nullptr) {
  if (root == nullptr || root == NIL) {
    return true;
  }

  int leftHeight = get_tree_height(root->left, NIL);
  int rightHeight = get_tree_height(root->right, NIL);
  int balanceFactor = leftHeight - rightHeight;

  // Verifica se o fator de balanceamento está entre -1 e 1
  if (balanceFactor < -1 || balanceFactor > 1) {
    return false;
  }

  // Verifica recursivamente as subárvores esquerda e direita
  return all_balanced(root->left, NIL) && all_balanced(root->right, NIL);
}
} // namespace stats
