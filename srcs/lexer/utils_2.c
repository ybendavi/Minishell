#include "../../includes/minishell.h"

char	*ft_env_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	y;
	size_t	n;
	char	*ret;

	ret = (char *)big;
	if (ft_strlen(little) == 0)
		return (ret);
	i = 0;
	while (big[i] && i < len)
	{
		y = 0;
		n = i;
		while (n < len && big[n] == little[y])
		{
			n++;
			y++;
			if (little[y] == '\0' && big[n] == '=')
				return (ret);
		}
		ret++;
		i++;
	}
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	c1;
	char	*s1;

	s1 = (char *)s;
	c1 = (char)c;
	i = 0;
	while (i < (ft_strlen(s) + 1))
	{
		if (s1[i] == c1)
			return (&s1[i]);
		i++;
	}
	return (NULL);
}

char	*ft_cpy2(char *s1)
{
	char	*s2;
	int	i;

	i = 0;
	s2 = ft_calloc(ft_strlen(s1) + 1);
	if (!s2)
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	return (s2);
}

int	ft_mcpy(char *s1, char **s2)
{
	int	i;

	i = 0;
	*s2 = ft_calloc(ft_strlen(s1) + 1);
	if (!*s2)
		return (-1);
	while (s1[i])
	{
		(*s2)[i] = s1[i];
		i++;
	}
	return (0);
}


