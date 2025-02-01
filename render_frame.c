#include "so_long.h"

void my_put_image_to_window(t_data *d, void *img, ssize_t x, ssize_t y)
{
	mlx_put_image_to_window(d->mlx, d->win, img, x * PIC_SIZE, INFO_BER + (y * PIC_SIZE));
}
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
void render_player(t_data *d)
{
	ft_printf("d->player.flg=%d,d->player.idx=%d \n",d->player.flg,d->player.idx);
	if (d->player.idx >= 3)
		if(d->player.flg == 1)
			return;
		else
			d->player.idx = 0;
	my_put_image_to_window(d, d->player.img[d->player.idx], d->player.x, d->player.y);
	d->player.idx++;
}
void init_frame(t_data *d)
{
	ssize_t x;
	ssize_t y;
	ssize_t item_cnt;

	y = 0;
	item_cnt = 0;
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
				my_put_image_to_window(d, d->img.item[item_cnt++%3] , x, y);
			else
				my_put_image_to_window(d, d->img.floor, x, y);
			x++;
		}
		y++;
	}
	render_player(d);
}
void render_goal(t_data *d)
{
	if(d->map->getitems == d->map->allitems && d->goal.idx < 5)
	{
		my_put_image_to_window(d, d->img.goal[d->goal.idx] , d->goal.x, d->goal.y);
		d->goal.idx++;
	}
}
void render_vilans(t_data *d)
{
	t_list *enemy;
	ssize_t x;

	if(d->goal.flg == 1)
		return;
	enemy = d->enemys;
	while(enemy)
	{
		if(enemy->object.x == d->player.x && enemy->object.y == d->player.y)
		{
			d->player.flg = 1;
			d->player.img = d->img.player.damage;
			d->player.idx = 0;
			end_game(d, "Game Over.  Press Esc key.");
		}
		ft_printf("vilan=x:%d,y:%d\n",enemy->object.x, enemy->object.y);
		if(enemy->object.flg == 0)
			if(d->map->map[enemy->object.y][enemy->object.x + 1] != WALL)
			{
				my_put_image_to_window(d, d->img.floor, enemy->object.x, enemy->object.y);
				enemy->object.x = enemy->object.x + 1;
			}
			else
			{
				enemy->object.flg = 1;
				enemy->object.img = d->img.monster.left;
			}
		else
			if(d->map->map[enemy->object.y][enemy->object.x - 1] != WALL)
			{
				my_put_image_to_window(d, d->img.floor, enemy->object.x, enemy->object.y);
				enemy->object.x = enemy->object.x - 1;
			}
			else
			{
				enemy->object.flg = 0;
				enemy->object.img = d->img.monster.right;
			}
		my_put_image_to_window(d, enemy->object.img[enemy->object.idx], enemy->object.x, enemy->object.y);
		enemy->object.idx++;
		if (enemy->object.idx >= 3)
			enemy->object.idx = 0;
		enemy = enemy->next;
	}
}
int render_next_frame(t_data *d)
{
	static ssize_t render = 0;

	if (render <= 0)
	{
		render_goal(d);
		render_vilans(d);
		render_player(d);
		render = 1000;
	}
	render--;
}