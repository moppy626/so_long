/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 21:53:44 by mmachida          #+#    #+#             */
/*   Updated: 2025/01/13 18:13:02 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_buffer	*ft_lstnew(int fd)
{
	t_buffer	*list;

	list = malloc(sizeof(t_buffer));
	if (!list)
		return (NULL);
	list->str = malloc(BUFFER_SIZE);
	if (!list->str)
	{
		free(list);
		return (NULL);
	}
	list->fd = fd;
	list->buflen = 0;
	list->idx = 0;
	list->next = NULL;
	return (list);
}

ssize_t	ft_lstclear(t_buffer **lst, int fd)
{
	t_buffer	*buf;
	t_buffer	*prev;

	buf = (*lst);
	if (buf->fd == fd)
		*lst = buf->next;
	else
		while (buf->next != NULL && buf->next->fd != fd)
			buf = buf->next;
	if (buf->fd == fd)
		prev = buf;
	else
		prev = buf->next;
	if (prev)
	{
		if (buf->fd != fd)
			buf->next = prev->next;
		free(prev->str);
		prev->str = NULL;
		free(prev);
		prev = NULL;
	}
	return (-1);
}
