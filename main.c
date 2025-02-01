#include "so_long.h"

int on_destroy(t_data *d)
{
    free_data(d);
	exit(EXIT_SUCCESS);
    return(0);
}
void clear_bar(t_data *d)
{
	ssize_t x;

	x = 0;
	while(x < d->map->column)
	{
		mlx_put_image_to_window(d->mlx, d->win, d->img.system.bar, x * PIC_SIZE, 0);
		x++;
	}
}
void set_bar(t_data *d)
{
	char *count;
	char *getitems;
	char *allitems;

	
	clear_bar(d);
	ft_printf("%d\n", d->map->count);
	count = ft_itoa(d->map->count++);
	getitems = ft_itoa(d->map->getitems);
	allitems = ft_itoa(d->map->allitems);
	mlx_put_image_to_window(d->mlx, d->win, d->img.system.foot, 10, 3);
	mlx_string_put(d->mlx, d->win, 40, 16, 0xFFFFFFFF, count);
	mlx_put_image_to_window(d->mlx, d->win, d->img.system.coin, 70, 3);
	mlx_string_put(d->mlx, d->win, 100, 16, 0xFFFFFFFF, getitems);
	mlx_string_put(d->mlx, d->win, 120, 16, 0xFFFFFFFF, "/");
	mlx_string_put(d->mlx, d->win, 130, 16, 0xFFFFFFFF, allitems);
	free(count);
	free(getitems);
	free(allitems);
}
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
void ctl_player(t_data *d, void *img, ssize_t x, ssize_t y)
{
	if (d->goal.flg == 1)
		return ;
	d->player.img = img;
	if(d->map->map[y][x] != WALL)
	{
		my_put_image_to_window(d, d->img.floor, d->player.x, d->player.y);
		if(d->map->map[y][x] == ITEM)
		{
			d->map->getitems++;
			d->map->map[y][x] = FLOOR;
		}
		if(d->map->map[y][x] == EXIT && d->map->getitems == d->map->allitems)
		{
			d->player.img = d->img.player.goal;
			end_game(d, "Game Clear!!  Press Esc key.");
		}
		set_bar(d);
		d->player.x = x;
		d->player.y = y;
		render_player(d);
	}
}
int on_keypress(int keycode, t_data *d)
{
	ssize_t x;
	ssize_t y;

	x = d->player.x;
	y = d->player.y;
	if(keycode == KEY_ESC)
		on_destroy(d);
	else if(keycode == KEY_W || keycode == KEY_UP)
		ctl_player(d, d->img.player.back, x, --y);
	else if(keycode == KEY_A || keycode == KEY_LEFT)
		ctl_player(d, d->img.player.left, --x, y);
	else if(keycode == KEY_S || keycode == KEY_DOWN)
		ctl_player(d, d->img.player.front, x, ++y);
	else if(keycode == KEY_D || keycode == KEY_RIGHT)
		ctl_player(d, d->img.player.right, ++x, y);
    return (0);
}
void set_object(t_data *d, t_object *t, char stracture)
{
	ssize_t x;
	ssize_t y;

    if (!d || !d->map || !d->map->map)
        free_and_exit("Error\n Failed in set_object\n", d);
	x = 0;
	t->flg = 0;
	t->idx = 0;
	while (x < d->map->column)
	{
		y = 0;
		while(y < d->map->row)
		{
			if(d->map->map[y][x] == stracture)
			{
				t->x = x;
				t->y = y;
			}
			y++;
		}
		x++;
	}
}
void set_vilans(t_data *d, t_list **list, void *img)
{
	ssize_t x;
	ssize_t y;

    if (!d || !d->map || !d->map->map)
        free_and_exit("Error\n Failed in set_object\n", d);
	x = 0;
	while (x < d->map->column)
	{
		y = 0;
		while(y < d->map->row)
		{
			if(d->map->map[y][x] == VILAN)
			{
				enlist(list, x, y, img);
			}
			y++;
		}
		x++;
	}
}

int main(int argc, char **argv)
{
    t_data d = {0};

    if (argc != 2)
        fail_and_exit("Error\n Not a single argument\n", &d);
    get_map(&d, argc, argv);
	set_object(&d, &d.player, PLAYER);
	set_object(&d, &d.goal, EXIT);
	check_reachable(&d);
	d.mlx = mlx_init();
	if (!d.mlx)
	    free_and_exit("Failed in mlx_init\n", &d);
	d.win = mlx_new_window(d.mlx, d.map->column * PIC_SIZE, INFO_BER + (d.map->row * PIC_SIZE), "so_long");
	if (!d.win)
	    free_and_exit("Failed in mlx_new_window\n", &d);
	set_img(&d);
	set_vilans(&d, &d.enemys, &d.img.monster.right);
	set_bar(&d);
	init_frame(&d);
	mlx_key_hook(d.win, on_keypress, &d);
	mlx_hook(d.win, DestroyNotify, StructureNotifyMask, on_destroy, &d);
	mlx_loop_hook(d.mlx, render_next_frame, &d);
    mlx_loop(d.mlx);
}
