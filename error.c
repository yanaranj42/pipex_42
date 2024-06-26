/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:23:25 by yanaranj          #+#    #+#             */
/*   Updated: 2024/04/30 17:21:52 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *msg, int flag, t_pipe *px)
{
	if (px)
		clean_px(px);
	write(2, "pipex: ", 7);
	if (flag == 1)
		perror(msg);
	else
		write(1, msg, ft_strlen(msg));
	exit(errno);
}

void	clean_px(t_pipe *px)
{
	if (px && px->paths)
		ft_free(px->paths);
	if (px && px->path1)
		free(px->path1);
	if (px && px->path2)
		free(px->path2);
	if (px && px->in_cmd)
		ft_free(px->in_cmd);
	if (px && px->out_cmd)
		ft_free(px->out_cmd);
	if (px)
		free(px);
	px = NULL;
}

void	ft_free(char **arr)
{
	int	n;

	n = -1;
	while (arr[++n])
		free(arr[n]);
	free(arr);
	arr = NULL;
}

char	*check_access(t_pipe *px, char **cmd, int i)
{
	char	*path;

	while (px->paths[++i])
	{
		path = px_barjoin(px->paths[i], "/");
		path = px_strjoin(path, cmd[0]);
		if (!path)
			print_error("Malloc error", 0, px);
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) != 0)
				print_error(" -permission denied\n", 126, px);
			else
				return (path);
		}
		else
			free(path);
	}
	print_error(ft_strjoin(cmd[0], ": No such a file or directory\n"), 127, px);
	return (0);
}
