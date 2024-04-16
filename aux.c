/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:15:38 by yanaranj          #+#    #+#             */
/*   Updated: 2024/04/16 19:01:36 by yanaranj         ###   ########.fr       */
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
			while(s[i] && s[i + 1] != c)
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
		px->flag = -1;
		px->start = px->i + 1;
	}
	else if (px->i == 0 && s[px->i] != ' ')
		px->start = px->i;
	else if (s[px->i] != ' ' && !px->flag && px->i > 0 && s[px->i - 1] == ' ')
		px->start = px->i;
}

char	*ft_substr_slash(char *s, int start, int len, int i)
{
	char	*m;
	int		size;

	size = len;
	while (++i < (len - 1) && s[i + start + 1])
	{
		if (s[i + start] == '\\' && s[i +  start + 1] == '\"')
			size--;
	}
	i = 0;
	m = malloc(size + 1);
	if (m)
	{
		while (i < size && s[i + start])
		{
			if (s[i + start] == '\\' && s[i + start + 1] == '\"')
				start++;
			else
			{
				m[i] = s[start + i];
				i++;
			}
		}
		m[i] = '\0';
		return (m);
	}
	else
		return (0);
}
