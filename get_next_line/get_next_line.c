/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 21:54:43 by mmachida          #+#    #+#             */
/*   Updated: 2025/01/15 23:00:31 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static struct t_buffer	*lst = NULL;
	t_buffer				*b;
	char					*ret;
	ssize_t					cpylen;
	ssize_t					len;

	ret = NULL;
	b = NULL;
	len = 0;
	while (get_next_buffer(&lst, fd, &b) >= 0 && b != NULL)
	{
		cpylen = get_cpylen(b);
		ret = cpy(ret, b, len, cpylen);
		if (!ret)
			return (ft_lstclear(&lst, fd), NULL);
		len += cpylen;
		b->idx += cpylen;
		if (b->str[b->idx - 1] == '\n')
			break ;
	}
	if (ret != NULL)
		ret[len] = '\0';
	return (ret);
}

ssize_t	get_next_buffer(t_buffer **lst, int fd, struct t_buffer **buf)
{
	ssize_t					ret;

	ret = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > SSIZE_MAX)
		return (-1);
	*buf = search(lst, fd);
	if (!*buf)
		return (-1);
	if ((*buf)->idx >= (*buf)->buflen)
	{
		ret = read(fd, (*buf)->str, BUFFER_SIZE);
		if (ret <= 0)
		{
			ft_lstclear(lst, fd);
			(*buf) = NULL;
		}
		else
		{
			(*buf)->buflen = ret;
			(*buf)->idx = 0;
		}
	}
	return (ret);
}

t_buffer	*search(struct t_buffer **lst, int fd)
{
	struct t_buffer	*buf;

	if (!(*lst))
	{
		*lst = ft_lstnew(fd);
		if (!(*lst))
			return (NULL);
		buf = *lst;
	}
	else
	{
		buf = *lst;
		while (buf != NULL && buf->fd != fd)
			buf = buf->next;
		if (!buf)
		{
			buf = ft_lstnew(fd);
			if (!buf)
				return (NULL);
			buf->next = *lst;
			*lst = buf;
		}
	}
	return (buf);
}

char	*cpy(char *ret, t_buffer *b, ssize_t len, ssize_t cpylen)
{
	char	*temp;

	temp = malloc(len + cpylen + 1);
	if (!temp)
	{
		free(ret);
		return (NULL);
	}
	ft_memcpy(temp, ret, len);
	ft_memcpy(temp + len, b->str + b->idx, cpylen);
	free(ret);
	ret = temp;
	return (ret);
}

ssize_t	get_cpylen(t_buffer *b)
{
	ssize_t	cpylen;

	cpylen = 0;
	while ((b->idx + cpylen) < b->buflen && b->str[b->idx + cpylen] != '\n')
		cpylen++;
	if ((b->idx + cpylen) < b->buflen && b->str[b->idx + cpylen] == '\n')
		cpylen++;
	return (cpylen);
}
