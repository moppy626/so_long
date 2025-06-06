/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   road_xpm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:55:07 by mmachida          #+#    #+#             */
/*   Updated: 2025/02/06 20:55:07 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
	mlx_xpm_file_to_imageを使用し、
	その戻り値がNULLの場合エラー処理を行います
*/
void	read_img(void **img, t_data *d, char *filename)
{
	int	wid;
	int	hei;

	wid = 0;
	hei = 0;
	*img = mlx_xpm_file_to_image(d->mlx, filename, &wid, &hei);
	if (!*img)
		end("Error\n Failed to load image\n", d);
}

/*
	プレイヤーの画像を読み込みます
*/
void	set_player_img(t_data *d)
{
	read_img((void **)&d->img.player.front[0], d, "./img/player/front0.xpm");
	read_img((void **)&d->img.player.front[1], d, "./img/player/front1.xpm");
	read_img((void **)&d->img.player.front[2], d, "./img/player/front2.xpm");
	read_img((void **)&d->img.player.back[0], d, "./img/player/back0.xpm");
	read_img((void **)&d->img.player.back[1], d, "./img/player/back1.xpm");
	read_img((void **)&d->img.player.back[2], d, "./img/player/back2.xpm");
	read_img((void **)&d->img.player.right[0], d, "./img/player/right0.xpm");
	read_img((void **)&d->img.player.right[1], d, "./img/player/right1.xpm");
	read_img((void **)&d->img.player.right[2], d, "./img/player/right2.xpm");
	read_img((void **)&d->img.player.left[0], d, "./img/player/left0.xpm");
	read_img((void **)&d->img.player.left[1], d, "./img/player/left1.xpm");
	read_img((void **)&d->img.player.left[2], d, "./img/player/left2.xpm");
	read_img((void **)&d->img.player.damage[0], d, "./img/player/damage0.xpm");
	read_img((void **)&d->img.player.damage[1], d, "./img/player/damage1.xpm");
	read_img((void **)&d->img.player.damage[2], d, "./img/player/damage2.xpm");
	read_img((void **)&d->img.player.exit[0], d, "./img/player/exit0.xpm");
	read_img((void **)&d->img.player.exit[1], d, "./img/player/exit1.xpm");
	read_img((void **)&d->img.player.exit[2], d, "./img/player/exit2.xpm");
}

/*
	パトロールの初期状態を設定する
*/
void	set_vilans(t_data *d, t_list **list, char stracture, void *img)
{
	ssize_t	x;
	ssize_t	y;

	if (!d || !d->map || !d->map->map)
		end("Error\n Failed in set_vilans\n", d);
	x = 0;
	while (x < d->map->column)
	{
		y = 0;
		while (y < d->map->row)
		{
			if (d->map->map[y][x] == stracture)
			{
				add_list(list, x, y, img);
			}
			y++;
		}
		x++;
	}
}

/*
	描画に必要な画像を読み込みます
*/
void	road_xpm(t_data *d)
{
	read_img((void **)&d->img.floor, d, "./img/floor.xpm");
	read_img((void **)&d->img.wall.top, d, "./img/wall/top.xpm");
	read_img((void **)&d->img.wall.stone, d, "./img/wall/stone.xpm");
	read_img((void **)&d->img.wall.under, d, "./img/wall/under.xpm");
	read_img((void **)&d->img.vilan.left[0], d, "./img/vilan/left0.xpm");
	read_img((void **)&d->img.vilan.left[1], d, "./img/vilan/left1.xpm");
	read_img((void **)&d->img.vilan.left[2], d, "./img/vilan/left2.xpm");
	read_img((void **)&d->img.vilan.right[0], d, "./img/vilan/right0.xpm");
	read_img((void **)&d->img.vilan.right[1], d, "./img/vilan/right1.xpm");
	read_img((void **)&d->img.vilan.right[2], d, "./img/vilan/right2.xpm");
	read_img((void **)&d->img.item, d, "./img/item.xpm");
	read_img((void **)&d->img.system.bar, d, "./img/system/bar.xpm");
	read_img((void **)&d->img.system.coin, d, "./img/system/coin.xpm");
	read_img((void **)&d->img.system.foot, d, "./img/system/foot.xpm");
	read_img((void **)&d->img.system.frame, d, "./img/system/frame.xpm");
	read_img((void **)&d->img.exit[0], d, "./img/exit/0.xpm");
	read_img((void **)&d->img.exit[1], d, "./img/exit/1.xpm");
	read_img((void **)&d->img.exit[2], d, "./img/exit/2.xpm");
	read_img((void **)&d->img.exit[3], d, "./img/exit/3.xpm");
	read_img((void **)&d->img.exit[4], d, "./img/exit/4.xpm");
	set_player_img(d);
	d->player.img = d->img.player.front;
	set_vilans(d, &d->vilans, VILAN, d->img.vilan.right);
}
