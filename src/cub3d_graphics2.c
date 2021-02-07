/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_graphics2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:51:15 by jonny             #+#    #+#             */
/*   Updated: 2020/05/31 18:25:01 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Draw the 2D map
*/

void	ft_draw_position(unsigned char color[4], t_window *game)
{
	t_vect2d	start;
	t_vect2d	end;

	start.x = game->cam->xpos;
	start.y = game->cam->ypos - 4;
	end.x = start.x;
	end.y = game->cam->ypos + 5;
	color[2] = 0xFF;
	ft_draw_line2(start, end, color, game);
	start.x = game->cam->xpos - 4;
	start.y = game->cam->ypos;
	end.x = game->cam->xpos + 5;
	end.y = start.y;
	ft_draw_line2(start, end, color, game);
}

void	draw_map2(t_vect2d pos, unsigned char color[4], t_window *game)
{
	int			block_width;
	int			block_height;
	t_vect2d	img;

	block_width = game->infos->res_width / game->infos->map_width;
	block_height = game->infos->res_height / game->infos->map_height;
	while (++pos.x < game->infos->map_height)
	{
		pos.y = -1;
		while (++pos.y < game->infos->map_width)
			if (game->infos->map_content[(int)pos.x][(int)pos.y] == '1')
			{
				img.x = -1;
				while (img.x++ < block_height)
				{
					img.y = -1;
					while (img.y++ < block_width)
						draw_pixel(game, (pos.y * block_width) + img.y,
										(pos.x * block_height) + img.x, color);
				}
			}
	}
}

void	draw_map(t_window *game)
{
	t_vect2d		pos;
	t_vect2d		max;
	unsigned char	color[4];

	pos.x = 0;
	pos.y = 0;
	max.x = 0;
	max.y = game->infos->res_height;
	color[0] = 0x00;
	color[1] = 0x00;
	color[2] = 0x00;
	color[3] = 0x00;
	ft_draw_position(color, game);
	max.x = game->infos->res_width;
	color[1] = 0x33;
	color[2] = 0x4d;
	pos.x = -1;
	draw_map2(pos, color, game);
}
