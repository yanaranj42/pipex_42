/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:08:31 by yanaranj          #+#    #+#             */
/*   Updated: 2024/04/24 13:26:52 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/errno.h>
# include "libft/libft.h"

# define DEF_PATH "/usr/local/bin:/usr/bin:/bin:\
	/usr/sbin:/sbin:/usr/local/go/bin:"

typedef struct s_pipe
{
	int		in_fd;
	int		out_fd;
	int		flag;
	int		i;
	int		n;
	int		k;
	int		str;
	char	**paths;
	char	*path1;
	char	*path2;
	char	**in_cmd;
	char	**out_cmd;
}			t_pipe;

//		--main.c--		//
void	child_process(char *envp[], char *infile, t_pipe *px, int fd[]);
void	parent_process(char *envp[], char *outfile, t_pipe *px, int fd[]);
void	init_pipex(t_pipe *pipex);
void	parsing(char **av, char *envp[], t_pipe *px);

//		--error.c--		//
void	print_error(char *msg, int flag, t_pipe *px, char **arr);
void	clean_px(t_pipe *px);
void	ft_free(char **arr);
void	check_access(t_pipe *px, char **cmd, char **path);
char	*check_paths(char **paths, char *cmd, t_pipe *px);

//		--utils.c--		//
char	**del_quotes(t_pipe *px, char *s, char c, char **arr);
char	**ft_split_quote(t_pipe *px, char *s, char c);
char	*ft_substr_path(char *s, int start, int len);
char	**ft_split_pipex(t_pipe *pipex, char *s, char c, int i);
char	**final_cmd(char *s, t_pipe *px, int i);

//		--aux.c--		//
int		cmd_count(char *s, char c);
int		w_count(char *s, char c);
void	ft_start_quote(t_pipe *px, char *s, char c);
char	*ft_substr_slash(char *s, int start, int len, int i);

#endif
