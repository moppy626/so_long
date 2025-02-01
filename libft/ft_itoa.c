/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_itoa.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mmachida <mmachida@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/28 17:06:47 by mmachida		  #+#	#+#			 */
/*   Updated: 2024/05/29 09:54:41 by mmachida		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

static int		getlen(int n);
static long		tolong(int n);

char	*ft_itoa(int n)
{
	char	*ret;
	long	num;
	int		len;
	int		i;

	len = getlen(n);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ret[len] = '\0';
	if (n == 0)
	{
		ret[0] = '0';
		return (ret);
	}
	i = len - 1;
	num = tolong(n);
	while (0 < num)
	{
		ret[i--] = (num % 10) + '0';
		num = num / 10;
	}
	if (n < 0)
		ret[0] = '-';
	return (ret);
}

static int	getlen(int n)
{
	int		i;
	long	num;

	i = 0;
	if (n < 0)
		i++;
	num = tolong(n);
	while (num >= 10)
	{
		num = num / 10;
		i++;
	}
	return (i + 1);
}

static long	tolong(int n)
{
	if (n < 0)
		return (-(long)n);
	else
		return ((long)n);
}
