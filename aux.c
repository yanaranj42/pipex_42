/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:15:38 by yanaranj          #+#    #+#             */
/*   Updated: 2024/04/24 15:26:29 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	cmd_count(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != ' ' && (s[i + 1] == ' ' || !s[i + 1]))
			count++;
		else if (s[i] == ' ' && s[i + 1] == c)
		{
			i++;
			while (s[i] && s[i + 1] != c)
				i++;
			if (!s[i])
				return (count);
		}
		i++;
	}
	return (count);
}

int	w_count(char *s, char c)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == '\0' || s[i + 1] == c))
			counter++;
		i++;
	}
	return (counter);
}

void	ft_start_quote(t_pipe *px, char *s, char c)
{
	if ((s[px->i] == c && px->i == 0) || (s[px->i] == c && s[px->i - 1] == ' ' \
				&& px->flag == 0 && px->i > 0))
	{
		px->flag = 1;
		px->str = px->i + 1;
	}
	else if (px->i == 0 && s[px->i] != ' ')
		px->str = px->i;
	else if (s[px->i] != ' ' && !px->flag && px->i > 0 && s[px->i - 1] == ' ')
		px->str = px->i;
}

char	*ft_substr_slash(char *s, int str, int len, int i)
{
	char	*m;
	int		size;

	size = len;
	while (++i < (len - 1) && s[i + str + 1])
	{
		if (s[i + str] == '\\' && s[i + str + 1] == '\"')
			size--;
	}
	i = 0;
	m = (char *)malloc(size + 1);
	if (!m)
		print_error("malloc", 0, NULL);
	while (i < size && s[i + str])
	{
		if (s[i + str] == '\\' && s[i + str + 1] == '\"')
			str++;
		else
		{
			m[i] = s[str + i];
			i++;
		}
	}
	m[i] = '\0';
	return (m);
}

char	*px_strjoin(char *path, char *buf)
{
	size_t		i;
	size_t		j;
	char		*str;

	i = 0;
	str = malloc(sizeof(char) * ((ft_strlen(path) + ft_strlen(buf)) + 1));
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (path && path[++i] != '\0')
		str[i] = path[i];
	while (buf && buf[j] != '\0')
		str[i++] = buf[j++];
	str[i] = '\0';
	free(path);
	return (str);
}