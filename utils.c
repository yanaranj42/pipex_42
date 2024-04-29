/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:05:48 by yanaranj          #+#    #+#             */
/*   Updated: 2024/04/24 18:31:41 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**del_quotes(t_pipe *px, char *s, char c, char **arr)
{
	while (*s && s[++px->i])
	{
		ft_start_quote(px, s, c);
		if ((s[px->i] != ' ' && (s[px->i + 1] == ' ' || !s[px->i + 1]) \
					&& px->flag == 0) || (s[px->i] == c && (s[px->i + 1] == ' ' \
				|| !s[px->i + 1]) && px->flag == 1 && s[px->i - 1] != '\\'))
		{
			if (px->flag == 1)
				arr[++px->n] = ft_substr_slash(s, px->str, \
						(px->i - px->str), -1);
			else
				arr[++px->n] = ft_substr_slash(s, px->str, \
						(px->i - px->str + 1), -1);
			if (!arr[px->n] && px->n > 0)
				print_error("malloc", 0, px);
			if (px->flag == 1)
				px->flag = 0;
		}
	}
	arr[++px->n] = NULL;
	return (arr);
}

char	**ft_split_quote(t_pipe *px, char *s, char c)
{
	char	**arr;

	px->i = -1;
	px->n = -1;
	arr = (char **)malloc(sizeof(char *) * (cmd_count(s, c) + 1));
	if (!arr)
		print_error("malloc error", 0, px);
	px->flag = 0;
	return (del_quotes(px, s, c, arr));
}

char	*ft_substr_path(char *s, int str, int len) //check para liberar
{
	char	*sub;
	int		i;
	int		size;

	size = ft_strlen(s);
	if (str >= size)
		return (ft_strdup(""));
	if (len > size - str)
		len = size - str;
	sub = malloc(sizeof(char *) * len + 2);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[i + str];
		i++;
	}
	sub[i] = '/';
	sub[i + 1] = '\0';
	printf("SUBPATH: %s\n", sub);
	return (sub);
}
/*
char	*px_strtrim(char *s, char *set, int j)
{
	char	*arr;
	int		start;
	int		len;

	start = 0;
	len = 0;
	while (s[start] && ft_strchr(set, s[start]))
		start++;
	while (len > start && ft_strchr(set, s[len - 1]))
		len--;
	arr = malloc(sizeof(char *) * ((len - start) + 1));
	if (!arr)
		return (NULL);
	while (start < len)
		arr[j++] = s[start++];
	arr[j] = '\0';
	free(s);
	return (arr);
}
*/
char	*px_strtrim(char *s1, char *set)
{
	size_t			start;
	size_t			j;
	size_t			len;
	char			*ret;

	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	len = ft_strlen(s1);
	while (len > start && ft_strchr(set, s1[len - 1]))
		len--;
	ret = (char *)malloc(sizeof(char) * ((len - start) + 1));
	if (!ret)
		return (NULL);
	j = 0;
	while (start < len)
	{
		ret[j] = s1[start];
		j++;
		start++;
	}
	ret[j] = '\0';
	free(s1);
	return (ret);
}
/*
//REVISAR LA LIBERACION DEL SUBPATH HAY QUE LIBERAR AQUI
char	**ft_split_px(t_pipe *px, char *s, char c, int i)
{
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * (w_count(s, c) + 1));
	if (!arr)
		print_error("malloc error", 0, px);
	while (*s && s[++i])
	{
		if (s[i] != c && i == 0)
			px->str = i;
		else if (s[i] != c && i > 0 && s[i - 1] == c)
			px->str = i;
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			arr[++px->k] = ft_substr_path(s, px->str, (i - px->str + 1));
			//printf("ARR: %s\n", arr[px->k]);
			if (!arr[px->k] && px->k > 0)
				print_error("malloc error", 0, px);
		}
	}
	arr[++px->k] = NULL;
	return (arr);
}
*/

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
	}
	if (!first)
	{
	//	pipex->flag = 1; //check el uso de esta flag
		return (ft_split(s, ' '));
	//	return (ft_split_pipex(pipex, s, ' ', -1));
	}
	else
		return (ft_split_quote(pipex, s, first));
	return (NULL);
}