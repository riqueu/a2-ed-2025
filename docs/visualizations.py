import pandas as pd
import matplotlib.pyplot as plt

bst = pd.read_csv("dados_bst.csv")
avl = pd.read_csv("dados_avl.csv")
# rbt = pd.read_csv("dados_rbt.csv")
col_names = bst.columns[1:]

def plot_graph(ax, col_name, title, ylabel):
    ax.plot(bst["N_docs"], bst[col_name], label="BST")
    ax.plot(avl["N_docs"], avl[col_name], label="AVL")
    # ax.plot(rbt["N_docs"], rbt[col_name], label="RBT")
    ax.set_xlabel("Número de documentos")
    ax.set_ylabel(ylabel)
    ax.set_title(title)
    ax.legend()

def save_branch_graph(col_name_1, col_name_2, title):
    _, axes = plt.subplots(1, 1, figsize=(6, 5)) 
    plot_graph(axes, col_name_1, title, "Tamanaho do galho")
    axes.plot(avl["N_docs"], avl[col_name_2], color="#ff7f0e")
    axes.plot(bst["N_docs"], bst[col_name_2], color="#1f77b4")
    # axes[0].plot(rbt["N_docs"], rbt[col_name_2], color="#2ca02c")
    plt.savefig(f'docs/graphs/grafico_branchs.png')
    plt.close()
    
def save_simple_graph(col_name, title):
    _, axes = plt.subplots(1, 1, figsize=(6, 5)) 
    plot_graph(axes, col_name, title, title)
    plt.savefig(f'docs/graphs/grafico_{col_name}.png')
    plt.close()

def save_double_graph(col_name_1, col_name_2, pre, title, path):
    _, axes = plt.subplots(1, 2, figsize=(12, 5))  
    if pre == "Tempo":
        plot_graph(axes[0], col_name_1, pre + " Médio " + title, "Tempo (em milissegundos)")
        plot_graph(axes[1], col_name_2, pre + " Total " + title, "Tempo (em milissegundos)")
    elif pre == "Número":
        plot_graph(axes[0], col_name_1, pre + " Médio " + title, "Número de comparações")
        plot_graph(axes[1], col_name_2, pre + " Total " + title, "Número de comparações")
    plt.tight_layout(rect=[0, 0, 1, 0.95])
    plt.savefig(f'docs/graphs/grafico_{path}.png')
    plt.close()

save_double_graph(col_names[0], col_names[1], pre="Tempo", title="de Inserção de uma Palavra", path="ExecutionTimeInsertion")
save_double_graph(col_names[2], col_names[3], pre="Tempo", title="de Busca de uma Palavra", path="ExecutionTimeSearch")
save_double_graph(col_names[4], col_names[5], pre="Número", title="de Comparações para Inserção", path="NumComparisonsInsertion")
save_double_graph(col_names[6], col_names[7], pre="Número", title="de Comparações para Busca", path="NumComparisonsSearch")
save_simple_graph(col_names[8], title="Altura da Árvore")
save_branch_graph(col_names[9], col_names[10], "Comparação maior e menor galho")
save_simple_graph(col_names[11], title="Número de nós")


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
plt.plot(avl['TreeHeight'], 2**(avl['TreeHeight']/1.44), label="min", linestyle="--", color="blue")
plt.title("Comparação de número de nós pela altura da árvore AVL")
plt.xlabel("Altura da árvore")
plt.ylabel("Log do Número de nós")
plt.yscale("log")
plt.legend()
plt.savefig(f'docs/graphs/grafico_height_node_avl.png')
plt.close()