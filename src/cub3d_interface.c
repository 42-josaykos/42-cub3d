/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_interface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 19:08:02 by jonny             #+#    #+#             */
/*   Updated: 2020/06/30 11:26:23 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_draw_pistol(t_window *game)
{
	t_vect2d		start;
	t_vect2d		end;
	t_vect2d		img;
	unsigned char	color[4];

	img.y = 0;
	start.y = 3.0 * game->infos->res_height / 4.0;
	while (start.y <= game->infos->res_height)
	{
		start.x = game->infos->res_width / 2;
		img.x = 0;
		while (img.x < 64)
		{
			get_color(game->texture[5], img.x, img.y, color);
			end.x = start.x + 1;
			end.y = start.y;
			if (((int)color[0] + (int)color[1]) + (int)color[2])
				ft_draw_line2(start, end, color, game);
			img.x += 128.0 / (game->infos->res_width / 2);
			start.x++;
		}
		start.y++;
		img.y += 64.0 / (game->infos->res_height / 4);
	}
}

void	ft_draw_ui(t_window *game, int xstart, unsigned int i)
{
	t_vect2d			start;
	t_vect2d			end;
	t_vect2d			img;
	unsigned char		color[4];

	img.y = 0;
	start.y = 1;
	while (start.y <= game->infos->res_height / 5.0)
	{
		start.x = xstart;
		img.x = 0;
		while (start.x < (game->infos->res_width) / 5.0 + xstart)
		{
			get_color(game->texture[i], img.x, img.y, color);
			end.x = start.x + 1;
			end.y = start.y;
			if (((int)color[0] + (int)color[1]) + (int)color[2])
				ft_draw_line2(start, end, color, game);
			img.x += 64.0 / (game->infos->res_width / 5);
			start.x++;
		}
		start.y++;
		img.y += 64.0 / (game->infos->res_height / 5);
	}
}

void	ft_draw_hp2(t_window *game, t_vect2d start, t_vect2d end,
													unsigned char color[4])
{
	int	inter;

	start.y = game->infos->res_height / 20.0;
	color[1] = 0x00;
	start.x--;
	end.y = start.y;
	ft_draw_line2(start, end, color, game);
	inter = start.y;
	start.y = game->infos->res_height / 10.0;
	end.y = game->infos->res_height / 10.0;
	ft_draw_line2(start, end, color, game);
	start.y = inter;
	end.x = start.x;
	ft_draw_line2(start, end, color, game);
	start.x = 2.0 * game->infos->res_width / 5.0;
	end.x = start.x;
	ft_draw_line2(start, end, color, game);
}

void	ft_draw_hp(t_window *game)
{
	t_vect2d		start;
	t_vect2d		end;
	unsigned char	color[4];

	color[0] = 0x00;
	color[1] = 0xff;
	color[2] = 0x00;
	color[3] = 0x00;
	start.x = game->infos->res_width / 8;
	start.y = game->infos->res_height / 20.0;
	end.x = 2.0 * game->infos->res_width / 5.0;
	while (start.y < game->infos->res_height / 10.0)
	{
		end.y = start.y;
		ft_draw_line2(start, end, color, game);
		start.y++;
	}
	ft_draw_hp2(game, start, end, color);
}

void	ft_draw_interface(t_window *game)
{
	ft_draw_pistol(game);
	ft_draw_pointer(game);
}
