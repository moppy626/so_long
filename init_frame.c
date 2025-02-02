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