/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:35:16 by mmachida          #+#    #+#             */
/*   Updated: 2025/02/06 21:35:16 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <X11/X.h>
# include <fcntl.h>
# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line.h"

# define FLOOR		'0'
# define WALL		'1'
# define PLAYER		'P'
# define EXIT		'E'
# define ITEM		'C'
# define VILAN		'V'
# define KEY_ESC	65307
# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100
# define KEY_UP		65362
# define KEY_LEFT	65361
# define KEY_DOWN	65364
# define KEY_RIGHT	65363
# define PIC_SIZE	48
# define INFO_BER	24

typedef struct s_object
{
	void			**img;
	ssize_t			x;
	ssize_t			y;
	ssize_t			flg;
	ssize_t			idx;
}	t_object;
typedef struct s_list {
	t_object		object;
	struct s_list	*next;
}	t_list;
typedef struct s_vilan
{
	void			*left[3];
	void			*right[3];
}	t_vilan;
typedef struct s_player
{
	void			*back[3];
	void			*front[3];
	void			*left[3];
	void			*right[3];
	void			*damage[3];
	void			*exit[3];
}	t_player;

typedef struct s_wall
{
	void			*top;
	void			*stone;
	void			*under;
}	t_wall;

typedef struct s_system
{
	void			*bar;
	void			*coin;
	void			*foot;
	void			*frame;
}	t_system;

typedef struct s_img
{
	void			*floor;
	void			*item;
	void			*exit[5];
	t_wall			wall;
	t_player		player;
	t_vilan			vilan;
	t_system		system;
}	t_img;

typedef struct s_map
{
	char			**map;
	ssize_t			row;
	ssize_t			column;
	ssize_t			allitems;
	ssize_t			getitems;
	ssize_t			count;
}	t_map;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	t_map			*map;
	t_img			img;
	t_object		player;
	t_object		exit;
	t_list			*vilans;
}	t_data;

void		check_map(t_data *d);
void		free_data(t_data *d);
void		fail_and_end(char *msg, t_data *d);
void		end(char *msg, t_data *d);
void		get_map(t_data *d, char **argv);
void		road_xpm(t_data *d);
void		init_frame(t_data *d);
void		my_put_image_to_window(t_data *d, void *img, ssize_t x, ssize_t y);
int			render_next_frame(t_data *data);
void		render_player(t_data *d);
void		check_playable(t_data *d);
void		end_game(t_data *d, char *msg);
void		add_list(t_list **head, ssize_t x, ssize_t y, void *img);
t_object	get_from_list(t_list **head);
void		check_attacked(t_data *d);
t_data		init_data(void);
int			check_ext(char *str, char *ext);
void		render_exit(t_data *d);

#endif