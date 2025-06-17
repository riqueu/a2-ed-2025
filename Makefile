# compilador e flags
CXX = g++
CXXFLAGS = -Wall -Wextra -g3

# diretórios
SRC_DIR = src
OUTPUT_DIR = $(SRC_DIR)/output
DATA_DIR = data
STAMP_FILE = .unzip-stamp

# source
BST_SOURCES = $(SRC_DIR)/main_bst.cpp $(SRC_DIR)/bst.cpp $(SRC_DIR)/avl.cpp $(SRC_DIR)/rbt.cpp $(SRC_DIR)/data.cpp $(SRC_DIR)/tree_utils.cpp
AVL_SOURCES = $(SRC_DIR)/main_avl.cpp $(SRC_DIR)/avl.cpp $(SRC_DIR)/bst.cpp $(SRC_DIR)/rbt.cpp $(SRC_DIR)/data.cpp $(SRC_DIR)/tree_utils.cpp
RBT_SOURCES = $(SRC_DIR)/main_rbt.cpp $(SRC_DIR)/rbt.cpp $(SRC_DIR)/bst.cpp $(SRC_DIR)/avl.cpp $(SRC_DIR)/data.cpp $(SRC_DIR)/tree_utils.cpp

# test sources
TEST_BST_SOURCES = $(SRC_DIR)/test_bst.cpp $(SRC_DIR)/bst.cpp $(SRC_DIR)/avl.cpp $(SRC_DIR)/rbt.cpp $(SRC_DIR)/data.cpp $(SRC_DIR)/tree_utils.cpp
TEST_AVL_SOURCES = $(SRC_DIR)/test_avl.cpp $(SRC_DIR)/avl.cpp $(SRC_DIR)/bst.cpp $(SRC_DIR)/rbt.cpp $(SRC_DIR)/data.cpp $(SRC_DIR)/tree_utils.cpp
TEST_RBT_SOURCES = $(SRC_DIR)/test_rbt.cpp $(SRC_DIR)/rbt.cpp $(SRC_DIR)/bst.cpp $(SRC_DIR)/avl.cpp $(SRC_DIR)/data.cpp $(SRC_DIR)/tree_utils.cpp

# tree stats sources
TREE_STATS_SOURCES = $(SRC_DIR)/tree_stats.cpp $(SRC_DIR)/bst.cpp $(SRC_DIR)/avl.cpp $(SRC_DIR)/rbt.cpp $(SRC_DIR)/data.cpp $(SRC_DIR)/tree_utils.cpp $(SRC_DIR)/export_stats.cpp

# detecta o sistema operacional
ifeq ($(OS),Windows_NT)
	EXE_EXT = .exe
	RM = del /Q /F
	RMDIR = rmdir /S /Q
	SEP = \\
	UNZIP_CMD = tar -xf data.zip
	TOUCH = type NUL >
	MKDIR_P = if not exist "$(subst /,\,$(1))" mkdir "$(subst /,\,$(1))"
	SETUP_DATA_CMD = if exist "$(subst /,\,$(DATA_DIR))" ($(TOUCH) $@) else (if exist "data.zip" (echo Extracting data... & $(UNZIP_CMD) && $(TOUCH) $@) else (echo ERROR: Directory 'data' and file 'data.zip' not found. & exit 1))
else
	EXE_EXT =
	RM = rm -f
	RMDIR = rm -rf
	SEP = /
	UNZIP_CMD = unzip -qo data.zip
	TOUCH = touch
	MKDIR_P = mkdir -p $(1)
	SETUP_DATA_CMD = if [ -d "$(DATA_DIR)" ]; then $(TOUCH) $@; else if [ -f "data.zip" ]; then echo "Extracting data..."; $(UNZIP_CMD) && $(TOUCH) $@; else echo "ERROR: Directory 'data' and file 'data.zip' not found." >&2; exit 1; fi; fi

endif

# executáveis
BST_EXEC = $(OUTPUT_DIR)$(SEP)main_bst$(EXE_EXT)
AVL_EXEC = $(OUTPUT_DIR)$(SEP)main_avl$(EXE_EXT)
RBT_EXEC = $(OUTPUT_DIR)$(SEP)main_rbt$(EXE_EXT)

# executáveis de testes
TEST_BST_EXEC = $(OUTPUT_DIR)$(SEP)test_bst$(EXE_EXT)
TEST_AVL_EXEC = $(OUTPUT_DIR)$(SEP)test_avl$(EXE_EXT)
TEST_RBT_EXEC = $(OUTPUT_DIR)$(SEP)test_rbt$(EXE_EXT)

# executável de estatísticas de árvores
TREE_STATS_EXEC = $(OUTPUT_DIR)$(SEP)tree_stats$(EXE_EXT)

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
ifneq ($(wildcard $(SRC_DIR)/tree_stats.cpp),)
    MAIN_TARGETS += $(TREE_STATS_EXEC)
endif

# Alvo principal depende do 'carimbo' e dos executáveis
all: $(STAMP_FILE) $(MAIN_TARGETS) $(TEST_TARGETS)
run_test: $(STAMP_FILE) $(TEST_TARGETS)
run_main: $(STAMP_FILE) $(MAIN_TARGETS)

# Se data.zip não existir (nem o diretório data/), o make falhará automaticamente (comportamento desejado)
$(STAMP_FILE):
	@$(SETUP_DATA_CMD)

# Regras condicionais de compilação
ifneq ($(wildcard $(SRC_DIR)/main_bst.cpp),)
$(BST_EXEC): $(BST_SOURCES)
	@echo "Compiling BST main..."
	@$(call MKDIR_P,$(OUTPUT_DIR))
	$(CXX) $(CXXFLAGS) $^ -o $@
endif

ifneq ($(wildcard $(SRC_DIR)/main_avl.cpp),)
$(AVL_EXEC): $(AVL_SOURCES)
	@echo "Compiling AVL main..."
	@$(call MKDIR_P,$(OUTPUT_DIR))
	$(CXX) $(CXXFLAGS) $^ -o $@
endif

ifneq ($(wildcard $(SRC_DIR)/main_rbt.cpp),)
$(RBT_EXEC): $(RBT_SOURCES)
	@echo "Compiling RBT main..."
	@$(call MKDIR_P,$(OUTPUT_DIR))
	$(CXX) $(CXXFLAGS) $^ -o $@
endif

ifneq ($(wildcard $(SRC_DIR)/test_bst.cpp),)
$(TEST_BST_EXEC): $(TEST_BST_SOURCES)
	@echo "Compiling BST test..."
	@$(call MKDIR_P,$(OUTPUT_DIR))
	$(CXX) $(CXXFLAGS) $^ -o $@
endif

ifneq ($(wildcard $(SRC_DIR)/test_avl.cpp),)
$(TEST_AVL_EXEC): $(TEST_AVL_SOURCES)
	@echo "Compiling AVL test..."
	@$(call MKDIR_P,$(OUTPUT_DIR))
	$(CXX) $(CXXFLAGS) $^ -o $@
endif

ifneq ($(wildcard $(SRC_DIR)/test_rbt.cpp),)
$(TEST_RBT_EXEC): $(TEST_RBT_SOURCES)
	@echo "Compiling RBT test..."
	@$(call MKDIR_P,$(OUTPUT_DIR))
	$(CXX) $(CXXFLAGS) $^ -o $@
endif

ifneq ($(wildcard $(SRC_DIR)/tree_stats.cpp),)
$(TREE_STATS_EXEC): $(TREE_STATS_SOURCES)
	@echo "Compiling tree stats..."
	@$(call MKDIR_P,$(OUTPUT_DIR))
	$(CXX) $(CXXFLAGS) $^ -o $@
endif

# limpa diretório e arquivos gerados
clean:
ifeq ($(OS),Windows_NT)
	-if exist "$(subst /,\,$(OUTPUT_DIR))" $(RMDIR) "$(subst /,\,$(OUTPUT_DIR))"
	-if exist "$(subst /,\,$(STAMP_FILE))" $(RM) "$(subst /,\,$(STAMP_FILE))"
else
	-$(RMDIR) $(OUTPUT_DIR)
	-$(RM) $(STAMP_FILE)
endif

.PHONY: all clean run_test run_main
