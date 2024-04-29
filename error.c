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

void	print_error(char *msg, int flag, t_pipe *px)
{
	if (px)
		clean_px(px);
	write(2, "pipex: ", 7);
//	if (arr)
//		ft_free(arr);
	if (flag == 0)
		perror(msg);
	else
	{
		write(1, msg, ft_strlen(msg));
		//free(msg);
		exit(flag);
	}
	//free(msg);
	exit(errno);
}

void	clean_px(t_pipe *px)
{
	if (px && px->paths)
		free_matrix(px->paths);
	if (px && px->path1)
		free(px->path1);
	if (px && px->path2)
		free(px->path2);
	if (px && px->paths)
		ft_free(px->paths);
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
	//	printf("%s\n", px->paths[0]);
		path = px_strjoin(*px->paths, cmd[0]);
//		printf("Print_path: %s\n", path);//si tiene la barra
		if (!path)
			print_error("Malloc error", 0, px); //liberar paths??
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) != 0)
				print_error("Execute access error\n", 126, px);
			else
				return (path);
		}
		else
		{
			print_error("Access error\n", 127, px);
			free(path);
		}
	}
	return (0);
}
