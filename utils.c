/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:05:48 by yanaranj          #+#    #+#             */
/*   Updated: 2024/04/30 17:32:45 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**del_quotes(t_pipe *px, char *s, char c, char **arr)
{
	while (*s && s[++px->i])
	{
		ft_start_quote(px, s, c);
		if ((s[px->i] != ' ' && (s[px->i + 1] == ' ' || !s[px->i + 1]) \
					&& px->flag == 0) || (s[px->i] == c && (s[px->i + 1] == ' ' \
				|| !s[px->i + 1]) && px->flag == 1 && s[px->i - 1] != '\\'))
		{
			if (px->flag == 1)
				arr[++px->n] = ft_substr_slash(s, px->str, \
						(px->i - px->str), -1);
			else
				arr[++px->n] = ft_substr_slash(s, px->str, \
						(px->i - px->str + 1), -1);
			if (!arr[px->n] && px->n > 0)
				print_error("malloc", 0, px);
			if (px->flag == 1)
				px->flag = 0;
		}
	}
	arr[++px->n] = NULL;
	return (arr);
}

char	**ft_split_quote(t_pipe *px, char *s, char c)
{
	char	**arr;

	px->i = -1;
	px->n = -1;
	arr = (char **)malloc(sizeof(char *) * (cmd_count(s, c) + 1));
	if (!arr)
		print_error("malloc error", 0, px);
	px->flag = 0;
	return (del_quotes(px, s, c, arr));
}

char	*px_barjoin(char *path, char *buf)
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
	return (str);
}

char	*px_strtrim(char *s1, char *set)
{
	size_t			start;
	size_t			j;
	size_t			len;
	char			*ret;

	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	len = ft_strlen(s1);
	while (len > start && ft_strchr(set, s1[len - 1]))
		len--;
	ret = (char *)malloc(sizeof(char) * ((len - start) + 1));
	if (!ret)
		return (NULL);
	j = 0;
	while (start < len)
	{
		ret[j] = s1[start];
		j++;
		start++;
	}
	ret[j] = '\0';
	free(s1);
	return (ret);
}

char	**final_cmd(char *s, t_pipe *pipex, int i)
{
	char	first;

	first = '\0';
	while (s[++i])
	{
		if (!first && (s[i] == '\'' || s[i] == '\"'))
		{
			first = s[i];
			break ;
		}
	}
	if (ft_strchr(s, '/'))
	{
		i = ft_strlen(s) - 1;
		while (s[i] != '/')
			i--;
		s = ft_substr(s, i + 1, ft_strlen(s));
	}
	if (!first)
		return (ft_split(s, ' '));
	else
		return (ft_split_quote(pipex, s, first));
	return (NULL);
}
