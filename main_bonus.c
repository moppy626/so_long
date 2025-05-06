/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:56:12 by mmachida          #+#    #+#             */
/*   Updated: 2025/02/06 20:56:12 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
	上部のバーに現在のステータスを表示する
*/
void	set_bar(t_data *d)
{
	char	*str;
	ssize_t	x;
	ssize_t	loc;

	x = 0;
	while (x < d->map->column)
	{
		loc = x++ *PIC_SIZE;
		mlx_put_image_to_window(d->mlx, d->win, d->img.system.bar, loc, 0);
	}
	str = ft_itoa(d->map->count);
	mlx_string_put(d->mlx, d->win, 40, 16, 0xFFFFFFFF, str);
	free(str);
	str = ft_itoa(d->map->getitems);
	mlx_put_image_to_window(d->mlx, d->win, d->img.system.foot, 10, 3);
	mlx_string_put(d->mlx, d->win, 100, 16, 0xFFFFFFFF, str);
	free(str);
	str = ft_itoa(d->map->allitems);
	mlx_put_image_to_window(d->mlx, d->win, d->img.system.coin, 70, 3);
	mlx_string_put(d->mlx, d->win, 120, 16, 0xFFFFFFFF, "/");
	mlx_string_put(d->mlx, d->win, 130, 16, 0xFFFFFFFF, str);
	free(str);
}

/*
	キー押下がされた際、プレーヤーを動かす
*/
void	ctl_player(t_data *d, void *img, ssize_t x, ssize_t y)
{
	if (d->exit.flg == 1)
		return ;
	d->player.img = img;
	if (d->map->map[y][x] != WALL)
	{
		check_attacked(d);
		my_put_image_to_window(d, d->img.floor, d->player.x, d->player.y);
		if (d->map->map[y][x] == ITEM)
		{
			d->map->getitems++;
			d->map->map[y][x] = FLOOR;
		}
		if (d->map->map[y][x] == EXIT && d->map->getitems == d->map->allitems)
		{
			d->player.img = d->img.player.exit;
			end_game(d, "Game Clear!!  Press Esc key.");
		}
		d->map->count++;
		ft_printf("%d\n", d->map->count);
		set_bar(d);
		d->player.x = x;
		d->player.y = y;
		render_player(d);
	}
}

/*
	エスケープキー押下時・×ボタン押下時のイベント
*/
int	on_destroy(t_data *d)
{
	free_data(d);
	exit(EXIT_SUCCESS);
	return (0);
}

/*
	キー押下時のイベント
*/
int	on_keypress(int keycode, t_data *d)
{
	ssize_t	x;
	ssize_t	y;

	x = d->player.x;
	y = d->player.y;
	if (keycode == KEY_ESC)
		on_destroy(d);
	else if (keycode == KEY_W || keycode == KEY_UP)
		ctl_player(d, d->img.player.back, x, --y);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		ctl_player(d, d->img.player.left, --x, y);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		ctl_player(d, d->img.player.front, x, ++y);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		ctl_player(d, d->img.player.right, ++x, y);
	return (0);
}

/*
	メイン関数
*/
int	main(int argc, char **argv)
{
	t_data	d;
	ssize_t	width;
	ssize_t	height;

	if (argc != 2)
		fail_and_end("Error\n Not a single argument\n", &d);
	d = init_data();
	get_map(&d, argv);
	check_playable(&d);
	d.mlx = mlx_init();
	if (!d.mlx)
		end("Failed in mlx_init\n", &d);
	width = d.map->column * PIC_SIZE;
	height = INFO_BER + (d.map->row * PIC_SIZE);
	d.win = mlx_new_window(d.mlx, width, height, "so_long");
	if (!d.win)
		end("Failed in mlx_new_window\n", &d);
	road_xpm(&d);
	set_bar(&d);
	init_frame(&d);
	mlx_key_hook(d.win, on_keypress, &d);
	mlx_hook(d.win, DestroyNotify, StructureNotifyMask, on_destroy, &d);
	mlx_loop_hook(d.mlx, render_next_frame, &d);
	mlx_loop(d.mlx);
}
