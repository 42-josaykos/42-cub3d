/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 13:00:38 by jonny             #+#    #+#             */
/*   Updated: 2020/06/19 11:41:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_init_sprite(t_window *game)
{
	int			i;
	t_sprite	*sprite;

	i = 0;
	while (i < 5)
	{
		sprite = ft_calloc(sizeof(t_sprite), 1);
		sprite->distance = 0;
		game->sprite[i] = *sprite;
		free(sprite);
		i++;
	}
}

void	ft_add_sprite(t_window *game, double x, double y, double angle)
{
	int	i;
	int	rx;
	int	ry;
	int	distance;

	i = 0;
	distance = sqrt(pow(game->cam->xpos - (int)x, 2) +
					pow(game->cam->ypos - (int)y, 2));
	rx = game->infos->res_width / game->infos->map_width;
	ry = game->infos->res_height / game->infos->map_height;
	if ((sqrt(pow(game->cam->xpos - (int)x, 2) +
		pow(game->cam->ypos - (int)y, 2)) > ((rx + ry) / 5)))
	{
		while (game->sprite[i].distance && i < 4)
			i++;
		if (!(game->sprite[i].distance) && i <= 5)
		{
			game->sprite[i].xcenter = x;
			game->sprite[i].ycenter = y;
			game->sprite[i].angle = angle;
			game->sprite[i].xscreen = game->xscreen;
			if (game->sprite[abs(i - 1)].distance != distance)
				game->sprite[i].distance = distance;
		}
	}
}

void	ft_sort_sprites(t_sprite *sprite)
{
	t_sprite	inter;
	int			i;

	i = 1;
	while (sprite[i].distance != 0 && i < 5)
	{
		if (sprite[i].distance > sprite[i - 1].distance)
		{
			inter = sprite[i];
			sprite[i] = sprite[i - 1];
			sprite[i - 1] = inter;
			i = 0;
		}
		i++;
	}
}

void	ft_distance_to_sprite(t_window *game, t_sprite *sprite)
{
	double correct_distance;
	double plane_distance;
	double sprite_height;
	double block_size;

	block_size = round(game->infos->res_height / game->infos->map_height);
	correct_distance = cos(convert_radian(fabs(sprite->angle -
					game->cam->angle))) * sprite->distance;
	plane_distance = (game->infos->res_width / 2.0) /
						tan(convert_radian(FOV / 2.0));
	sprite_height = round(block_size / correct_distance * plane_distance);
	ft_draw_sprite(game, sprite_height,
					(sprite_height / (game->texture[4]->height)), sprite);
}

void	ft_display_sprites(t_window *game)
{
	int i;

	i = 0;
	ft_sort_sprites(game->sprite);
	while (i <= 4 && game->sprite[i].distance)
	{
		ft_distance_to_sprite(game, &game->sprite[i]);
		game->sprite[i].distance = 0;
		i++;
	}
}
