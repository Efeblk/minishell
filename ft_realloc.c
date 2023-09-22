#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>


static void	*ft_memcpy(void *dst, const void *src, size_t n)
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

void *ft_realloc(void *ptr, size_t old_len, size_t new_len)
{
    void    *new_ptr;
    if (!ptr)
        return (NULL);
    new_ptr = calloc(new_len, 1);
    if (new_ptr != NULL)
        ft_memcpy(new_ptr, ptr, old_len < new_len ? old_len : new_len);
    free(ptr);
    return (new_ptr);
}
