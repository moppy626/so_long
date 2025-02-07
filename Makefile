# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/02 20:20:23 by mmachida          #+#    #+#              #
#    Updated: 2025/02/02 20:20:23 by mmachida         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = sudo cc -Wall -Wextra -Werror
NAME = so_long
BONUS_NAME = so_long_bonus
SRC = main.c free_data.c get_map.c road_xpm.c render_frame.c check_map.c init_frame.c check_playable.c init_data.c
SRC_GNL = get_next_line.c get_next_line_utils.c
SRC_PRINTF = str_funcs.c ft_strlen.c printf_funcs.c ft_printf.c
SRC_LIBFT = ft_memcpy.c ft_itoa.c

SRC_GNL := $(addprefix get_next_line/, $(SRC_GNL))
SRC_PRINTF := $(addprefix ft_printf/, $(SRC_PRINTF))
SRC_LIBFT := $(addprefix libft/, $(SRC_LIBFT))

OBJS = $(SRC:.c=.o) $(SRC_GNL:.c=.o) $(SRC_PRINTF:.c=.o) $(SRC_LIBFT:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -lmlx -lXext -lX11 -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(OBJS)
	@$(CC) $(OBJS) -lmlx -lXext -lX11 -o $(BONUS_NAME)

clean: 
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all
	