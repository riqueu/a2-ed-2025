# Projeto: Índice Invertido e Análise Comparativa de Estruturas de Dados  

Este repositório é um refúgio para o projeto final da disciplina de Estrutura de Dados do 3º período da graduação de Ciências de Dados e Inteligência Artificial da FGV EMAp

* **Alunos integrantes**: Bruno Ferreira Salvi, Henrique Coelho Beltrão, Henrique Gabriel Gasparelo, José Thevez Gomes Guedes e Luiz Eduardo Bravin.
* **Professor orientador**: Matheus Telles Werner.

---
### Resumo
-> resumo do trabalho aqui

---
### Relatório
Leia também o [Relatório Completo](docs/relatorio.md).

---
### Instruções para Execução

- Use C++17 ou uma versão superior

#### Linux/UNIX-like

1. **Compilar todos os executáveis:**
    ```bash
    make
    ```
2. **Alternativa: Compilar apenas uma árvore específica:**
     - Binary Search Tree (BST)
          ```bash
          make src/output/main_bst
          ```
     - AVL Tree
          ```bash
          make src/output/main_avl
          ```
     - Red-Black Tree (RBT)
          ```bash
          make src/output/main_rbt
          ```
3. **Executar o programa para uma árvore específica:**
     - Binary Search Tree (BST)
          ```bash
          ./src/output/main_bst <comando> <n_docs> <diretório>
          ```
     - AVL Tree
          ```bash
          ./src/output/main_avl <comando> <n_docs> <diretório>
          ```
     - Red-Black Tree (RBT)
          ```bash
          ./src/output/main_rbt <comando> <n_docs> <diretório>
          ```
4. **Limpar arquivos gerados:**
     ```bash
     make clean
     ```
5. **Exemplo de execução:**
     ```bash
     ./src/output/main_bst search 10 data/
     ```

---

#### Windows

1. **Compilar todos os executáveis:**
    ```cmd
    make
    ```
2. **Alternativa: Compilar apenas uma árvore específica:**
     - Binary Search Tree (BST)
          ```cmd
          make src/output/main_bst.exe
          ```
     - AVL Tree
          ```cmd
          make src/output/main_avl.exe
          ```
     - Red-Black Tree (RBT)
          ```cmd
          make src/output/main_rbt.exe
          ```
3. **Executar o programa para uma árvore específica:**
     - Binary Search Tree (BST)
          ```cmd
          src\output\main_bst.exe <comando> <n_docs> <diretório>
          ```
     - AVL Tree
          ```cmd
          src\output\main_avl.exe <comando> <n_docs> <diretório>
          ```
     - Red-Black Tree (RBT)
          ```cmd
          src\output\main_rbt.exe <comando> <n_docs> <diretório>
          ```
4. **Limpar arquivos gerados:**
     ```cmd
     make clean
     ```
5. **Exemplo de execução:**
     ```cmd
     src\output\main_bst.exe search 10 data\
     ```

---
