/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:37:41 by yanaranj          #+#    #+#             */
/*   Updated: 2023/11/02 13:37:22 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t			i;
	unsigned int	dst_cont;
	unsigned int	src_cont;

	i = 0;
	dst_cont = ft_strlen(dst);
	src_cont = ft_strlen(src);
	if (dstsize <= dst_cont)
		return (dstsize + src_cont);
	while (src[i] != '\0' && dst_cont + 1 < dstsize)
	{
		dst[dst_cont] = src[i];
		i++;
		dst_cont++;
	}
	dst[dst_cont] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[i]));
}
