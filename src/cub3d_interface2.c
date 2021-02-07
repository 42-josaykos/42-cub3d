/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_interface2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:35:39 by jonny             #+#    #+#             */
/*   Updated: 2020/05/27 17:35:43 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_draw_pointer(t_window *game)
{
	int				x;
	int				y;
	t_vect2d		start;
	t_vect2d		end;
	unsigned char	color[4];

	color[0] = 0xff;
	color[1] = 0xff;
	color[2] = 0xff;
	color[3] = 0x00;
	x = (game->infos->res_width / 2);
	y = (game->infos->res_height / 2);
	start.x = x - 10;
	start.y = y;
	end.x = x + 10;
	end.y = y;
	ft_draw_line2(start, end, color, game);
	start.x = x;
	start.y = y - 10;
	end.x = x;
	end.y = y + 10;
	ft_draw_line2(start, end, color, game);
}
