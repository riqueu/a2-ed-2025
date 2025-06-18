import pandas as pd
import matplotlib.pyplot as plt

bst = pd.read_csv("docs/dados_bst.csv")
avl = pd.read_csv("docs/dados_avl.csv")
rbt = pd.read_csv("docs/dados_rbt.csv")
col_names = bst.columns[1:]

def plot_graph(ax, col_name, title, ylabel):
    ax.plot(bst["N_docs"], bst[col_name], label="BST", color="blue")
    ax.plot(avl["N_docs"], avl[col_name], label="AVL", color="green")
    ax.plot(rbt["N_docs"], rbt[col_name], label="RBT", color="red")
    ax.set_xlabel("Número de Documentos")
    ax.set_ylabel(ylabel)
    ax.set_title(title)
    ax.legend()

def save_branch_graph(col_name_1, col_name_2, title):
    _, axes = plt.subplots(1, 1, figsize=(6, 5)) 
    plot_graph(axes, col_name_1, title, "Tamanaho do Galho")
    axes.plot(avl["N_docs"], avl[col_name_2], color="green")
    axes.plot(bst["N_docs"], bst[col_name_2], color="blue")
    axes.plot(rbt["N_docs"], rbt[col_name_2], color="red")
    plt.tight_layout()
    plt.savefig(f'docs/graphs/grafico_branchs.png')
    plt.close()
    
def save_simple_graph(col_name, title):
    _, axes = plt.subplots(1, 1, figsize=(6, 5)) 
    plot_graph(axes, col_name, title, title)
    plt.tight_layout()
    plt.savefig(f'docs/graphs/grafico_{col_name}.png')
    plt.close()

def save_double_graph(col_name_1, col_name_2, pre, mid, title, path, log1=False, log2=False):
    _, axes = plt.subplots(1, 2, figsize=(12, 5))  
    if pre == "Tempo":
        if log1:
            axes[0].set_yscale("log")
        plot_graph(axes[0], col_name_1, pre + " Médio " + title, "Tempo (em milissegundos)")
        if log2:
            axes[1].set_yscale("log")
        plot_graph(axes[1], col_name_2, pre + " " + mid + " " + title, "")
    elif pre == "Número":
        if log1:
            axes[0].set_yscale("log")
        plot_graph(axes[0], col_name_1, pre + " Médio " + title, "Número de Comparações")
        if log2:
            axes[1].set_yscale("log")
        plot_graph(axes[1], col_name_2, pre + " " + mid + " " + title, "")
    plt.tight_layout()
    plt.savefig(f'docs/graphs/grafico_{path}.png')
    plt.close()

save_double_graph(col_names[0], col_names[1], pre="Tempo", mid="Total", 
                  title="de Inserção", path="ExecutionTimeInsertion")
save_double_graph(col_names[2], col_names[3], pre="Tempo", mid="Máximo (em log)", 
                  title="de Busca de uma Palavra", path="ExecutionTimeSearch", log2=True)
save_double_graph(col_names[4], col_names[5], pre="Número", mid="Total", 
                  title="de Comparações para Inserção", path="NumComparisonsInsertion")
save_double_graph(col_names[6], col_names[7], pre="Número", mid="Máximo", 
                  title="de Comparações para Busca", path="NumComparisonsSearch")

save_simple_graph(col_names[8], title="Altura da Árvore")
save_branch_graph(col_names[9], col_names[10], "Comparação maior e menor galho")
save_simple_graph(col_names[11], title="Número de Nós")
save_simple_graph(col_names[12], title="Tamanho da Árvore (bytes)")


#Tamanho da arvore pelo numero de nós BST
plt.figure()
plt.plot(bst['TreeHeight'], 2**(bst['TreeHeight'] + 1) -1, label="max", linestyle="--", color="black")
plt.plot(bst['TreeHeight'], bst['NumNodes'], label="BST", color="blue")
plt.plot(bst['TreeHeight'], bst['TreeHeight'] + 1, label="min", linestyle="--", color="black")
plt.title("Comparação de número de nós pela altura da árvore BST")
plt.xlabel("Altura da árvore")
plt.ylabel("Número de Nós (log)")
plt.yscale("log")
plt.legend()
plt.tight_layout()
plt.savefig(f'docs/graphs/grafico_height_node_bst.png')
plt.close()

#Tamanho da arvore pelo numero de nós AVL
plt.figure()
plt.plot(avl['TreeHeight'], 2**(avl['TreeHeight'] + 1) -1, label="max", linestyle="--", color="black")
plt.plot(avl['TreeHeight'], avl['NumNodes'], label="AVL", color="green")
plt.plot(avl['TreeHeight'], 2**(avl['TreeHeight']/1.44), label="min", linestyle="--", color="black")
plt.title("Comparação de número de nós pela altura da árvore AVL")
plt.xlabel("Altura da árvore")
plt.ylabel("Número de Nós (log)")
plt.yscale("log")
plt.legend()
plt.tight_layout()
plt.savefig(f'docs/graphs/grafico_height_node_avl.png')
plt.close()

#Tamanho da arvore pelo numero de nós RBT
plt.figure()
plt.plot(rbt['TreeHeight'], 2**(rbt['TreeHeight'] + 1) -1, label="max", linestyle="--", color="black")
plt.plot(rbt['TreeHeight'], rbt['NumNodes'], label="RBT", color="red")
plt.plot(rbt['TreeHeight'], 2**(rbt['TreeHeight']/2) -1, label="min", linestyle="--", color="black")
plt.title("Comparação de número de nós pela altura da árvore RBT")
plt.xlabel("Altura da árvore")
plt.ylabel("Número de Nós (log)")
plt.yscale("log")
plt.legend()
plt.tight_layout()
plt.savefig(f'docs/graphs/grafico_height_node_rbt.png')
plt.close()