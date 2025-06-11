import pandas as pd
import matplotlib.pyplot as plt

bst = pd.read_csv("dados_bst.csv")
avl = pd.read_csv("dados_avl.csv")
# rbt = pd.read_csv("dados_rbt.csv")
col_names = bst.columns[1:]

def save_graph(col_name_1, col_name_2, pre, title, path):
    _, axes = plt.subplots(1, 2, figsize=(12, 5))  
    axes[0].plot(bst["N_docs"], bst[col_name_1], label="BST")
    axes[0].plot(avl["N_docs"], avl[col_name_1], label="AVL")
    # axes[0].plot(rbt["N_docs"], rbt[col_name_1], label="RBT")
    axes[0].set_xlabel("Número de documentos")
    axes[0].set_ylabel(col_name_1)
    axes[0].set_title(pre + " Médio " + title)
    axes[0].legend()
    axes[0].grid()

    axes[1].plot(bst["N_docs"], bst[col_name_2], label="BST")
    axes[1].plot(avl["N_docs"], avl[col_name_2], label="AVL")
    # axes[0].plot(rbt["N_docs"], rbt[col_name_2], label="RBT")
    axes[1].set_xlabel("Número de documentos")
    axes[1].set_ylabel(col_name_2)
    axes[1].set_title(pre + " Total " + title)
    axes[1].legend()
    axes[1].grid()
    
    plt.tight_layout(rect=[0, 0, 1, 0.95])
    plt.savefig(f'docs/graphs/grafico_{path}.png')
    plt.close()


save_graph(col_names[1], col_names[0], pre="Número", title="de Comparações para Inserção", path="NumComparisonsInsertion")
save_graph(col_names[2], col_names[3], pre="Tempo", title="de Inserção de Palavra", path="ExecutionTimeInsertion")
save_graph(col_names[4], col_names[5], pre="Número", title="de Comparações para Busca", path="NumComparisonsSearch")
save_graph(col_names[6], col_names[7], pre="Tempo", title="de Busca de Palavra", path="ExecutionTimeSearch")

#Altura da árvore
plt.figure()
plt.plot(bst["N_docs"], bst['TreeHeight'], label="BST")
plt.plot(avl["N_docs"], avl['TreeHeight'], label="AVL")
# plt.plot(rbt["N_docs"], rbt['TreeHeight'], label="RBT")
plt.xlabel("Número de documentos")
plt.ylabel("TreeHeight")
plt.title("Altura da Árvore")
plt.legend()
plt.grid()
plt.savefig(f'docs/graphs/grafico_TreeHeight.png')
plt.close()

#Numero de nós
plt.figure()
plt.plot(bst["N_docs"], bst['NumNodes'], label="BST")
plt.plot(avl["N_docs"], avl['NumNodes'], label="AVL")
# plt.plot(rbt["N_docs"], rbt['NumNodes'], label="RBT")
plt.xlabel("Número de documentos")
plt.ylabel("NumNodes")
plt.title("Número de nós")
plt.legend()
plt.grid()
plt.savefig(f'docs/graphs/grafico_NumNodes.png')
plt.close()


#Tamanho dos galhos
plt.figure()
plt.plot(bst["N_docs"], bst['MinBranch'], label="BST", color="#1f77b4")
plt.plot(avl["N_docs"], avl['MinBranch'], label="AVL", color="#ff7f0e")
# plt.plot(rbt["N_docs"], rbt['MinBranch'], label="RBT", color="#2ca02c")
plt.plot(avl["N_docs"], avl['MaxBranch'], color="#ff7f0e")
plt.plot(bst["N_docs"], bst['MaxBranch'], color="#1f77b4")
# plt.plot(rbt["N_docs"], rbt['MaxBranch'], color="#2ca02c")
plt.xlabel("Número de documentos")
plt.ylabel("Tamanaho do galho")
plt.title("Comparação maior e menor galho")
plt.legend()
plt.grid()
plt.savefig(f'docs/graphs/grafico_branchs.png')
plt.close()


#Tamanho da arvore pelo numero de nós BST
plt.figure()
plt.plot(bst['TreeHeight'], 2**(bst['TreeHeight'] + 1) -1, label="max", linestyle="--", color="darkorange")
plt.plot(bst['TreeHeight'], bst['NumNodes'], label="BST", color="green")
plt.plot(bst['TreeHeight'], bst['TreeHeight'] + 1, label="min", linestyle="--", color="blue")
plt.title("Comparação de número de nós pela altura da árvore BST")
plt.xlabel("Altura da árvore")
plt.ylabel("Log do Número de nós")
plt.yscale("log")
plt.legend()
plt.savefig(f'docs/graphs/grafico_height_node_bst.png')
plt.close()

#Tamanho da arvore pelo numero de nós AVL
plt.figure()
plt.plot(avl['TreeHeight'], 2**(avl['TreeHeight'] + 1) -1, label="max", linestyle="--", color="darkorange")
plt.plot(avl['TreeHeight'], avl['NumNodes'], label="AVL", color="green")
plt.plot(avl['TreeHeight'], 2**(avl['TreeHeight']/2), label="min", linestyle="--", color="blue")
plt.title("Comparação de número de nós pela altura da árvore AVL")
plt.xlabel("Altura da árvore")
plt.ylabel("Log do Número de nós")
plt.yscale("log")
plt.legend()
plt.savefig(f'docs/graphs/grafico_height_node_avl.png')
plt.close()