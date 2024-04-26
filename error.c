/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:23:25 by yanaranj          #+#    #+#             */
/*   Updated: 2024/04/25 18:36:41 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *msg, int flag, t_pipe *px, char **arr)
{
	if (px)
		clean_px(px);
	write(2, "pipex: ", 7);
	if (arr)
		ft_free(arr);
	if (flag == 0)
		perror(msg);
	else
	{
		write(1, msg, ft_strlen(msg));
		exit(flag);
	}
	exit(errno);
}

void	clean_px(t_pipe *px)
{
	if (px && px->path1 != NULL)
		free(px->path1);
	if (px && px->path2)
		free(px->path2);
	if (px && px->paths)
		ft_free(px->paths);
	if (px && px->in_cmd)
		ft_free(px->in_cmd);
	if (px && px->out_cmd)
		ft_free(px->out_cmd);
	free(px);
	px = NULL;
}

void	ft_free(char **arr)
{
	int	n;

	n = -1;
	while (n > 0)
		free(arr[n--]);
	if (n == 0)
		free(arr[n]);
	if (n < 0)
	{
		while (arr[++n])
		{
			free(arr[n]);
		}
		free(arr);
		arr = NULL;
	}
}

void	check_access(t_pipe *px, char **cmd, char **path)
{
	if (ft_strchr(cmd[0], '/'))
	{
		if (access(cmd[0], F_OK) == 0)
		{
			if (access(cmd[0], X_OK) != 0)
				print_error(ft_strjoin(cmd[0], "- permission denied\n"), \
						126, px, NULL);
			*path = ft_strdup(cmd[0]);
		}
		else
			print_error(ft_strjoin(cmd[0], "- command not found\n"), \
						127, px, NULL);
	}
	else
		*path = ft_strdup(check_paths(px->paths, cmd[0], px));
}

char	*check_paths(char **paths, char *cmd, t_pipe *px)
{
	char	*p;

	px->i = -1;
	while (paths[++px->i])
	{
		p = ft_strjoin(paths[px->i], cmd);
//		printf("check_paths: %s\n", p);
		if (!p)
			print_error("malloc error", 0, NULL, paths);
		if (access(p, F_OK) == 0)
		{
			if (access(p, X_OK) != 0)
				print_error(ft_strjoin(cmd, ": permission denied\n"), \
						126, px, NULL);
			else
				return (p);
			free(p);
		}
	}
	print_error(ft_strjoin(cmd, ": command not found\n"), 127, px, NULL);
	return (NULL);
}
