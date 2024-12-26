# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oumondad <oumondad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/10 17:09:01 by hes-safi          #+#    #+#              #
#    Updated: 2024/12/18 17:59:49 by oumondad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3d
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -fsanitize=address -g3

MINILBX	=	mlx/libmlx_Linux.a
PATH_ML	=	mlx/

SRC		=	cub3d.c tools.c utils.c parsing.c elements.c pathing.c ft_split.c \
			moving.c draw.c runder_img.c ray_casting.c
SRC_O	=	$(SRC:.c=.o)

all: $(NAME)

$(MINILBX):
	@make -C $(PATH_MLX) > test
	@echo minilibx DONE

$(NAME): $(MINILBX) $(SRC_O)
	@echo objecte DONE
	@$(CC) $(CFLAGS) $(SRC_O) $(MINILBX) -L$(PATH_MLX) -lmlx -lXext -lX11 -lm  -o $(NAME)
	@echo $(NAME) DONE
	@rm -f test

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(SRC_O)
	@echo all objecte clean
	 
fclean: clean
	@rm -f $(NAME)
	@echo the programe clean

re: fclean all

.SECONDARY: $(SRC_O)

.PHONY: all clean fclean re test