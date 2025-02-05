#include "so_long.h"

void check_attacked(t_data *d)
{
	t_list *enemy;
	if(d->goal.flg == 1)
		return;
	enemy = d->vilans;
	while(enemy)
	{
		if(enemy->object.x == d->player.x && enemy->object.y == d->player.y)
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
	ステータスバーを考慮した位置に画像を配置する
*/
void my_put_image_to_window(t_data *d, void *img, ssize_t x, ssize_t y)
{
	mlx_put_image_to_window(d->mlx, d->win, img, x * PIC_SIZE, INFO_BER + (y * PIC_SIZE));
}

/*
	ゲームを終了し、画面上部にメッセージを表示する
*/
void end_game(t_data *d, char *msg)
{
	ssize_t x;

	d->goal.flg = 1;
	x = 0;
	while(x < d->map->column)
	{
		my_put_image_to_window(d, d->img.system.goalframe, x, 0);
		x++;
	}
	mlx_string_put(d->mlx, d->win, 15, 53, 0xFFFFFFFF, msg);
}
/*
	壁の描画を行う
*/
void set_wall(t_data *d, ssize_t x, ssize_t y)
{
	if (x == 0)
		my_put_image_to_window(d, d->img.wall.top, x, y);
	else if(x == d->map->column - 1)
		my_put_image_to_window(d, d->img.wall.top, x, y);
	else if(y == d->map->row - 1)
		my_put_image_to_window(d, d->img.wall.top, x, y);
	else if(y == 0)
		my_put_image_to_window(d, d->img.wall.under, x, y);
	else
		my_put_image_to_window(d, d->img.wall.stone, x, y);
}

/*
	フレームの描画を行う
*/
void init_frame(t_data *d)
{
	ssize_t x;
	ssize_t y;

	y = 0;
	while (y < d->map->row)
	{
		x = 0;
		while(x < d->map->column)
		{
			if(d->map->map[y][x] == WALL)
				set_wall(d, x, y);
			else if(d->map->map[y][x] == EXIT)
				my_put_image_to_window(d, d->img.goal[0], x, y);
			else if(d->map->map[y][x] == ITEM)
				my_put_image_to_window(d, d->img.item, x, y);
			else
				my_put_image_to_window(d, d->img.floor, x, y);
			x++;
		}
		y++;
	}
	render_player(d);
}