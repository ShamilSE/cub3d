/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_file_volume_4.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mismene <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 05:29:45 by mismene           #+#    #+#             */
/*   Updated: 2021/02/21 05:29:47 by mismene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/cub3d.h"

void	undefined_handler(char c)
{
	if (c != ' ')
		throw_error("unexpected char(s) in R option");
}

void	correct_color_handler(char *line)
{
	line++;
	if (*line != ' ')
		throw_error("...");
	while (!(ft_isdigit(*line)))
	{
		if (*line != ' ')
			throw_error("stop doing this dushnila stuff :)");
		line++;
	}
}