/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:31:45 by yanaranj          #+#    #+#             */
/*   Updated: 2024/04/10 13:26:01 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	size1;
	size_t	size2;
	size_t	newsize;
	size_t	i;

	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	newsize = size1 + size2;
	join = (char *)malloc(sizeof(char) * (newsize + 1));
	if (!join)
		return (NULL);
	i = 0;
	while (i < newsize)
	{
		if (i < size1)
			join[i] = s1[i];
		else
			join[i] = s2[i - size1];
		i++;
	}
	join[i] = '\0';
	return (join);
}
/*
int main ()
{
	char *str1 = "Hola";
	char *str2 = "Mundo";
	printf("%s\n", ft_strjoin(str1, str2));
	return (0);
}
*/
