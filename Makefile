#COLORS#
GREEN = \033[1;92m
RED = \033[1;91m
NC = \033[0m
YELLOW= \033[1;33m

NAME = pipex
CC = cc -g #-fsanitize=address
CFLAGS = -Wall -Werror -Wextra -MMD -I ./
RM = rm -rf

SRCS = main.c aux.c error.c utils.c
OBJS = $(SRCS:%.c=%.o)
DEPS = $(SRCS:%.c=%.d)

SRCS_LIBFT = ./libft/libft.a
MAKE_LIBFT = make -C libft

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@
#	@echo "$(YELLOW)Compiling... $(END)$(patsubst $(DIR_BUILD)%,%,$@)"

all: make_lib $(NAME)
#	@echo "$(YELLOW)Compiling... $(END)$(patsubst $(DIR_BUILD)%,%,$@)"


make_lib:
	$(MAKE_LIBFT)

-include $(DEPS)
$(NAME): $(OBJS) $(SRCS_LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(SRCS_LIBFT) -o $(NAME)
#	@echo "$(GREEN)PIPEX DONE$(END)"

clean:
	RM $(OBJS) $(DEPS)
	@$(MAKE) clean -C ./libft
	@echo "$(RED)OBJECTS DELETED$(END)"

fclean: clean
	RM $(NAME)
	@$(MAKE) fclean -C ./libft
	@echo "$(RED)EXEC DELETED $(END)"
#	NO ACABAR DE BORRAR EL .A DE LA LIBFT

re: fclean all

.PHONY: all clean fclean re
