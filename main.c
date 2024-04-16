/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:07:58 by yanaranj          #+#    #+#             */
/*   Updated: 2024/04/16 19:00:08 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char *envp[], char *infile, t_pipe *px, int fd[])
{
	close(fd[0]);
	px->in_fd = open(infile, O_RDONLY);
	if (px->in_fd == -1)
		print_error(infile, 0, px);
	check_access(px, px->in_cmd, &(px->path1));
	if (dup2(px->in_fd, STDIN_FILENO) < 0)
	{
		close(px->in_fd);
		print_error("dup2: error file descriptor", 0, px);
	}
	close(px->in_fd);
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		print_error("dup2: error file descriptor", 0, px);
	close(fd[1]);
	if (execve(px->path1, px->in_cmd, envp) == -1)
		print_error(px->in_cmd[0], 0, px);
}

void	parent_process(char *envp[], char *outfile, t_pipe *px, int fd[])
{
	close(fd[1]);
	px->out_fd = open(outfile, O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (px->out_fd == -1)
		print_error(strerror(1), 1, px);
	check_access(px, px->out_cmd, &(px->path2));
	if (dup2(px->out_fd, STDOUT_FILENO) < 0)
	{
		close(px->out_fd);
		print_error("dup2: error file descriptor", 0, px);
	}
	close(px->out_fd);
	if (dup2(fd[0], STDIN_FILENO) < 0)
		print_error("dup2: file descriptor", 0, px);
	close(fd[0]);
	if (execve(px->path2, px->out_cmd, envp) == -1)
		print_error(px->out_cmd[0], 0, px);
}

void	init_pipex(t_pipe *pipex)
{
	pipex->i = -1;
	pipex->n = -1;
	pipex->flag = 0;
	pipex->in_fd = -1;
	pipex->out_fd = -1;
	pipex->in_cmd = NULL;
	pipex->out_cmd = NULL;
	pipex->paths = NULL;
	pipex->path1 = NULL;
	pipex->path2 = NULL;
}

void	parsing(char **av, char *envp[], t_pipe *px)
{
	int	i;

	i = -1;
	init_pipex(px);
	px->in_cmd = final_cmd(av[2], px, -1);
	px->out_cmd = final_cmd(av[3], px, -1);
	while(envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			px->paths = ft_split_pipex(px, envp[i] + 5, ':', -1, 0);	
			break ;
		}
	}
	if (!px->paths)
		px->paths = ft_split_pipex(px, DEF_PATH, ':', -1, 0);
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
	parsing(av, envp, px);
	if (pipe(fd) < 0 )
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
