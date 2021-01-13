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

#include "../headers/graphics.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		++i;
	return (i);
}

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

char	*ft_strdup(const char *s1)
{
	char	*str_dup;
	char	*p;

	str_dup = malloc(ft_strlen(s1) + 1);
	p = str_dup;
	if (str_dup == NULL)
		return (NULL);
	while (*s1)
		*p++ = *s1++;
	*p = '\0';
	return (str_dup);
}

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		++i;
	}
	free(s1);
	while (s2[j] != '\0')
	{
		p[i] = s2[j];
		++i;
		++j;
	}
	p[i] = '\0';
	return (p);
}


