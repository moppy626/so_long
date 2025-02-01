#include "so_long.h"

void free_map(t_map *map)
{
	ssize_t idx;

	if(map)
	{
		idx = 0;
        if(map->map)
        {
            while(idx < map->row)
            {
                if(map->map[idx])
                {
                    free(map->map[idx]);
                    map->map[idx] = NULL;
                }
                idx++;
            }
            free(map->map);
            map->map = NULL;
        }
        free(map);
        map = NULL;
	}
}
void check_and_destroyimg(void *mlx, void *img)
{
    if(img)
    {
        mlx_destroy_image(mlx, img);
        img = NULL;
    }
}
void destroy_list(void *mlx, void **list, ssize_t repeat)
{
	ssize_t idx;

    idx = 0;
    while (idx < repeat)
    {
        check_and_destroyimg(mlx, list[idx]);
        idx++;
    }
}
void free_data(t_data *d)
{
    free_map(d->map);
    check_and_destroyimg(d->mlx, d->img.floor);
    check_and_destroyimg(d->mlx, d->img.wall.top);
    check_and_destroyimg(d->mlx, d->img.wall.under);
    check_and_destroyimg(d->mlx, d->img.wall.stone);
    destroy_list(d->mlx, d->img.player.front, 3);
    destroy_list(d->mlx, d->img.player.back, 3);
    destroy_list(d->mlx, d->img.player.right, 3);
    destroy_list(d->mlx, d->img.player.left, 3);
    destroy_list(d->mlx, d->img.player.damage, 3);
    destroy_list(d->mlx, d->img.player.goal, 3);
    destroy_list(d->mlx, d->img.monster.left, 3);
    destroy_list(d->mlx, d->img.monster.right, 3);
    destroy_list(d->mlx, d->img.item, 4);
    check_and_destroyimg(d->mlx, d->img.system.bar);
    check_and_destroyimg(d->mlx, d->img.system.coin);
    check_and_destroyimg(d->mlx, d->img.system.foot);
    check_and_destroyimg(d->mlx, d->img.system.goalframe);
    destroy_list(d->mlx, d->img.goal, 5);
    if(d->win)
        mlx_clear_window(d->mlx, d->win);
    if(d->win)
	    mlx_destroy_window(d->mlx, d->win);
    if(d->mlx)
    {
        mlx_destroy_display(d->mlx);
        free(d->mlx);
    }
    while (d->enemys)
        delist(&d->enemys);
}
void fail_and_exit(char *msg, t_data *d)
{
    if(d->map)
        free(d->map);
    ft_printf(msg);
    exit(EXIT_FAILURE);
}
void free_and_exit(char *msg, t_data *d)
{
    ft_printf(msg);
    free_data(d);
    exit(EXIT_FAILURE);
}