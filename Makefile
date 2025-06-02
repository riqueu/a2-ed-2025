# compilador e flags
CXX = g++
CXXFLAGS = -Wall -Wextra -g3

# diretórios
SRC_DIR = src
OUTPUT_DIR = $(SRC_DIR)/output

# source
BST_SOURCES = $(SRC_DIR)/main_bst.cpp $(SRC_DIR)/bst.cpp $(SRC_DIR)/data.cpp $(SRC_DIR)/tree_utils.cpp
AVL_SOURCES = $(SRC_DIR)/main_avl.cpp $(SRC_DIR)/avl.cpp $(SRC_DIR)/data.cpp $(SRC_DIR)/tree_utils.cpp
RBT_SOURCES = $(SRC_DIR)/main_rbt.cpp $(SRC_DIR)/rbt.cpp $(SRC_DIR)/data.cpp $(SRC_DIR)/tree_utils.cpp

# detecta o sistema operacional
ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXE_EXT = .exe
else
    RM = rm -f
    EXE_EXT =
endif

# executáveis
BST_EXEC = $(OUTPUT_DIR)/main_bst$(EXE_EXT)
AVL_EXEC = $(OUTPUT_DIR)/main_avl$(EXE_EXT)
RBT_EXEC = $(OUTPUT_DIR)/main_rbt$(EXE_EXT)

# Targets para construir os executáveis
all: $(BST_EXEC) $(AVL_EXEC) $(RBT_EXEC)

# executaveis Binary Search Tree
$(BST_EXEC): $(BST_SOURCES)
	@mkdir -p $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# executaveis AVL Tree
$(AVL_EXEC): $(AVL_SOURCES)
	@mkdir -p $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# executaveis Red-Black Tree
$(RBT_EXEC): $(RBT_SOURCES)
	@mkdir -p $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# limpa arquivos gerados
clean:
	$(RM) $(BST_EXEC) $(AVL_EXEC) $(RBT_EXEC)
	$(RM) -r $(OUTPUT_DIR)

.PHONY: all clean