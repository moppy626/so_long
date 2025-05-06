/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:57:03 by mmachida          #+#    #+#             */
/*   Updated: 2025/02/06 20:57:03 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
	敵のパトロールを動かす
*/
void	move_vilan(t_data *d, t_list *enemy, int next)
{
	if (d->map->map[enemy->object.y][enemy->object.x + next] == WALL
		|| (d->map->map[enemy->object.y][enemy->object.x + next] == EXIT
			&& d->map->getitems == d->map->allitems))
	{
		if (next == 1)
		{
			enemy->object.flg = 1;
			enemy->object.img = d->img.vilan.left;
		}
		else
		{
			enemy->object.flg = 0;
			enemy->object.img = d->img.vilan.right;
		}
	}
	else
	{
		if (d->map->map[enemy->object.y][enemy->object.x] == ITEM)
			my_put_image_to_window(d, d->img.item,
				enemy->object.x, enemy->object.y);
		else
			my_put_image_to_window(d, d->img.floor,
				enemy->object.x, enemy->object.y);
		enemy->object.x = enemy->object.x + next;
	}
}

/*
	敵のパトロールを描画する
*/
void	render_vilans(t_data *d)
{
	t_list	*enemy;

	if (d->exit.flg == 1)
		return ;
	enemy = d->vilans;
	while (enemy)
	{
		if (enemy->object.flg == 0)
			move_vilan(d, enemy, +1);
		else
			move_vilan(d, enemy, -1);
		my_put_image_to_window(d, enemy->object.img[enemy->object.idx],
			enemy->object.x, enemy->object.y);
		enemy->object.idx++;
		if (enemy->object.idx >= 3)
			enemy->object.idx = 0;
		enemy = enemy->next;
	}
}

/*
	プレイヤーを描画する
*/
void	render_player(t_data *d)
{
	if (d->player.idx >= 3)
	{
		if (d->player.flg == 1)
			return ;
		else
			d->player.idx = 0;
	}
	my_put_image_to_window(d, d->player.img[d->player.idx],
		d->player.x, d->player.y);
	d->player.idx++;
}

/*
	アイテムがすべて回収されたら、出口を描画する
*/
void	render_exit(t_data *d)
{
	if (d->map->getitems == d->map->allitems && d->exit.idx < 5)
	{
		my_put_image_to_window(d, d->img.exit[d->exit.idx],
			d->exit.x, d->exit.y);
		d->exit.idx++;
	}
}

/*
	レンダリングを行う
*/
int	render_next_frame(t_data *d)
{
	static int	render = 0;

	if (render <= 0)
	{
		render_exit(d);
		check_attacked(d);
		render_vilans(d);
		render_player(d);
		render = 1000;
	}
	render--;
	return (0);
}
