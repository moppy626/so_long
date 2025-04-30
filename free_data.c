/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:11:54 by mmachida          #+#    #+#             */
/*   Updated: 2025/02/06 21:11:54 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
	Release the loaded map data.
*/
void	free_map(t_map *map)
{
	ssize_t	idx;

	if (map)
	{
		idx = 0;
		if (map->map)
		{
			while (idx < map->row)
			{
				if (map->map[idx])
				{
					free(map->map[idx]);
					map->map[idx] = NULL;
				}
				idx++;
			}
			free(map->map);
			map->map = NULL;
		}
		free(map);
		map = NULL;
	}
}

/*
	Discard loaded images
*/
void	check_and_destroyimg(void *mlx, void *img)
{
	if (img)
	{
		mlx_destroy_image(mlx, img);
		img = NULL;
	}
}

/*
	Discard images loaded in the list
*/
void	destroy_list(void *mlx, void **list, ssize_t repeat)
{
	ssize_t	idx;

	idx = 0;
	while (idx < repeat)
	{
		check_and_destroyimg(mlx, list[idx]);
		idx++;
	}
}

/*
	Free up memory reserved for mlx tools
*/
void	free_mlx_tools(t_data *d)
{
	if (d->win)
		mlx_clear_window(d->mlx, d->win);
	if (d->win)
		mlx_destroy_window(d->mlx, d->win);
	if (d->mlx)
	{
		mlx_destroy_display(d->mlx);
		free(d->mlx);
	}
}

/*
	Release data that has been read
*/
void	free_data(t_data *d)
{
	free_map(d->map);
	check_and_destroyimg(d->mlx, d->img.floor);
	check_and_destroyimg(d->mlx, d->img.wall.top);
	check_and_destroyimg(d->mlx, d->img.wall.under);
	check_and_destroyimg(d->mlx, d->img.wall.stone);
	destroy_list(d->mlx, d->img.player.front, 3);
	destroy_list(d->mlx, d->img.player.back, 3);
	destroy_list(d->mlx, d->img.player.right, 3);
	destroy_list(d->mlx, d->img.player.left, 3);
	destroy_list(d->mlx, d->img.player.damage, 3);
	destroy_list(d->mlx, d->img.player.exit, 3);
	destroy_list(d->mlx, d->img.vilan.left, 3);
	destroy_list(d->mlx, d->img.vilan.right, 3);
	check_and_destroyimg(d->mlx, d->img.item);
	check_and_destroyimg(d->mlx, d->img.system.bar);
	check_and_destroyimg(d->mlx, d->img.system.coin);
	check_and_destroyimg(d->mlx, d->img.system.foot);
	check_and_destroyimg(d->mlx, d->img.system.frame);
	destroy_list(d->mlx, d->img.exit, 5);
	while (d->vilans)
		get_from_list(&d->vilans);
	free_mlx_tools(d);
}
