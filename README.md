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

- Certifique-se de que o compilador **g++** está instalado e configurado no sistema.
- Use **C++17** ou uma versão superior.
- O [Makefile](Makefile) detecta automaticamente o sistema operacional e ajusta os comandos de criação e limpeza de executáveis e diretórios.


#### 1. Compilação:
#### Compilar todos os executáveis (mains e testes)
```sh
# Linux/macOS
make

# Windows (cmd)
make
```

#### Compilar apenas os arquivos principais (mains)
```sh
make run_main
```

#### Compilar apenas os arquivos de teste
```sh
make run_test
```

#### Compilar um arquivo específico (exemplo: main_bst)
```sh
# Linux/macOS
make src/output/main_bst

# Windows (cmd)
make src\output\main_bst.exe
```

#### 2. Execução:
#### Executar um dos programas compilados (exemplo: main_bst)
```sh
# Linux/macOS
./src/output/main_bst <comando> <n_docs> <diretório>

# Windows (cmd)
src\output\main_bst.exe <comando> <n_docs> <diretório>
```

#### 3. Limpeza:
#### Limpar todos os arquivos gerados
```sh
make clean
```

#### 4. Exemplo de Fluxos de compilação e execução:
#### Exemplo de fluxo completo (Linux/macOS)
```sh
make clean
make
# busca com 100 arquivos no diretório data/ com a AVL
./src/output/main_avl search 100 data/
... # execução/output do programa
make clean
```

#### Exemplo de fluxo completo (Windows)
```sh
make clean
make
# stats com 1000 arquivos no diretório data\ com a BST
src\output\main_bst.exe stats 1000 data\
... # execução/output do programa
make clean
```