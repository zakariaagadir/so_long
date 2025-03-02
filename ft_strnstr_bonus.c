/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:12:28 by zmounji           #+#    #+#             */
/*   Updated: 2025/03/02 22:19:51 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	pt;

	pt = ft_strlen(needle);
	i = 0;
	if (!*needle)
		return ((char *)haystack);
	if (!*haystack || len == 0)
		return (NULL);
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && haystack[i + j])
			j++;
		if (needle[j] == '\0' && (i + pt) <= len)
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
