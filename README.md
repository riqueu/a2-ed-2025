# Projeto: Índice Invertido e Análise Comparativa de Estruturas de Dados  

Este repositório é um refúgio para o projeto final da disciplina de Estrutura de Dados do 3º período da graduação de Ciências de Dados e Inteligência Artificial da FGV EMAp

* **Alunos integrantes**: Bruno Ferreira Salvi, Henrique Coelho Beltrão, Henrique Gabriel Gasparelo, José Thevez Gomes Guedes e Luiz Eduardo Bravin.
* **Professor orientador**: Matheus Telles Werner.

---
### Resumo
Optou-se por remover palavras duplicadas durante a leitura dos documentos, garantindo que cada palavra fosse inserida apenas uma vez na árvore BST por documento. Como resultado, a lista de palavras que serão inseridas na árvore contém apenas palavras únicas por documento.

---
### Relatório
Leia também o [Relatório Completo](docs/relatorio.md).

---
### Instruções para Execução

- Certifique-se de que o compilador **g++** está instalado e configurado no sistema.
- Use **C++17** ou uma versão superior.
- O [Makefile](Makefile) detecta automaticamente o sistema operacional e ajusta os comandos de criação e limpeza de executáveis e diretórios. Como também é capaz de lidar com a descompactação, o passo 0 existe apenas por conveniência.

### Avisos
- O volume de dados é considerável, portanto, o tempo de execução pode ser longo, especialmente para a geração de estatísticas. Por exemplo, para ler e buscar 1000 documentos, a execução pode levar cerca de 40 segundos antes de entrarmos na interface de busca. Isto é, para a leitura de cada documento, o tempo médio é de aproximadamente 40 milissegundos, o que é aceitável para a leitura de arquivos de texto, mas gera longos tempos de leitura para grandes volumes de dados, como é o caso para a leitura de 1000 ou 10000 documentos. Esse tempo de leitura não está relacionado com a construção das diferentes estruturas das árvores, mas sim com o processamento dos arquivos de texto.

#### 0. Descompactação dos dados (Opcional):

Visto o tamanho dos dados, o repositório contém apenas o arquivo compactado `data.zip` com os dados necessários para a execução do projeto.

Este passo é opcional, visto que o nosso [Makefile](Makefile) já faz a descompactação caso o diretório `data/` não exista, que é o caso na primeira execução.

#### Descompacte o arquivo `data.zip` na raiz do projeto.
```sh
# Linux/macOS
unzip -qo data.zip

# Windows
# use o seu descompactador de estimação (7z, winrar, explorer, etc.) e clique em "Extract Here"
# ou
tar -xf data.zip
```


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

#### 3. Geração de Estatísticas (CSV):
#### Geração dos arquivos CSV com as estatísticas para cada árvore
```sh
# Linux/macOS
./src/output/tree_stats <tipoArvore> <n_docs> <n_pontos> <diretório>

# Windows (cmd)
src\output\tree_stats <tipoArvore> <n_docs> <n_pontos> <diretório>
```

#### 4. Geração dos gráficos
#### Instale as bibliotecas Python necessárias:
```sh
pip install matplotlib pandas
```

#### Gere os gráficos a partir desse arquivo:
```sh
# Linux/macOS
python3 docs/visualizations.py

# Windows (cmd)
python docs\visualizations.py
```

#### 5. Limpeza:
#### Limpar todos os arquivos gerados
```sh
make clean
```

#### 6. Exemplo de Fluxos de compilação e execução:
#### Exemplo de fluxo completo (Linux/macOS)
```sh
make clean
make
# busca com 100 arquivos no diretório data/ com a AVL
./src/output/main_avl search 100 data/
... # execução/output do programa
# geração do CSV de estatísticas usando a BST para a leitura de 1000 arquivos, com 25 pontos igualmente espaçados
./src/output/tree_stats bst 1000 25 data/
... # execução/output do programa
# geração do CSV de estatísticas usando a AVL para a leitura de 1000 arquivos, com 25 pontos igualmente espaçados
./src/output/tree_stats avl 1000 25 data/
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
# geração do CSV de estatísticas usando a BST para a leitura de 1000 arquivos, com 25 pontos igualmente espaçados
src\output\tree_stats bst 1000 25 data\
... # execução/output do programa
# geração do CSV de estatísticas usando a AVL para a leitura de 1000 arquivos, com 25 pontos igualmente espaçados
src\output\tree_stats avl 1000 25 data\
... # execução/output do programa
make clean
```
