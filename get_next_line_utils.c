/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:59:52 by mismene           #+#    #+#             */
/*   Updated: 2020/11/25 15:04:29 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/graphics.h"

char	*ft_strnew(unsigned int size)
{
	char	*str;

	if (!(str = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	str[size] = '\0';
	while (size--)
		str[size] = '\0';
	return (str);
}

char	*ft_strcpy(char *dst, const char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = '\0';
	return (dst);
}


