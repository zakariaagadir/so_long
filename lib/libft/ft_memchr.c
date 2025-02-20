/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.your42network>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:06:25 by zmounji           #+#    #+#             */
/*   Updated: 2024/11/05 21:07:11 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	target;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)s;
	target = (unsigned char)c;
	while (i < n)
	{
		if (ptr[i] == target)
		{
			if (ptr[i] == target)
				return ((void *)(ptr + i));
		}
		i++;
	}
	return (NULL);
}
