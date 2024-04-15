/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:23:25 by yanaranj          #+#    #+#             */
/*   Updated: 2024/04/15 14:05:29 by yanaranj         ###   ########.fr       */
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
