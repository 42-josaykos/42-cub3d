/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_graphics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 11:22:08 by josaykos          #+#    #+#             */
/*   Updated: 2020/06/08 17:52:01 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** This function draw a pixel on the image
*/

void	draw_pixel(t_window *game, unsigned int x, unsigned int y,
		unsigned char color[5])
{
	int pos;
	int i;

	if (x >= game->infos->res_width || y >= game->infos->res_height)
		return ;
	pos = (x * 4) + (y * 4) * game->infos->res_width;
	i = -1;
	while (++i < 4)
		game->data_ptr->addr[pos + i] = color[i];
}

/*
** Get the 4 (TRGB) values of the pixel x/y in the texture image.
** Save it in a "color array" to use with the draw_pixel function.
*/

void	get_color(t_texture *texture, int x, int y, unsigned char *color)
{
	int pos;
	int i;

	if (x > texture->width || y > texture->height)
		return ;
	if (x < 0 || y < 0)
		return ;
	pos = (x + y * texture->width) * 4;
	i = -1;
	while (++i < 4)
		color[i] = texture->data[pos + i];
}

/*
** Draw ground and ceiling. Colors parsing
*/

void	ft_draw_ground(t_window *game)
{
	int						y;
	int						ymax;
	t_vect2d				start;
	t_vect2d				end;

	y = 0;
	ymax = game->infos->res_height;
	start.x = 0;
	end.x = game->infos->res_width;
	while (y < (ymax / 2))
	{
		start.y = y;
		end.y = y;
		ft_draw_line2(start, end, game->infos->ceil, game);
		y += 1;
	}
	while (y < ymax)
	{
		start.y = y;
		end.y = y;
		ft_draw_line2(start, end, game->infos->floor, game);
		y += 1;
	}
}
