/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:25:04 by yanaranj          #+#    #+#             */
/*   Updated: 2023/11/11 16:19:44 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	size_t			str_len;
	char			*str;

	if (!s || !f)
		return (NULL);
	str_len = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (str_len +1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < str_len)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
char upper_map(unsigned int i, char c) {
	if(i)
		i = 0;
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 'A';
    }
    return c;
}

int main (int ac, char **av)
{
	if (ac == 2)
		printf("%s", ft_strmapi(av[1], &upper_map));
	printf("%s", "\n");
}
*/
