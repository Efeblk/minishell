#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if ((start > ft_strlen(s)))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		len = ft_strlen(s) - start;
	str = (char *) malloc((sizeof(char) * (len) + 1));
	if (!str)
		return (0);
	while (s[start] && (i < len))
		str[i++] = s[start++];
	str[i] = 0;
	return (str);
}