#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*newdst;
	char	*newsrc;
	size_t	i;

	if (!dst && !src)
		return (NULL);
	newdst = (char *)dst;
	newsrc = (char *)src;
	i = 0;
	while (i < n)
	{
		newdst[i] = newsrc[i];
		i++;
	}
	return (dst);
}
