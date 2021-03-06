include CONFIG.cfg

.PHONY: all check clean

CC = gcc
EXEC_FILE = $(BUILD_DIR)/$(NAME)
OBJECTS = $(BUILD_DIR)/main.o $(BUILD_DIR)/sorting.o $(BUILD_DIR)/manage_strings.o
INPUTS = $(patsubst $(TEST_DIR)/%.in, $(TEST_DIR)/%.log, $(wildcard $(TEST_DIR)/*.in))

all: $(EXEC_FILE)

$(EXEC_FILE) : $(OBJECTS) | $(BUILD_DIR)
	$(CC) $^ -o $@

$(OBJECTS): $(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c | $(BUILD_DIR)
	$(CC) -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $@


check: $(INPUTS)

$(TEST_DIR)/%.log: $(TEST_DIR)/%.in $(EXEC_FILE)
	@$(EXEC_FILE) $< >$@
	@if cmp $@ $(TEST_DIR)/$*.out; then \
        echo "Test $< - OK"; \
    else \
        echo "Test $< - FAILED"; \
        exit 1; \
    fi


clean:
	$(RM) $(OBJECTS) $(INPUTS) $(BUILD_DIR)/$(NAME)