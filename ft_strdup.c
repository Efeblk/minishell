#include "minishell.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *) malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!str)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = 0;
	return (str);
}