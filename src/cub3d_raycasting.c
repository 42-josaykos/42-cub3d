/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:52:06 by jonny             #+#    #+#             */
/*   Updated: 2020/06/15 14:32:47 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		ft_sw(t_window *game)
{
	if (game->sens == 1 || game->sens == 2)
		return (0);
	return (-63);
}

void	ft_draw_view(t_window *game, double wall_height, int x2, int y2)
{
	t_vect2d		point;
	unsigned char	color[4];
	double			pixel_height;
	int				ymax;
	int				j;

	pixel_height = (wall_height / (game->texture[0]->height));
	point.x = (game->infos->res_height / 2.0) - (wall_height / 2.0);
	point.y = point.x + pixel_height;
	ymax = point.x + wall_height;
	j = 0;
	while (point.y < ymax)
	{
		if (game->sens < 2)
			get_color(game->texture[game->sens], labs(ft_sw(game) + ((x2 * 64 /
	(game->infos->block_size)) % 64)), j, color);
		else
			get_color(game->texture[game->sens], labs(ft_sw(game) + ((y2 * 64 /
	(game->infos->block_size)) % 64)), j, color);
		ft_draw_wall(point.x, point.y, color, game);
		point.x = point.y;
		point.y += pixel_height;
		j++;
	}
	game->sens != 4 ? game->xscreen += 1 : 1;
}

void	ft_distance_to_wall(t_window *game, double x2, double y2, double angle)
{
	double distance;
	double correct_distance;
	double plane_distance;
	double wall_height;
	double block_size;

	game->infos->block_size = game->infos->res_height / game->infos->map_height;
	block_size = game->infos->block_size;
	distance = sqrt(pow(game->cam->xpos - x2, 2) +
					pow(game->cam->ypos - y2, 2));
	correct_distance = cos(convert_radian(fabs(angle - game->cam->angle))) *
							distance;
	plane_distance = (game->infos->res_width / 2.0) /
						tan(convert_radian(FOV / 2.0));
	wall_height = round(block_size / correct_distance * plane_distance);
	ft_draw_view(game, wall_height, x2, y2);
}

void	raycast(t_window *game, double x, double y, double angle)
{
	int		rx;
	int		ry;
	double	i;
	double	j;

	i = cos(convert_radian(angle));
	j = sin(convert_radian(angle));
	rx = game->infos->res_width / game->infos->map_width;
	ry = game->infos->res_height / game->infos->map_height;
	while (game->infos->map_content[(int)y / ry][(int)x / rx] != '1')
	{
		x += i;
		y += j;
		if (game->infos->map_content[(int)y / ry][(int)x / rx] == '2' &&
							(int)x % rx == rx / 2 && (int)y % ry == ry / 2)
			ft_add_sprite(game, x, y, angle);
	}
	ft_sens(game, x, y) != 5 ? game->sens = ft_sens(game, x, y) : 1;
	ft_distance_to_wall(game, x, y, angle);
}
