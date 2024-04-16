/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:23:25 by yanaranj          #+#    #+#             */
/*   Updated: 2024/04/16 14:07:44 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *msg, int flag, t_pipe *px)
{
	if (px)
		ft_free(px);
	write(2, "pipex: ", 7);
	if (flag ==  0)
		perror(msg);
	else
	{
		write(1, msg, ft_strlen(msg));
		exit(flag);
	}
	exit(errno);
}
/*
void	free_cmd(char *cmd1, char *cmd2);
{
	while(cmd1[i])
}*/

void	ft_free(t_pipe *px)
{
	int	i;

	i = -1;
	if (px->paths != NULL)
	{
		while(px->paths[++i])
		{
			free(px->paths[i]);
			px->paths[i] = NULL;
		}
		free(px->paths);
		px->paths = NULL;
	}
	i = -1;
	if (px->in_cmd != NULL && px->out_cmd != NULL)
	{
		while (px->in_cmd[++i] && px->out_cmd[++i])
		{
			free(px->in_cmd[i]);
			free(px->out_cmd[i]);
			px->in_cmd[i] = NULL;
			px->out_cmd[i] = NULL;
		}
		free(px->in_cmd);
		free(px->out_cmd);
		px->in_cmd = NULL;
		px->out_cmd = NULL;
	}
}

void	check_access(t_pipe *px, char **cmd, char **path)
{
	if (ft_strchr(cmd[0], '/'))
	{
		if (access(cmd[0], F_OK) == 0)
		{
			if (access(cmd[0], X_OK) != 0)
				print_error(ft_strjoin(cmd[0], "- permission denied2\n"), \
					   126, px);
			*path = ft_strdup(cmd[0]);
		}
		else
			print_error(ft_strjoin(cmd[0], "- command not found2\n"), 127, px);
	}
	else
		*path = ft_strdup(check_paths(px->paths, cmd[0], px));
}

char *check_paths(char **paths, char *cmd, t_pipe *px)
{
	char	*p;

	while (paths[++px->i])
	{
		p = ft_strjoin(paths[px->i], cmd);
		if (!p)
		{
			ft_free(px);
			print_error("malloc error", 0, NULL);
		}
		if (access(p, F_OK) == 0)
		{
			if (access(p, X_OK) != 0)
				print_error(ft_strjoin(cmd, ": permission denied1\n"), \
						126, px);
			else
				return (p);
		}
	}
	print_error(ft_strjoin(cmd, ": command not found1\n"), 127, px);
	return (NULL);
}
