# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/03 20:55:24 by mikim             #+#    #+#              #
#    Updated: 2017/07/05 21:45:16 by mikim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c \
	  ft_ls.c \
	  sort_file.c \
	  get_lsflag.c \
	  get_file.c \
	  get_param.c \
	  print_col.c \
	  print_one.c \
	  print_long.c \
	  print_permission.c \
	  print_id.c \
	  print_time.c \
	  print_name.c \
	  message.c
	  
OBJ = $(SRC:.c=.o)

SRCDIR = srcs
OBJDIR = objs
LIBDIR = libft

SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(OBJ))
LIBS = -L $(LIBDIR) -lft
HEADER = -I includes -I $(LIBDIR)/includes

CC = gcc
CFLAGS = -c -Wall -Wextra -Werror

NAME = ft_ls

.PHONY: all clean fclean re
.SUFFIXES: .c .o

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(HEADER) $< -o $@

$(NAME): $(OBJS)
	@make -C $(LIBDIR)
	@$(CC) $(OBJS) $(LIBS) -o $@
	@echo "[Ft_Ls - 모래반지 빵야빵야!]"

clean:
	@/bin/rm -rf $(OBJDIR)
	@make -C $(LIBDIR) clean
	@echo "[Ft_Ls - clean]"

fclean: clean
	@/bin/rm -f $(NAME)
	@rm -f $(LIBDIR)/libft.a
	@echo "[Ft_Ls - fclean]"

re: fclean all
