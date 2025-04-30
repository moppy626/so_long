/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 22:41:25 by mmachida          #+#    #+#             */
/*   Updated: 2025/02/06 22:41:25 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_attacked(t_data *d)
{
	t_list	*enemy;

	if (d->exit.flg == 1)
		return ;
	enemy = d->vilans;
	while (enemy)
	{
		if (enemy->object.x == d->player.x && enemy->object.y == d->player.y)
		{
			d->player.flg = 1;
			d->player.img = d->img.player.damage;
			d->player.idx = 0;
			end_game(d, "Game Over.  Press Esc key.");
		}
		enemy = enemy->next;
	}
}

/*
	Place images in a position that takes the status bar into account
*/
void	my_put_image_to_window(t_data *d, void *img, ssize_t x, ssize_t y)
{
	ssize_t		nx;
	ssize_t		ny;

	nx = x * PIC_SIZE;
	ny = INFO_BER + (y * PIC_SIZE);
	mlx_put_image_to_window(d->mlx, d->win, img, nx, ny);
}

/*
	Exit the game and display a message at the top of the screen
*/
void	end_game(t_data *d, char *msg)
{
	ssize_t	x;

	d->exit.flg = 1;
	x = 0;
	while (x < d->map->column)
	{
		my_put_image_to_window(d, d->img.system.frame, x, 0);
		x++;
	}
	mlx_string_put(d->mlx, d->win, 15, 53, 0xFFFFFFFF, msg);
}

/*
	Drawing a wall.
*/
void	set_wall(t_data *d, ssize_t x, ssize_t y)
{
	if (x == 0)
		my_put_image_to_window(d, d->img.wall.top, x, y);
	else if (x == d->map->column - 1)
		my_put_image_to_window(d, d->img.wall.top, x, y);
	else if (y == d->map->row - 1)
		my_put_image_to_window(d, d->img.wall.top, x, y);
	else if (y == 0)
		my_put_image_to_window(d, d->img.wall.under, x, y);
	else
		my_put_image_to_window(d, d->img.wall.stone, x, y);
}

/*
	Drawing frames.
*/
void	init_frame(t_data *d)
{
	ssize_t	x;
	ssize_t	y;

	y = 0;
	while (y < d->map->row)
	{
		x = 0;
		while (x < d->map->column)
		{
			if (d->map->map[y][x] == WALL)
				set_wall(d, x, y);
			else if (d->map->map[y][x] == EXIT)
				my_put_image_to_window(d, d->img.exit[0], x, y);
			else if (d->map->map[y][x] == ITEM)
				my_put_image_to_window(d, d->img.item, x, y);
			else
				my_put_image_to_window(d, d->img.floor, x, y);
			x++;
		}
		y++;
	}
	render_player(d);
}
