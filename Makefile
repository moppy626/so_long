CC = sudo cc -Wall -Wextra -Werror
NAME = so_long
SRC = main.c free_data.c get_map.c init_data.c render_frame.c check_map.c
SRC_GNL = get_next_line.c get_next_line_utils.c
SRC_PRINTF = str_funcs.c ft_strlen.c printf_funcs.c ft_printf.c
SRC_LIBFT = ft_memcpy.c ft_itoa.c

SRC_GNL := $(addprefix get_next_line/, $(SRC_GNL))
SRC_PRINTF := $(addprefix ft_printf/, $(SRC_PRINTF))
SRC_LIBFT := $(addprefix libft/, $(SRC_LIBFT))

all: $(SRC_GNL) $(SRC_PRINTF) $(SRC_LIBFT) $(SRC) 
	@$(CC) $(SRC_LIBFT) $(SRC) $(SRC_GNL) $(SRC_PRINTF) -lmlx -lXext -lX11 -o $(NAME)

crean: $(SRC_GNL) $(SRC_PRINTF) $(SRC_LIBFT) $(SRC) 
	rm -rf 

fclean:

re:
# play: all
# 	valgrind --leak-check=full -s ./a.out "map/map.ber"

	