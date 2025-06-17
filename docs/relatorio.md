# Relatório do Projeto: Índice Invertido e Análise Comparativa de Estruturas de Dados  

* **Alunos integrantes**: Bruno Ferreira Salvi, Henrique Coelho Beltrão, Henrique Gabriel Gasparelo, José Thevez Gomes Guedes e Luiz Eduardo Bravin.
* **Professor orientador**: Matheus Telles Werner.
* **Repositório**: https://github.com/riqueu/a2-ed-2025/

---
## Resumo
Este trabalho detalha a implementação e a avaliação de desempenho de um índice invertido utilizando três estruturas de dados baseadas em árvores: a Árvore Binária de Busca (BST), a Árvore AVL e a Árvore Rubro-Negra (RBT). O objetivo foi comparar a eficiência de cada estrutura em operações de inserção e busca, aplicadas a um corpus de aproximadamente 10.000 documentos de texto. As métricas analisadas, como tempo de execução, número de comparações e altura da árvore, demonstraram a superioridade das árvores auto-balanceadas (AVL e RBT) sobre a BST, que se mostrou suscetível à degeneração. Os resultados indicaram que a RBT ofereceu o melhor tempo de inserção, enquanto a AVL se destacou por buscas ligeiramente mais rápidas e estáveis. Conclui-se que a RBT representa a escolha mais equilibrada para aplicações dinâmicas com operações frequentes de inserção e busca, e a AVL é ideal para cenários onde a velocidade de consulta é a prioridade máxima.

## 1. Introdução

Neste projeto, visa-se implementar um índice invertido, ou seja, um mapeamento de palavras e os documentos em que elas aparecem, e alocá-lo em uma estrutura de dados que otimize a busca no mesmo. Para isto, serão utilizadas as estruturas denominadas de árvores, que para o escopo deste projeto serão: **Árvore Binária de Busca (BST)**, **Árvore AVL (AVL)** e **Árvore Rubro-Negra (RBT)**, sendo as três árvores binárias de busca, entretanto com diferentes abordagens que serão exploradas nesse projeto. 

Como árvores binárias de busca, em qualquer uma das três árvores, os nós possuem no máximo 2 filhos, onde os descendentes à esquerda são anteriores, em ordem, nesse caso alfabética, ao pai e os à direita são posteriores. Desta forma, no caso ideal, a altura da árvore é proporcional a $log(n)$, possibilitando operações mais rápidas, tanto de busca quanto inserção. Logo, a diferença fundamental entre as árvores é na forma como as propriedades modificam as funções de inserção, o que impacta diretamente na organização dos nós na árvore. 

Na BST, não existe nenhuma regra adicional, além das já estabelecidas para uma árvore binária de busca, o que, portanto, possibilita uma fácil implementação das funções de inserção e busca. Apesar disso, a falta de regras que garantam o balanceamento permitem, por exemplo, a existência de casos degenerados, onde a árvore se torna uma lista encadeada e sua performance é $O(n)$ para todas as operações. Já para a AVL, são instauradas regras de balanceamento, onde, para cada nó, a diferença de altura entre suas subárvores esquerda e direita (fator de balanceamento) é no máximo 1, isso é garantido por meio de funções de rotação que alteram as alturas das subárvores. Por conta dessas restrições, as funções de inserção fazem mais alterações na árvore para boa parte dos nós inseridos. Entretanto, o balaceamento garante operações com complexidade $O(log(n))$, no pior caso. A fim de diminuir o grau de restrição da AVL, a RBT mantém o balanceamento através de um conjunto de regras que envolvem colorir cada nó de vermelho ou preto. Essas regras garantem que o caminho mais longo da raiz a qualquer folha não seja mais que o dobro do caminho mais curto, permitindo um custo operacional de $O(log(n))$, no pior caso, com uma menor rigidez que a AVL. Mesmo assim, por conta deste comportamento, a RBT pode apresentar uma altura ligeiramente maior que AVL, em determinadas situações. 

Portanto, o objetivo principal é analisar e comparar o desempenho dessas estruturas em operações fundamentais como inserção e busca, considerando diferentes volumes de dados.

## 2. Desenvolvimento

### 2.1. Metodologia de funcionamento

A comparação entre as três estruturas de dados foi realizada seguindo os passos abaixo:

1.  **Corpus de Documentos:** Foi utilizado um conjunto de aproximadamente 10.000 documentos de texto (`.txt`) com palavras já pré-processadas, com todas minúsculas e sem pontuações.
2.  **Construção do Índice:** As palavras extraídas foram inseridas como `Node` em cada uma das três estruturas de árvore (BST, AVL, RBT). Para cada palavra, o ID do documento em que ela apareceu foi adicionado à lista de documentos associada ao nó da palavra, conforme a estrutura abaixo:
```cpp
struct Node {
    std::string word;
    std::vector<int> documentIds;
    Node* parent;
    Node* left;
    Node* right;
    int height;    // usado na AVL
    int isRed;     // usado na RBT
};
```
3.  **Coleta de Métricas:** Os métricas abaixo foram calculadas para diferentes subconjuntos do corpus, variando o número de documentos processados de 100 a 10.000 documentos.
    * Tempo de inserção (média, total)
    * Tempo de busca de palavras (médio, máximo)
    * Número de comparações por operação
    * Altura da árvore
    * Tamanho dos galhos (menor e maior caminho)
    * Número de nós
    * Tamanho da árvore
4.  **Ferramentas:** A implementação das árvores e coleta de métricas foram realizadas por programas em C++. Os gráficos e análises estatísticas foram feitos utilizando a biblioteca Matplotlib de Python.

### 2.2. Código

Agora segue detalhamento das principais abordagens utilizadas no código do projeto.

Leitura dos documentos (`data.cpp`): Para a extração das palavras dos documentos, foram processados os arquivos do diretório e suas palavras foram colocadas e um vetor, nesse momento, é verificada a existência de palavras duplicadas em um arquivo, percorrendo esse vetor, e apenas os elementos únicos são inseridos. Vale salientar que a ordem de leitura dos documentos pelo iterador do diretório não necessariamente representa a ordem numérica habitual, deste modo, documentos de id superiores podem ser lidos antes dos arquivos com id inferiores.

Implementação da árvores (`bst.cpp`, `avl.cpp`, `rbt.cpp`): Para a implementação das árvores, foram desenvolvidas funções de criação, inserção, busca e deleção das mesmas, além de elaboração das funções que conservam as propriedades de balanceamento da AVL e RBT. Para a AVL, foi estipulado que a altura de nó vazio é $-1$, consequentemente, a altura das folhas é $0$, e foi considerado, como fator de balaceamento, a diferença entre as alturas das subárvores à direita e à esquerda.

Implementação dos testes (`test_bst.cpp`, `test_avl.cpp`, `test_rbt.cpp`): Para implementação dos testes, foram verificadas a consistência das regras de cada árvore, as funções de inserção e de busca.

Geração e coleta de estatísticas (`tree_utils.cpp`, `tree_stats.cpp`, `export_stats.cpp`): Para coleta das métricas, no arquivo `tree_utils.cpp`, foram implementadas funções que geram as estatísticas referentes às árvores. Estas métricas são utilizadas no CLI de estatísticas e na criação de um arquivo CSV com os dados obtidos.

Arquivos principais (`main_bst.cpp`, `main_avl.cpp`, `main_rbt.cpp`): Para utilização do código por outros usuários, no arquivo main de cada árvore, foram desenvolvidos comandos CLI para busca de uma determinada palavra, geração de estatísticas e visualização da árvore.

### 2.3 Estatísticas

Assim como supracitado, o documento ‘tree_utils.cpp’ contém funções que coletam as estatísticas com base em parâmetros, como o tipo da árvore e a quantidade de documentos que serão inseridos. A partir dessas funções, são coletadas estatísticas como: o número total de documentos inseridos na estrutura (`n_docs`); o número médio (`numComparisonsInsertionMean`) e total (`numComparisonsInsertion`) de comparações realizadas durante as operações de inserção; o tempo médio (`executionTimeInsertionMean`) e total (`executionTimeInsertion`) de execução das inserções, medidos em milissegundos; o número médio (`numComparisonsSearchMean`) e o máximo (`numComparisonsSearchMax`) de comparações realizadas durante as buscas; o tempo máximo (`executionTimeSearchMax`) e médio (`executionTimeSearchMean`) de execução das buscas; a altura final da árvore (`treeHeight`) após todas as inserções; o comprimento do menor galho (`minBranch`); o número total de nós existentes na árvore (`numNodes`); além do tamanho total ocupado pela árvore em memória, representado em bytes (`size`).

Vale ressaltar que, neste contexto, são considerados como número de comparações a quantidade de nós que foram percorridos durante a operação, ou seja, é contabilizado cada comparação com um nó durante a inserção ou busca. Além disso, a fim de reduzir erros de medições de tempo nas estáticas de tempo de busca, para as árvores que tem 800 documentos ou menos, a busca por cada palavra é realizada 50 vezes, e então é calculado a médias desses resultados, mitigando assim, as oscilações causas pelo computador nos tempos calculados.

Essas métricas permitem a análise comparativa dos diferentes tipos de implementação de árvores, possibilitando, por exemplo, a comparação do impacto do número de documentos inseridos na altura de cada uma das árvores.

No documento `tree_stats.cpp`, utilizando as funções responsáveis pela coleta de estatísticas, são armazenadas as métricas obtidas de um tipo especificado de árvore, variando a quantidade de documentos inseridos. Essas estatísticas são então concatenadas em um arquivo CSV, o que viabiliza a plotagem dos dados e facilita a análise entre as diferentes estruturas de árvores. Vale destacar que o `tree_stats.cpp` deve ser executado separadamente para cada tipo de árvore, uma vez que o CSV gerado tem apenas as estatísticas referentes a um único tipo de árvore.

### 2.4. Divisão de Tarefas

#### 2.4.1. Entrega 1
* **Bruno Ferreira Salvi:** Implementação da função de busca para BST e da CLI (Busca) para BST;
* **Henrique Coelho Beltrão:** Implementação de funções para estatísticas, ajustes na CLI para estatísticas e construção do Makefile;
* **Henrique Gabriel Gasparelo:** Implementação das funções de print da árvore, de inserção na BST e de destroy da BST;
* **José Thevez Gomes Guedes:** Implementação das funções para leitura dos arquivos e construção do índice invertido;
* **Luiz Eduardo Bravin:** Implementação dos teste unitários da BST e inicialização da redação do relatório.

#### 2.4.2. Entrega 2

* **Bruno Ferreira Salvi:** Implementação da CLI para AVL e estatísticas extras;
* **Henrique Coelho Beltrão:** Implementação das funções da AVL, testes unitários da AVL, refatoração do código;
* **Henrique Gabriel Gasparelo:** Implementação das estatísticas para árvores;
* **José Thevez Gomes Guedes:** Implementação das estatísticas para árvores e transição para CSV;
* **Luiz Eduardo Bravin:** Implementação da análise comparativa das árvores, geração dos gráficos em Python e redação do relatório.

#### 2.4.3. Entrega 3

* **Bruno Ferreira Salvi:** Elaboração e revisão do relatório final, formulação das estatísticas extras e revisão geral do código e documentação;
* **Henrique Coelho Beltrão:**  Elaboração e revisão do relatório final, revisão geral do código, documentação, instruções de execução com novos dados e ajustes no Makefile;
* **Henrique Gabriel Gasparelo:** Implementação dos testes unitários da RBT e redação do relatório;
* **José Thevez Gomes Guedes:** Implementação das funções da RBT e redação do relatório;
* **Luiz Eduardo Bravin:** Implementação da CLI para RBT, atualização das funções úteis para comportar NIL e redação do relatório.

## 3. Resultados e Discussões

Nesta seção, apresentamos os resultados numéricos obtidos e uma discussão sobre o desempenho comparativo das estruturas.

### 3.1. Tempo de Inserção
#### **Figura 1: Tempo de Inserção de Palavra**
![Figura 1](graphs/grafico_ExecutionTimeInsertion.png)
#### **Discussão:** Analisando o tempo total de inserção, nota-se que a RBT apresentou o melhor desempenho, sendo consistentemente mais rápida que as outras duas. A árvore AVL, embora mantenha um tempo de inserção estável, foi ligeiramente mais lenta que a RBT, provavelmente devido ao maior número de rotações necessárias para manter seu balanceamento estrito. A BST, por sua vez, apresentou tempos médios voláteis e um tempo total que, embora próximo ao da AVL, reflete sua ineficiência estrutural.

### 3.2. Tempo de Busca
#### **Figura 2: Tempo de Busca de Palavra**
![Figura 2](graphs/grafico_ExecutionTimeSearch.png)
#### **Discussão:** As árvores auto-balanceadas, AVL e RBT, reduziram consideravelmente o tempo de busca em relação à BST. A AVL apresentou o tempo médio de busca mais baixo e estável, confirmando que seu balanceamento rigoroso é vantajoso para consultas. A RBT teve um desempenho muito próximo ao da AVL, sendo também uma excelente opção para buscas. A BST foi a mais lenta, com picos de tempo de busca que evidenciam os problemas causados por seu desbalanceamento.

### 3.3. Número de Comparações
#### **Figura 3: Número de Comparações por Inserção de Palavra**
![Figura 3](graphs/grafico_NumComparisonsInsertion.png)
#### **Figura 4: Número de Comparações por Busca de Palavra**
![Figura 4](graphs/grafico_NumComparisonsSearch.png)
#### **Discussão:** Tanto na inserção quanto na busca, as árvores AVL e RBT realizaram um número de comparações significativamente menor que a BST. Para inserções, a RBT exigiu o menor número total de comparações, seguida de perto pela AVL, o que corrobora seus tempos de inserção mais baixos. Para buscas, a AVL se mostrou marginalmente mais eficiente, realizando, em média e no pior caso, o menor número de comparações, com a RBT apresentando resultados quase idênticos.

### 3.4. Altura da Árvore
#### **Figura 5: Altura da Árvore**
![Figura 5](graphs/grafico_TreeHeight.png)
#### **Discussão:** Nota-se que a altura da árvore não cresce tanto conforme se aumenta o número de documentos, pois nos primeiros 40 documentos acessados já são computadas e criados os respectivos nós para mais de 4 mil palavras distintas, com os outros documentos apenas acrescentando unidades a esses nós, sem criar novos. As árvores BST têm em média o dobro da altura das árvores AVL e RBT, visto que aquelas podem vir a degenerar, enquanto que estas — por serem balanceadas — organizam melhor os nós pelas camadas, reduzindo a altura. As alturas da AVL e da RBT permaneceram muito próximas durante todo o experimento.

### 3.5. Tamanho dos Galhos (Menor e Maior Caminho)
#### **Figura 6: Tamanho do Maior e Menor Galho**
![Figura 6](graphs/grafico_branchs.png)
#### **Discussão:** Nota-se que a distância entre o maior e menor galho da AVL e da RBT é bem curta, enquanto na BST essa distância é exageradamente longa. Isso ocorre devido à natureza da AVL e da RBT, que são projetadas para evitar degenerações e manter a árvore balanceada, com isso balanceia-se também o tamanho dos galhos. Em contrapartida, alguns galhos da BST podem degenerar e se tornar longos demais.

### 3.6. Números de nós
#### **Figura 7: Número de nós**
![Figura 7](graphs/grafico_NumNodes.png)
#### **Discussão:** Nota-se que para as três árvores os os números de nós é o mesmo, óbvio, pois todas possuem a mesma natureza de adicionar um nó para cada palavra única encontrada nos documentos e como ambas estão analisando os mesmos documentos. Nota-se algo mais interessante, no entanto, a quantidade de nós adicionados vai diminuindo conforme se aumenta a quantidade de documentos. Isso acontece pois as 4 mil palavras adicionadas nos primerios 40 arquivos são provavelmente as palavras mais utilizadas no idioma, os arquivos seguintes, portanto, estarão repletos dessas palavras que serão adicionadas aos nós já existentes e de algumas outras menos utilizadas que constituirão os novos nós. Desse modo, a cada arquivo analisado aumenta a probabilidade de uma palavra que já foi computada aparecer novamente, o que diminui a criação de novos nós pelos últimos documentos, podendo inclusive um documento não adicionar nenhum novo nó.

### 3.7. Tamanho da árvore
#### **Figura 8: Tamanho da árvore**
![Figura 8](graphs/grafico_TreeSizeBytes.png)
#### **Discussão:**


## 4. Gráficos e Estatísticas

#### **Figura 9: Altura da Árvore vs. Número de nós BST**
![Figura 9](graphs/grafico_height_node_bst.png)
#### **Discussão:** Nesse gráfico verifica-se que o número de nós computados está dentro do aceitável, entre o máximo e mínimo teórico da BST. O mínimo número de nós se dá quando a BST degenera, isto é, há um nó por camada, logo $n \geq h + 1$. O número máximo de nós se dá quando a BST está completa, isto é, há $2^{m}$ nós na camada de altura $m$, logo $n \leq 2^{n+1} -1$.

#### **Figura 10: Altura da Árvore vs. Número de nós AVL**
![Figura 10](graphs/grafico_height_node_avl.png)
#### **Discussão:** Nesse gráfico verifica-se que o número de nós computados está dentro do aceitável, entre o máximo e mínimo teórico da AVL. O mínimo número de nós se dá quando se cumpre minimamente as restrições de balanceamento da AVL, logo $n \geq 2^{\frac{h}{1.44}}$. O número máximo de nós se dá quando a AVL está completa, isto é, há $2^{m}$ nós na camada de altura $m$, logo $n \leq 2^{n+1} -1$.

#### **Figura 11: Altura da Árvore vs. Número de nós AVL**
![Figura 11](graphs/grafico_height_node_rbt.png)
#### **Discussão:** Nesse gráfico verifica-se que o número de nós computados está dentro do aceitável, entre o máximo e mínimo teórico da RBT. O mínimo número de nós se dá quando se cumpre minimamente as restrições de balanceamento da RBT, logo $n \geq 2^{\frac{h}{2}} -1$. O número máximo de nós se dá quando a RBT está completa, isto é, há $2^{m}$ nós na camada de altura $m$, logo $n \leq 2^{n+1} -1$.

## 5. Conclusão

Após a implementação das três estruturas de dados para aplicacação do índice invertido e análise dos dados, podemos extrair as seguintes conclusões:

### 5.1. Árvore Binária de Busca (BST)

* **Vantagens:** Simplicidade de implementação, constituindo uma base para o entendimento de estruturas mais complexas.
* **Desvantagens:** Suscetível à degeneração, onde a altura da árvore aproxima-se do número de nós, análogo a uma lista encadeada.
* **Observado:** Os resultados confirmaram a tendência da BST ao desbalanceamento (Figuras 5 e 6), com uma altura significativamente maior e uma grande disparidade entre os galhos. Isso impactou diretamente seu tempo de busca (Figura 2), que foi o mais lento entre as estruturas.

### 5.2. Árvore Adelson-Velsky e Landis (AVL)

* **Vantagens:** Garante um tempo de busca logarítmico, mantem a altura da árvore próxima do mínimo teórico.
* **Desvantagens:** A manutenção do balanceamento estrito pode exigir rotações mais frequentes durante as inserções, o que pode aumentar o custo dessa operação.
* **Observado:** A AVL manteve uma altura controlada e muito menor (Figura 5), resultando em número de comparações e tempo de busca (Figuras 2 e 4) consideravelmente inferiores aos da BST, provando sua eficácia para aplicações focadas em consulta.

### 5.3. Árvore Rubro-Negra (RBT)

* **Vantagens:** Seu critério de balanceamento menos rígido que o da AVL geralmente resulta em menos rotações durante as inserções, tornando-as potencialmente mais rápidas.
* **Desvantagens:** A altura pode ser ligeiramente maior que a de uma AVL, podendo levar a um tempo de busca um pouco maior.
* **Observado:** 

### 5.4. Recomendação Final 

## 6. Dificuldades Encontradas
* **Complexidade de Implementação:** A lógica de auto-balanceamento, especialmente as rotações simples e duplas da AVL, foi desafiadora e exigiu depuração extensiva. 
* **Trabalho em Equipe:** Coordenar a integração dos diferentes branchs desenvolvidas pelos membros e manter a consistência do código demandou comunicação eficaz e uso disciplinado do Git.

## 8. Divisão de Tarefas

### 8.1 Entrega 1
* **Bruno Ferreira Salvi:** Implementação da função de busca para BST e da CLI (Busca) para BST;
* **Henrique Coelho Beltrão:** Implementação de funções para estatísticas, ajustes na CLI para estatísticas e construção do Makefile;
* **Henrique Gabriel Gasparelo:** Implementação das funções de print da árvore, de inserção na BST e de destroy da BST;
* **José Thevez Gomes Guedes:** Implementação das funções para leitura dos arquivos e construção do índice invertido;
* **Luiz Eduardo Bravin:** Implementação dos teste unitários da BST e inicialização da redação do relatório.

### 8.2 Entrega 2

* **Bruno Ferreira Salvi:** Implementação da CLI para AVL e estatísticas extras;
* **Henrique Coelho Beltrão:** Implementação das funções da AVL, testes unitários da AVL, refatoração do código;
* **Henrique Gabriel Gasparelo:** Implementação das estatísticas para árvores;
* **José Thevez Gomes Guedes:** Implementação das estatísticas para árvores e transição para CSV;
* **Luiz Eduardo Bravin:** Implementação da análise comparativa das árvores, geração dos gráficos em Python e redação do relatório.

### 8.3 Entrega 3

* **Bruno Ferreira Salvi:** Elaboração e revisão do relatório final, formulação das estatísticas extras e revisão geral do código e documentação;
* **Henrique Coelho Beltrão:**  Elaboração e revisão do relatório final, revisão geral do código, documentação, instruções de execução com novos dados e ajustes no Makefile;
* **Henrique Gabriel Gasparelo:** Implementação dos testes unitários da RBT e redação do relatório;
* **José Thevez Gomes Guedes:** Implementação das funções da RBT;
* **Luiz Eduardo Bravin:** Implementação da CLI para RBT, atualização das funções úteis para comportar NIL e redação do relatório.
