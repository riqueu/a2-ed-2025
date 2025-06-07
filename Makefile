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

# test sources
TEST_BST_SOURCES = $(SRC_DIR)/test_bst.cpp $(SRC_DIR)/bst.cpp $(SRC_DIR)/data.cpp $(SRC_DIR)/tree_utils.cpp
TEST_AVL_SOURCES = $(SRC_DIR)/test_avl.cpp $(SRC_DIR)/avl.cpp $(SRC_DIR)/data.cpp $(SRC_DIR)/tree_utils.cpp
TEST_RBT_SOURCES = $(SRC_DIR)/test_rbt.cpp $(SRC_DIR)/rbt.cpp $(SRC_DIR)/data.cpp $(SRC_DIR)/tree_utils.cpp

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

# executáveis de testes
TEST_BST_EXEC = $(OUTPUT_DIR)$(SEP)test_bst$(EXE_EXT)
TEST_AVL_EXEC = $(OUTPUT_DIR)$(SEP)test_avl$(EXE_EXT)
TEST_RBT_EXEC = $(OUTPUT_DIR)$(SEP)test_rbt$(EXE_EXT)

# listas de targets (main e test)
MAIN_TARGETS =
TEST_TARGETS =

# usa apenas os arquivos que existem na compilaçao
ifneq ($(wildcard $(SRC_DIR)/main_bst.cpp),)
    MAIN_TARGETS += $(BST_EXEC)
endif
ifneq ($(wildcard $(SRC_DIR)/main_avl.cpp),)
    MAIN_TARGETS += $(AVL_EXEC)
endif
ifneq ($(wildcard $(SRC_DIR)/main_rbt.cpp),)
    MAIN_TARGETS += $(RBT_EXEC)
endif
ifneq ($(wildcard $(SRC_DIR)/test_bst.cpp),)
    TEST_TARGETS += $(TEST_BST_EXEC)
endif
ifneq ($(wildcard $(SRC_DIR)/test_avl.cpp),)
    TEST_TARGETS += $(TEST_AVL_EXEC)
endif
ifneq ($(wildcard $(SRC_DIR)/test_rbt.cpp),)
    TEST_TARGETS += $(TEST_RBT_EXEC)
endif

# targets para construção dos executáveis
all: $(MAIN_TARGETS) $(TEST_TARGETS)
run_test: $(TEST_TARGETS)
run_main: $(MAIN_TARGETS)

# Regras condicionais de compilação
ifneq ($(wildcard $(SRC_DIR)/main_bst.cpp),)
$(BST_EXEC): $(BST_SOURCES)
	@$(MKDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@
endif

ifneq ($(wildcard $(SRC_DIR)/main_avl.cpp),)
$(AVL_EXEC): $(AVL_SOURCES)
	@$(MKDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@
endif

ifneq ($(wildcard $(SRC_DIR)/main_rbt.cpp),)
$(RBT_EXEC): $(RBT_SOURCES)
	@$(MKDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@
endif

ifneq ($(wildcard $(SRC_DIR)/test_bst.cpp),)
$(TEST_BST_EXEC): $(TEST_BST_SOURCES)
	@$(MKDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@
endif

ifneq ($(wildcard $(SRC_DIR)/test_avl.cpp),)
$(TEST_AVL_EXEC): $(TEST_AVL_SOURCES)
	@$(MKDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@
endif

ifneq ($(wildcard $(SRC_DIR)/test_rbt.cpp),)
$(TEST_RBT_EXEC): $(TEST_RBT_SOURCES)
	@$(MKDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@
endif

# limpa diretório e arquivos gerados
clean:
ifeq ($(OS),Windows_NT)
	-$(RMDIR) "$(subst /,\,$(OUTPUT_DIR))"
else
	-$(RMDIR) $(OUTPUT_DIR)
endif

.PHONY: all clean run_test run_main