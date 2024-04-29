//header

#include "pipex.h"

void	parent_process(char *envp[], char *outfile, t_pipe *px, int fd[])
{
	close(fd[1]);
	px->out_fd = open(outfile, O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (px->out_fd == -1)
		print_error(strerror(1), 1, px, NULL);
    if (dup2(fd[0], STDIN_FILENO) < 0)
    {
        close(px->in_fd);
		print_error("dup2: error file descriptor", 0, px, NULL);
    }
	if (dup2(px->out_fd, STDOUT_FILENO) < 0)
	{
		close(px->out_fd);
		print_error("dup2: error file descriptor", 0, px, NULL);
	}
	close(px->out_fd);
	if (execve(px->path2, px->out_cmd, envp) == -1)
		print_error(px->out_cmd[0], 0, px, NULL);
    close(fd[0]);
}

void	child_process(char *envp[], char *infile, t_pipe *px, int fd[])
{
	close(fd[0]);
	px->in_fd = open(infile, O_RDONLY);
	if (px->in_fd == -1)
		print_error(infile, 0, px, NULL);
	if (dup2(px->in_fd, STDIN_FILENO) < 0)
	{
		close(px->in_fd);
		print_error("dup2: error file descriptor", 0, px, NULL);
	}
	close(px->in_fd);
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		print_error("dup2: Outfile error", 0, px, NULL);
	if (execve(px->path1, px->in_cmd, envp) == -1)
		print_error(px->in_cmd[0], 0, px, NULL);
}