/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:07:58 by yanaranj          #+#    #+#             */
/*   Updated: 2024/04/25 18:42:12 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//PROCESOS

void    init_paths(t_pipe *px, char **envp)
{
    int i;

    i = -1;
    while (envp[++i])
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
        {
            px->paths = ft_split(envp[i], ':');
			px->paths[0] = px_strtrim(px->paths[0], "PATH="); //0 elimina el path de el array
			break ;
        }
    }
    if (!px->paths)
		px->paths = ft_split(DEF_PATH, ':');
}

void	init_pipex(t_pipe *pipex)
{
	pipex->i = -1;
	pipex->n = -1;
	pipex->k = -1;
	pipex->flag = 0;
	pipex->in_fd = -1;
	pipex->out_fd = -1;
	pipex->in_cmd = NULL;
	pipex->out_cmd = NULL;
	pipex->paths = NULL;
	pipex->path1 = NULL;
	pipex->path2 = NULL;
}

void    parsing(t_pipe *px, char **av, char **envp)
{
    init_pipex(px);
    init_paths(px, envp);
    px->in_cmd = final_cmd(av[2], px, 1);
	px->k = -1;
    px->out_cmd = final_cmd(av[3], px, 1);
    check_access(px, px->in_cmd, -1);
    check_access(px, px->out_cmd, -1);
    //mirar si lo podemos eliminar porque era para el split_px
    px->flag = 0; 
    px->k = -1;
}

int	main(int ac, char **av, char *envp[])
{
	t_pipe	*px;
	int		pid;
	int		fd[2];

	px = NULL;
	if (ac != 5)
		print_error("invalid arguments. Introduce 4 args\n", 15, px);
	px = malloc(sizeof(t_pipe));
	if (!px)
		print_error("malloc error", 1, NULL);
	parsing(px, av, envp);
	if (pipe(fd) < 0)
		print_error("pipe error", 1, px);
	pid = fork();
	if (pid < 0)
		print_error("fork error", 1, px);
	if (pid == 0)
		child_process(envp, av[1], px, fd);
	else
		parent_process(envp, av[4], px, fd);
	waitpid(pid, NULL, 0);
	return (0);
}