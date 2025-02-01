#include "so_long.h"

/*
　読み込んだ文字の1行の長さを取得する
*/
ssize_t check_len(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != '\n' && s[len] != '\r')
		len++;
	return (len);
}

void check_map(t_data *d)
{
	ssize_t i;

	i = 0;
	d->map->column = check_len(d->map->map[i++]);
	while(i < d->map->row)
		if(d->map->column != check_len(d->map->map[i++]))
			free_and_exit("Error\n  The map must be rectangular\n", d);
	i = 0;
	while (i < d->map->column)
		if(d->map->map[0][i] != WALL || d->map->map[d->map->row - 1][i++] != WALL)
			free_and_exit("Error\n  The map must be closed/surrounded by walls\n", d);	
	i = 0;
	while (i < d->map->row)
		if(d->map->map[i][0] != WALL || d->map->map[i++][d->map->column -1] != WALL)
			free_and_exit("Error\n  The map must be closed/surrounded by walls\n", d);
	if(count_object(d, PLAYER) != 1)
		free_and_exit("Error\n  The map must contain 1 starting position\n", d);
	if(count_object(d, EXIT) != 1)
		free_and_exit("Error\n  The map must contain 1 exit\n", d);
	if(count_object(d, ITEM) < 1)
		free_and_exit("Error\n  The map must contain at least 1 collectible\n", d);
}
void enlist(t_list **head, ssize_t x, ssize_t y, void *img)
{
    t_list *new_node = (t_list *)malloc(sizeof(t_list));
    if (!new_node)
        return;
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
        return;
    }
    t_list *temp = *head;
    while(temp->next)
        temp = temp->next;
    temp->next = new_node;
}
t_object delist(t_list **head)
{
	t_list *temp = *head;
    t_object object = temp->object;
    *head = temp->next;
    free(temp);
    return object;
}
/*
　探索済みかどうかを示すマップを初期化する
*/
int set_visitedmap(t_data *d, int ***visited)
{
    int i;
    int j;

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
            while(j < i)
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
　現在地の前後左右を探索し、壁でなければキューに追加する
*/
void add_nextway(t_data *d, t_object current, int **visited, t_list **list, ssize_t i)
{
    ssize_t x;
    ssize_t y;
    int     searchlist[4][2];

    searchlist[0][0] = 0;
    searchlist[0][1] = 1;
    searchlist[1][0] = 0;
    searchlist[1][1] = -1;
    searchlist[2][0] = 1;
    searchlist[2][1] = 0;
    searchlist[3][0] = -1;
    searchlist[3][1] = 0;
    x = current.x + searchlist[i][0];
    y = current.y + searchlist[i][1];
    if (d->map->map[y][x] != WALL && visited[y][x] != 1)
    {
        enlist(list, x, y, NULL);
        visited[y][x] = 1;
    }
}

/*
　現在地から引数に設定された座標に到達できるかどうか、
　幅優先探索を行い、到達できたら1を返す
*/
int is_reachable(t_data *d, ssize_t arg_x, ssize_t arg_y)
{
    int ret;
    t_list *list;
    int **visited;
    t_object current;
    ssize_t i;

    ret = 0;
    if (set_visitedmap(d, &visited) == -1)
        return 0;
    list = NULL;
    enlist(&list, d->player.x, d->player.y, NULL);
    visited[d->player.y][d->player.x] = 1;
    while (list)
    {
        current = delist(&list);
        if (arg_x == current.x && arg_y == current.y)
        {
            ret = 1;
            break ;
        }
        i = 0;
        while(i < 4)
            add_nextway(d, current, visited, &list, i++);
    }
    while (list)
        delist(&list);
    i = 0;
	while (i < d->map->row)
		free(visited[i++]);
	free(visited);
	return ret;
}

void check_reachable(t_data *d)
{
	if(is_reachable(d, d->goal.x, d->goal.y) != 1)
        free_and_exit("Error\n  You have to check if there’s a valid path in the map\n", d);
}


