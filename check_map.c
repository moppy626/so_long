/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:51:44 by mmachida          #+#    #+#             */
/*   Updated: 2025/02/06 20:51:44 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
	リストにデータを追加する
*/
void	add_list(t_list **head, ssize_t x, ssize_t y, void *img)
{
	t_list	*new_node;
	t_list	*temp;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->object.x = x;
	new_node->object.y = y;
	new_node->object.flg = 0;
	new_node->object.idx = 0;
	new_node->next = NULL;
	if (img)
		new_node->object.img = img;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

/*
	リストからデータを取り出す
*/
t_object	get_from_list(t_list **head)
{
	t_list		*temp;
	t_object	object;

	temp = *head;
	object = temp->object;
	*head = temp->next;
	free(temp);
	return (object);
}

/*
　読み込んだ文字の1行の長さを取得する
*/
ssize_t	check_len(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != '\n' && s[len] != '\r')
		len++;
	return (len);
}

/*
　パラメタで指定された要素の数をカウントする
*/
ssize_t	count_object(t_data *d, t_object *t, char object)
{
	ssize_t	x;
	ssize_t	y;
	ssize_t	itemcnt;

	x = 0;
	itemcnt = 0;
	while (x < d->map->column)
	{
		y = 0;
		while (y < d->map->row)
		{
			if (d->map->map[y][x] == object)
			{
				if (t)
				{
					t->x = x;
					t->y = y;
				}
				itemcnt++;
			}
			y++;
		}
		x++;
	}
	return (itemcnt);
}

/*
	マップが規則に合ったものか確認する
*/
void	check_map(t_data *d)
{
	ssize_t	i;

	i = 0;
	d->map->column = check_len(d->map->map[i++]);
	while (i < d->map->row)
		if (d->map->column != check_len(d->map->map[i++]))
			end("Error\n  The map must be rectangular\n", d);
	i = 0;
	while (i < d->map->column)
		if (d->map->map[0][i] != WALL
			|| d->map->map[d->map->row - 1][i++] != WALL)
			end("Error\n  The map must be closed/surrounded by walls\n", d);
	i = 0;
	while (i < d->map->row)
		if (d->map->map[i][0] != WALL
		|| d->map->map[i++][d->map->column -1] != WALL)
			end("Error\n  The map must be closed/surrounded by walls\n", d);
	if (count_object(d, &d->player, PLAYER) != 1)
		end("Error\n  The map must contain 1 starting position\n", d);
	if (count_object(d, &d->exit, EXIT) != 1)
		end("Error\n  The map must contain 1 exit\n", d);
	d->map->allitems = count_object(d, NULL, ITEM);
	if (d->map->allitems < 1)
		end("Error\n  The map must contain at least 1 collectible\n", d);
}
