
SRC_FILES := main.c \
    util.c \
    parse.c \
    init_parse.c \
    builtins.c \
    list.c

INCLUDE_PATH := 

MODULE_NAME := parse_config

OBJ_PATH := bin/

OBJ_FILES := $(addsuffix .o, $(addprefix $(OBJ_PATH), $(basename $(SRC_FILES))))

$(OBJ_PATH)%.o: %.c
	@mkdir -p $(OBJ_PATH)$(dir $<)
	gcc -c $< -o $@

$(MODULE_NAME): $(OBJ_FILES)
	gcc $^ -o $@
	@echo "build over"

PHONY: clean
clean:
	@rm -rf $(OBJ_PATH)
	@rm -f $(MODULE_NAME)