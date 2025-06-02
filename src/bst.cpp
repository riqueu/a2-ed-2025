#include "bst.h"
#include <iostream>

namespace BST {
    BinaryTree* create(){
        // Criação da árvore
        BinaryTree * NewBinaryTree = new BinaryTree;
        NewBinaryTree->root = nullptr;
        return NewBinaryTree;
    }

    Node* createNode(const std::string& word, int documentId){
        // Criação e definições iniciais de um nó
        Node * NewNode = new Node;
        NewNode->word = word;
        NewNode->documentIds.push_back(documentId);
        NewNode->parent = nullptr;
        NewNode->left = nullptr;
        NewNode->right = nullptr;
        NewNode->height = 0;

        return NewNode;
    }

    Node* InsertNode(Node* root, const std::string& word, int documentId){
        // Caso ainda não haja um nó com a palavra
        if (root == nullptr){
            return createNode(word, documentId);
        }

        // Caso onde se encontra o nó com a palavra
        if (root->word == word){
            root->documentIds.push_back(documentId);
        } else if (root->word > word){ // Caso onde a palavra a ser inserida esta a esquerda do nó atual
            Node * left = InsertNode(root->left, word, documentId);
            root->left = left;
            left->parent = root;
        } else { // Caso análogo, só que para a direita
            Node * right = InsertNode(root->right, word, documentId);
            root->right = right;
            right->parent = root;
        }

        return root;
    }

    void insert(BinaryTree* tree, const std::string& word, int documentId){
        if (tree == nullptr){return;}

        // Chama a função recursiva, e caso o root da árvore tenha mudado atualiza na estrutura
        tree->root = InsertNode(tree->root, word, documentId);
        return;
    }

    void deleteNodes(Node* root){
        if (root == nullptr){return;}

        // Recurção para deletar os nós, não tem necessidade de verificar se são nullptr, pois a recurção já faz isso
        deleteNodes(root->left);
        deleteNodes(root->right);

        delete root;
        return;
    }

    void destroy(BinaryTree* tree){
        if (tree==nullptr){return;}

        // Deleta todos os nós da árvore recursivamente
        deleteNodes(tree->root);

        delete tree;
        return;
    }
}
