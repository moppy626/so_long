/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:12:36 by mmachida          #+#    #+#             */
/*   Updated: 2025/02/06 21:12:36 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
	エラーメッセージを表示し、マップのみ解放して終了する
*/
void	fail_and_end(char *msg, t_data *d)
{
	if (d->map)
		free(d->map);
	ft_printf(msg);
	exit(EXIT_FAILURE);
}

/*
	エラーメッセージを表示し、データを解放して終了する
*/
void	end(char *msg, t_data *d)
{
	ft_printf(msg);
	free_data(d);
	exit(EXIT_FAILURE);
}

/*
　マップの行数をカウントする
　（後ろの改行を無視するため、最後の改行以外の行を返す）
*/
ssize_t	count_map(t_data *d, char **argv)
{
	ssize_t	rowcnt;
	ssize_t	valid_rowcnt;
	int		fd;
	char	*ret;

	rowcnt = 0;
	valid_rowcnt = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		fail_and_end("Error\n Failed to open map file\n", d);
	ret = get_next_line(fd);
	while (ret)
	{
		rowcnt++;
		if (!(ret[0] == '\r' || ret[0] == '\n'))
			valid_rowcnt = rowcnt;
		free(ret);
		ret = get_next_line(fd);
	}
	close(fd);
	if (valid_rowcnt < 3)
		fail_and_end("Error\n Invalid map row count\n", d);
	return (valid_rowcnt);
}

/*
	マップを読み込みます
*/
void	read_map(t_data *d, int fd)
{
	int		i;
	char	*ret;

	i = 0;
	ret = get_next_line(fd);
	while (ret)
	{
		if (d->map->row > i)
			d->map->map[i] = ret;
		else
			free(ret);
		i++;
		ret = get_next_line(fd);
	}
}

/*
	パラメタのパスからマップを読み込みます
*/
void	get_map(t_data *d, char **argv)
{
	int	fd;

	d->map = malloc(sizeof(t_map));
	if (!d->map)
		fail_and_end("Error\n  Failed in malloc\n", d);
	d->map->row = count_map(d, argv);
	d->map->map = malloc(sizeof(char *) * d->map->row);
	if (!d->map->map)
		end("Error\n  Failed in malloc\n", d);
	fd = open(argv[1], O_RDONLY);
	read_map(d, fd);
	close(fd);
	check_map(d);
	d->map->count = 0;
	d->map->getitems = 0;
}
