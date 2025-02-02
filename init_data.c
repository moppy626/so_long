#include "so_long.h"

void read_img(void **img, t_data *d,char *filename)
{
	int	wid;
	int	hei;

    wid = 0;
    hei = 0;
	*img = mlx_xpm_file_to_image(d->mlx, filename, &wid, &hei);
	if(!*img)
		free_and_exit("Error\n Failed to load image\n", d);
}
void set_img(t_data *d)
{
	read_img((void **)&d->img.floor, d, "./img/floor.xpm");
	read_img((void **)&d->img.wall.top, d, "./img/wall/top.xpm");
	read_img((void **)&d->img.wall.stone, d, "./img/wall/stone.xpm");
	read_img((void **)&d->img.wall.under, d, "./img/wall/under.xpm");
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
	read_img((void **)&d->img.player.goal[0], d, "./img/player/goal0.xpm");
	read_img((void **)&d->img.player.goal[1], d, "./img/player/goal1.xpm");
	read_img((void **)&d->img.player.goal[2], d, "./img/player/goal2.xpm");
	read_img((void **)&d->img.monster.left[0], d, "./img/monster/left0.xpm");
	read_img((void **)&d->img.monster.left[1], d, "./img/monster/left1.xpm");
	read_img((void **)&d->img.monster.left[2], d, "./img/monster/left2.xpm");
	read_img((void **)&d->img.monster.right[0], d, "./img/monster/right0.xpm");
	read_img((void **)&d->img.monster.right[1], d, "./img/monster/right1.xpm");
	read_img((void **)&d->img.monster.right[2], d, "./img/monster/right2.xpm");
	read_img((void **)&d->img.item, d, "./img/item.xpm");
	read_img((void **)&d->img.system.bar, d, "./img/system/bar.xpm");
	read_img((void **)&d->img.system.coin, d, "./img/system/coin.xpm");
	read_img((void **)&d->img.system.foot, d, "./img/system/foot.xpm");
	read_img((void **)&d->img.system.goalframe, d, "./img/system/goalframe.xpm");
	read_img((void **)&d->img.goal[0], d, "./img/goal/0.xpm");
	read_img((void **)&d->img.goal[1], d, "./img/goal/1.xpm");
	read_img((void **)&d->img.goal[2], d, "./img/goal/2.xpm");
	read_img((void **)&d->img.goal[3], d, "./img/goal/3.xpm");
	read_img((void **)&d->img.goal[4], d, "./img/goal/4.xpm");
	d->player.img = d->img.player.front;

}
