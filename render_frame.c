#include "so_long.h"

void render_player(t_data *d)
{
	if (d->player.idx >= 3)
		if(d->player.flg == 1)
			return;
		else
			d->player.idx = 0;
	my_put_image_to_window(d, d->player.img[d->player.idx], d->player.x, d->player.y);
	d->player.idx++;
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
		if(enemy->object.flg == 0)
			if(d->map->map[enemy->object.y][enemy->object.x + 1] == WALL
			  || (d->map->map[enemy->object.y][enemy->object.x + 1] == EXIT && d->map->getitems == d->map->allitems))
			{
				enemy->object.flg = 1;
				enemy->object.img = d->img.monster.left;
			}
			else
			{
				if(d->map->map[enemy->object.y][enemy->object.x] == ITEM)
					my_put_image_to_window(d, d->img.item, enemy->object.x, enemy->object.y);
				else
					my_put_image_to_window(d, d->img.floor, enemy->object.x, enemy->object.y);
				enemy->object.x = enemy->object.x + 1;
			}
		else
			if(d->map->map[enemy->object.y][enemy->object.x - 1] == WALL
			  || (d->map->map[enemy->object.y][enemy->object.x - 1] == EXIT && d->map->getitems == d->map->allitems))
			{
				enemy->object.flg = 0;
				enemy->object.img = d->img.monster.right;
			}
			else
			{
				if(d->map->map[enemy->object.y][enemy->object.x] == ITEM)
					my_put_image_to_window(d, d->img.item, enemy->object.x, enemy->object.y);
				else
					my_put_image_to_window(d, d->img.floor, enemy->object.x, enemy->object.y);
				enemy->object.x = enemy->object.x - 1;
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