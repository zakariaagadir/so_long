/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.your42network>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:03:18 by zmounji           #+#    #+#             */
/*   Updated: 2024/11/06 01:50:35 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	if (dstsize == 0)
	{
		src_len = 0;
		while (src[src_len])
			src_len++;
		return (src_len);
	}
	i = 0;
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}
/*#include <stdio.h>
int main()
{
	char *dst = "world";
	char *src = "hello";
	ft_strlcpy(dst, src, 3);
	printf("%s\n", dst);
	return (0);
}*/
