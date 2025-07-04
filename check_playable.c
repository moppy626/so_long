/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_playable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 19:45:36 by mmachida          #+#    #+#             */
/*   Updated: 2025/02/04 19:45:36 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
	探索済みかどうかを示すマップを初期化する
*/
int	initialize_visitedmap(t_data *d, int ***visited)
{
	int	i;
	int	j;

	i = 0;
	*visited = (int **)malloc(d->map->row * sizeof(int *));
	if (!*visited)
		return (-1);
	while (i < d->map->row)
	{
		j = 0;
		(*visited)[i] = (int *)malloc(d->map->column * sizeof(int));
		if (!(*visited)[i])
		{
			while (j < i)
				free((*visited)[j]);
			free(*visited);
			return (-1);
		}
		while (j < d->map->column)
			(*visited)[i][j++] = 0;
		i++;
	}
	return (1);
}

/*
	現在地の前後左右を探索し、壁でなければリストに追加する
*/
void	search_nextway(t_data *d, t_object current
								, int **visited, t_list **list)
{
	ssize_t	x;
	ssize_t	y;
	ssize_t	i;
	int		searchlist[4][2];

	searchlist[0][0] = 0;
	searchlist[0][1] = 1;
	searchlist[1][0] = 0;
	searchlist[1][1] = -1;
	searchlist[2][0] = 1;
	searchlist[2][1] = 0;
	searchlist[3][0] = -1;
	searchlist[3][1] = 0;
	i = 0;
	while (i < 4)
	{
		x = current.x + searchlist[i][0];
		y = current.y + searchlist[i][1];
		if (d->map->map[y][x] != WALL && visited[y][x] != 1)
		{
			add_list(list, x, y, NULL);
			visited[y][x] = 1;
		}
		i++;
	}
}

/*
	探索を行う
*/
int	search_root(t_data *d, int **visited, ssize_t arg_x, ssize_t arg_y)
{
	int			ret;
	t_list		*list;
	t_object	current;

	ret = 0;
	list = NULL;
	add_list(&list, d->player.x, d->player.y, NULL);
	visited[d->player.y][d->player.x] = 1;
	while (list)
	{
		current = get_from_list(&list);
		if (arg_x == current.x && arg_y == current.y)
		{
			ret = 1;
			break ;
		}
		search_nextway(d, current, visited, &list);
	}
	while (list)
		get_from_list(&list);
	return (ret);
}

/*
	現在地から引数に設定された座標に到達できるかどうか、
 　	幅優先探索を行い、到達できたら1を返す
*/
int	is_reachable(t_data *d, ssize_t arg_x, ssize_t arg_y)
{
	int		ret;
	int		**visited;
	ssize_t	i;

	if (initialize_visitedmap(d, &visited) == -1)
		return (0);
	ret = search_root(d, visited, arg_x, arg_y);
	i = 0;
	while (i < d->map->row)
		free(visited[i++]);
	free(visited);
	return (ret);
}

/*
	すべてのアイテムとゴールが到達可能か調べる
*/
void	check_playable(t_data *d)
{
	ssize_t	x;
	ssize_t	y;

	x = 0;
	y = 0;
	if (is_reachable(d, d->exit.x, d->exit.y) != 1)
		end("Error\n  There’s not a valid path in the map\n", d);
	while (x < d->map->column)
	{
		y = 0;
		while (y < d->map->row)
		{
			if (d->map->map[y][x] == ITEM)
				if (is_reachable(d, x, y) != 1)
					end("Error\n  Check map for unreachable items\n", d);
			y++;
		}
		x++;
	}
}
