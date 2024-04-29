#COLORS#
GREEN = \033[1;92m
RED = \033[1;91m
NC = \033[0m
YELLOW= \033[1;33m

NAME = pipex
CC = cc -g #-fsanitize=address
CFLAGS = -Wall -Werror -Wextra -MMD -I ./
RM = rm -rf

SRCS = main.c aux.c error.c utils.c process.c
OBJS = $(SRCS:%.c=%.o)
DEPS = $(SRCS:%.c=%.d)

SRCS_LIBFT = ./libft/libft.a
MAKE_LIBFT = make -C libft

%.o: %.c Makefile
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(YELLOW)Compiling... $(END)$(patsubst $(DIR_BUILD)%,%,$@)"

all: make_lib $(NAME)

make_lib:
	@$(MAKE_LIBFT) --no-print-directory

-include $(DEPS)
$(NAME): $(OBJS) $(SRCS_LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(SRCS_LIBFT) -o $(NAME)
	@echo "$(GREEN)PIPEX DONE$(END)"

clean:
	@$(RM) $(OBJS) $(DEPS)
	@$(MAKE) -C ./libft clean --no-print-directory
	@echo "$(RED)OBJECTS DELETED$(END)"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C ./libft fclean --no-print-directory
	@echo "$(RED)EXEC DELETED $(END)"

re: fclean all

.PHONY: all clean fclean re
