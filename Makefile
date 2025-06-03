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
	EXE_EXT = .exe
	MKDIR = if not exist "$(subst /,\,$(OUTPUT_DIR))" mkdir "$(subst /,\,$(OUTPUT_DIR))"
	RM = del /Q
	RMDIR = rmdir /S /Q
	SEP = \\
else
	EXE_EXT =
	MKDIR = mkdir -p $(OUTPUT_DIR)
	RM = rm -f
	RMDIR = rm -rf
	SEP = /
endif

# executáveis
BST_EXEC = $(OUTPUT_DIR)$(SEP)main_bst$(EXE_EXT)
AVL_EXEC = $(OUTPUT_DIR)$(SEP)main_avl$(EXE_EXT)
RBT_EXEC = $(OUTPUT_DIR)$(SEP)main_rbt$(EXE_EXT)

# Targets para construir os executáveis
all: $(BST_EXEC) $(AVL_EXEC) $(RBT_EXEC)

# executaveis Binary Search Tree
$(BST_EXEC): $(BST_SOURCES)
	@$(MKDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# executaveis AVL Tree
$(AVL_EXEC): $(AVL_SOURCES)
	@$(MKDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# executaveis Red-Black Tree
$(RBT_EXEC): $(RBT_SOURCES)
	@$(MKDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# limpa arquivos gerados
clean:
ifeq ($(OS),Windows_NT)
	-$(RM) "$(subst /,\,$(BST_EXEC))" "$(subst /,\,$(AVL_EXEC))" "$(subst /,\,$(RBT_EXEC))"
	-$(RMDIR) "$(subst /,\,$(OUTPUT_DIR))"
else
	-$(RM) $(BST_EXEC) $(AVL_EXEC) $(RBT_EXEC)
	-$(RMDIR) $(OUTPUT_DIR)
endif

.PHONY: all clean