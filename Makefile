# Executable name
NAME =					miniRT

# Project's build path
BUILD_PATH =			./obj

# Compiler shell command
COMPILER =				gcc

# Compiler's flags
COMPILE_FLAGS =			-O0 -g3 -std=c99 -Wall -Werror -Wextra

# Compiler's includes flags (e.g. -I includes -I my_lib/includes)
INCLUDE_FLAGS =			-I includes \
						-I libraries/minilibx-linux \
						-I libraries/libft \
						-I libraries/libgnl

# Include files involved in project (needed for Makefile's recompilation check)
INCLUDE_FILES =			includes/parsing.h \
						includes/world.h

# Sources root path
SOURCES_PATH =			./sources

# Sources files list from root source path
SOURCE_FILE_PATHS =	main.c \
					parsing/display_parsing.c \
					parsing/elements/parse_ambient.c \
					parsing/elements/parse_camera.c \
					parsing/parsing.c

# Local libraries root paths that need to be compiled (e.g. ./lib/mylib)
LOCAL_LIBRARY_PATHS =	libraries/minilibx-linux \
						libraries/libft \
						libraries/libgnl

# Compiler's libraries flags (e.g. -L ./lib/my_lib/bin -L ./lib/my_other_lib/bin)
LIBRARY_BIN_PATHS =		-L libraries/minilibx-linux \
						-L libraries/libft \
						-L libraries/libgnl

# Flags used at linking time (e.g. -lm -lssl -lssh)
LINKER_FLAGS =			-lm -lmlx -lft -lgnl


################################################################################

OBJECT_FILES =   $(SOURCE_FILE_PATHS:%.c=$(BUILD_PATH)/%.o)

$(NAME): $(OBJECT_FILES)
	$(foreach lib,$(LOCAL_LIBRARY_PATHS),make -j8 -C $(lib);)
	$(COMPILER) -o $(NAME) $(OBJECT_FILES) $(LIBRARY_BIN_PATHS) $(LINKER_FLAGS)

all: $(NAME)

$(BUILD_PATH)/%.o: $(SOURCES_PATH)/%.c $(INCLUDE_FILES)
	@mkdir -p $(dir $@)
	$(COMPILER) $(COMPILE_FLAGS) -o $@ -c $< $(INCLUDE_FLAGS)

c: clean
clean:
	make clean -C libraries/minilibx-linux
	make clean -C libraries/libft
	make clean -C libraries/libgnl
	rm -rf $(OBJECT_FILES) $(OBJECT_FILES)

fclean: clean
	make fclean -C libraries/libft
	make fclean -C libraries/libgnl
	rm -rf $(BUILD_PATH)

re: fclean all

.PHONY: all clean fclean re