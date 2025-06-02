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
1. **Compilar todos os executáveis**:
   Execute o comando abaixo para compilar os programas para todas as árvores (BST, AVL, e RBT):
   ```bash
   make
   ```
2. **Compilar apenas uma árvore específica:**
    Para compilar apenas o programa de uma árvore específica, use:
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
    Após a compilação, você pode executar o programa correspondente a cada árvore:
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
    4. **Limpar arquivos gerados:** Para remover os executáveis e limpar o diretório de saída, execute:
    ```
    make clean
    ```

5. **Exemplo de execução:** Para buscar palavras em 10 documentos localizados no diretório `data/` usando a árvore BST:
    ```bash
    ./src/output/main_bst search 10 data/
    ```

---
