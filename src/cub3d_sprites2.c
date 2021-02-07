/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_sprites2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 13:00:38 by jonny             #+#    #+#             */
/*   Updated: 2020/05/27 17:52:59 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_draw_sprite2(t_vect2d *img, t_vect2d *start, t_vect2d *end,
														t_window *game)
{
	unsigned char	color[4];

	get_color(game->texture[4], img->x, img->y, color);
	if (start->x && ((int)color[0] + (int)color[1]) + (int)color[2])
		ft_draw_line2(*start, *end, color, game);
	start->y = end->y;
	end->y += 1;
}

void	ft_draw_sprite(t_window *game, double sprite_height,
						double pixel_height, t_sprite *sprite)
{
	t_vect2d		img;
	t_vect2d		start;
	t_vect2d		end;
	int				ymax;

	start.x = sprite->xscreen - (sprite_height / 2.0);
	img.x = 0;
	start.y = (game->infos->res_height / 2.0) - (sprite_height / 2.0);
	ymax = start.y + sprite_height;
	while (start.x < game->infos->res_width && start.x < sprite->xscreen +
														(sprite_height / 2.0))
	{
		end.x = start.x;
		img.y = 0;
		start.y = (game->infos->res_height / 2.0) - (sprite_height / 2.0);
		end.y = start.y + pixel_height;
		while (end.y < ymax)
		{
			ft_draw_sprite2(&img, &start, &end, game);
			img.y += 1 / pixel_height;
		}
		start.x += 1;
		img.x += 1 / pixel_height;
	}
}
