/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 21:53:32 by mmachida          #+#    #+#             */
/*   Updated: 2025/01/13 19:50:36 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <bits/posix1_lim.h>
# include "../libft/libft.h"

typedef struct t_buffer
{
	int				fd;
	char			*str;
	ssize_t			idx;
	ssize_t			buflen;
	struct t_buffer	*next;
}	t_buffer;

char		*get_next_line(int fd);
ssize_t		get_next_buffer(t_buffer **lst, int fd, struct t_buffer **buf);
ssize_t		get_cpylen(t_buffer *b);
char		*cpy(char *ret, t_buffer *b, ssize_t len, ssize_t cpylen);
t_buffer	*ft_lstnew(int fd);
t_buffer	*search(struct t_buffer **lst, int fd);
ssize_t		ft_lstclear(t_buffer **lst, int fd);

#endif 