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
	プレイヤーを描画する
*/
void	render_player(t_data *d)
{
	my_put_image_to_window(d, d->player.img[d->player.idx],
		d->player.x, d->player.y);
}

/*
	アイテムがすべて回収されたら、出口を描画する
*/
void	render_exit(t_data *d)
{
	if (d->map->getitems == d->map->allitems && d->exit.idx < 4)
	{
		d->exit.idx = 4;
		my_put_image_to_window(d, d->img.exit[d->exit.idx],
			d->exit.x, d->exit.y);
	}
}
