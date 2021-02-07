/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josaykos <josaykos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 11:57:27 by jonny             #+#    #+#             */
/*   Updated: 2020/08/05 12:29:55 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Tests of new functions to implement
*/

void	ft_draw_line2(t_vect2d start, t_vect2d end, unsigned char color[4],
																t_window *game)
{
	int		dx;
	int		dy;
	float	steps;
	int		i;

	i = 1;
	dx = end.x - start.x;
	dy = end.y - start.y;
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	dx = dx / steps;
	dy = dy / steps;
	while (i <= steps)
	{
		draw_pixel(game, start.x, start.y, color);
		start.x += dx;
		start.y += dy;
		i++;
	}
}

void	ft_draw_wall(int y1, int y2, unsigned char color[4], t_window *game)
{
	int		dy;
	float	steps;
	int		i;
	int		x;

	x = game->xscreen;
	i = 1;
	dy = y2 - y1;
	steps = abs(dy);
	dy = dy / steps;
	while (i <= steps)
	{
		draw_pixel(game, x, y1, color);
		y1 += dy;
		i++;
	}
}

void	get_floor_color(char *line, t_info *infos)
{
	int i;
	int j;
	int nb;

	i = 0;
	j = 2;
	while (line[i] && (line[i] == 'F' || line[i] == ' ' || line[i] == '\t'))
		i++;
	while (line[i] && j >= 0)
	{
		if ((line[i] < '0' || line[i] > '9') && line[i] != ' '
										&& line[i] != '\t' && line[i] != ',')
			infos->ceil_color = 0;
		if (line[i] >= '0' && line[i] <= '9')
		{
			nb = ft_atoi_index(line, &i);
			if (nb >= 0 && nb <= 255 && (line[i] == ',' || line[i] == ' ' ||
											line[i] == '\t' || line[i] == '\0'))
				infos->floor[j] = nb;
			else
				infos->floor_color = 0;
			j--;
		}
		i = line[i] ? i + 1 : i;
	}
}

void	get_ceil_color(char *line, t_info *infos)
{
	int i;
	int j;
	int nb;

	i = 0;
	j = 2;
	while (line[i] && (line[i] == 'C' || line[i] == ' ' || line[i] == '\t'))
		i++;
	while (line[i] && j >= 0)
	{
		if ((line[i] < '0' || line[i] > '9') && line[i] != ' '
										&& line[i] != '\t' && line[i] != ',')
			infos->ceil_color = 0;
		if (line[i] >= '0' && line[i] <= '9')
		{
			nb = ft_atoi_index(line, &i);
			if (nb >= 0 && nb <= 255 && (line[i] == ',' || line[i] == ' ' ||
											line[i] == '\t' || line[i] == '\0'))
				infos->ceil[j] = nb;
			else
				infos->ceil_color = 0;
			j--;
		}
		i = line[i] ? i + 1 : i;
	}
}

void	del_mem(void *data)
{
	if (data != NULL)
	{
		free(data);
		data = NULL;
	}
}
