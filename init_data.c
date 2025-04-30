/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 21:06:58 by mmachida          #+#    #+#             */
/*   Updated: 2025/02/07 21:06:58 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
	Initialize array
*/
void	init_array(void **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
		array[i++] = NULL;
}

/*
	Initialize image holding area
*/
void	init_img(t_img	*img)
{
	img->floor = NULL;
	img->item = NULL;
	init_array((void **)img->exit, 5);
	img->wall.top = NULL;
	img->wall.stone = NULL;
	img->wall.under = NULL;
	init_array((void **)img->player.back, 3);
	init_array((void **)img->player.front, 3);
	init_array((void **)img->player.left, 3);
	init_array((void **)img->player.right, 3);
	init_array((void **)img->player.damage, 3);
	init_array((void **)img->player.exit, 3);
	init_array((void **)img->vilan.left, 3);
	init_array((void **)img->vilan.right, 3);
	img->system.bar = NULL;
	img->system.coin = NULL;
	img->system.foot = NULL;
	img->system.frame = NULL;
}

/*
	Initialize data retention area
*/
t_data	init_data(void)
{
	t_data	d;

	d.mlx = NULL;
	d.win = NULL;
	d.map = NULL;
	init_img(&d.img);
	d.player.img = NULL;
	d.player.x = 0;
	d.player.y = 0;
	d.player.flg = 0;
	d.player.idx = 0;
	d.exit.img = NULL;
	d.exit.x = 0;
	d.exit.y = 0;
	d.exit.flg = 0;
	d.exit.idx = 0;
	d.vilans = NULL;
	return (d);
}
