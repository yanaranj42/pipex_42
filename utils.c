/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:05:48 by yanaranj          #+#    #+#             */
/*   Updated: 2024/04/15 18:53:04 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**del_quotes(t_pipe *px, char *s, char c, char **arr)
{
	while (*s && s[++px->i])
	{
		ft_start_quote(px, s, c);
		if ((s[px->i] != ' ' && (s[px->i + 1] == ' ' || !s[px->i + 1]) \
					&& px->flag == 0)|| (s[px->i] == c && (s[px->i + 1] == ' ' \
				|| !s[px->i + 1]) && px->flag == 1 && s[px->i - 1] != '\\'))
		{
			if (px->flag == 1)
				arr[++px->n] = ft_substr_slash(s, px->start, \
						(px->i - px->start), -1);
			else
				arr[++px->n] = ft_substr_slash(s, px->start, \
						(px->i - px->start + 1), -1);
			if (!arr[px->n] && px->n > 0)
			{
				ft_free(px);
				print_error("malloc", 0, px);
			}
			if (px->flag == 1)
				px->flag = 0;
		}
	}
	arr[++px->n] = NULL;
	return (arr);
}

char	**ft_split_quote(t_pipe *pipex, char *s, char c)
{
	char **arr;

	pipex->i = -1;
	pipex->n = -1;
	arr = malloc(sizeof(char *) * (cmd_count(s, c) + 1));
	if (!arr)
		print_error("malloc error", 0, pipex);
	pipex->flag = 0;
	return (del_quotes(pipex, s, c, arr));
}

char	**ft_split_pipex(t_pipe *pipex, char *s, char c, int i)
{
	int		k = -1;
	char	**path;
	int		start;

	path = malloc(sizeof(char *) * (w_count(s, c) + 1));
	if (!path)
		print_error("malloc error", 0, pipex);
	while (*s && s[++i])
	{
		if (s[i] == c && s[i] == 0)
			start = i;
		else if (s[i] != c && i > 0 && s[i - 1] == c)
			start = i;
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			path[++k] = ft_substr(s, start, (i - start + 1));
			if (!path[k] && k > 0)
			{
				ft_free(pipex);
				print_error("malloc error", 0, pipex);
			}
		}
	}
	path[++k] = NULL;
	return (path);
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
		if (!first)
			return (ft_split_pipex(pipex, s, ' ', -1));
		else
			return (ft_split_quote(pipex, s, first));
	}
	return (NULL);
}

void	check_access(t_pipe *px, char **cmd, char **path)
{
	if (ft_strchr(cmd[0], '/'))
	{
		if (access(cmd[0], F_OK) == 0)
		{
			if (access(cmd[0], X_OK) != 0)
				print_error(ft_strjoin(cmd[0], ": permission denied2\n"), \
					   126, px);
			*path = ft_strdup(cmd[0]);
		}
		else
			print_error(ft_strjoin(cmd[0], ": command not found2\n"), 127, px);
	}
	else
		*path = ft_strdup(check_paths(px->paths, cmd[0], px));
}
