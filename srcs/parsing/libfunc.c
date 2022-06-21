#include "minishell.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dest)
		return (0);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n && n != 0)
	{
		if (s1[i] != s2[i])
		{
			if ((unsigned char)s1[i] > (unsigned char)s2[i])
				return (1);
			else
				return (-1);
		}
		i++;
	}
	return (0);
}

static int	ft_strslen(char const *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i] == c && s[i])
		i++;
	if (s[i] == 0)
		return (0);
	while (s[i])
	{
		if (s[i] == c && s[i - 1] != c && i != 0)
			len++;
		i++;
	}
	if (s[i - 1] != c)
		return (len + 1);
	else
		return (len);
}

static char	*ft_strcutdup(const char *src, char c)
{
	char	*dest;
	int		i;

	i = 0;
	while (src[i] && src[i] != c)
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 1));
	if (!(dest))
		return (NULL);
	i = 0;
	while (src[i] && src[i] != c)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		len;
	char	**strs;
	int		j;

	if (s == NULL)
		return (0);
	len = ft_strslen(s, c);
	i = 0;
	strs = (char **)ft_calloc((len + 1) * sizeof(char *));
	if (!(strs))
		return (NULL);
	if (len == 0)
		return (strs);
	while (i < len)
	{
		j = 0;
		while (s[j] == c && s[j])
			j++;
		s = &s[j];
		strs[i] = ft_strcutdup(s, c);
		s = ft_strchr(s, c);
		i++;
	}
	return (strs);
}
