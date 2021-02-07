/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 11:28:09 by josaykos          #+#    #+#             */
/*   Updated: 2020/05/31 18:25:01 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_forward(t_window *game)
{
	double y;
	double x;

	y = ((game->cam->ypos + (sin(convert_radian(game->cam->angle)) * 5.0 *
		PLAYER_SPEED * (game->infos->res_width + game->infos->res_height)
		/ 1600)) / (game->infos->res_height / game->infos->map_height));
	x = ((game->cam->xpos + (cos(convert_radian(game->cam->angle)) * 5.0 *
		PLAYER_SPEED * (game->infos->res_width + game->infos->res_height)
		/ 1600)) / (game->infos->res_width / game->infos->map_width));
	if (game->infos->map_content[(int)y][(int)x] != '1')
	{
		game->cam->xpos += cos(convert_radian(game->cam->angle)) * PLAYER_SPEED
		* (game->infos->res_width + game->infos->res_height) / 1600;
		game->cam->ypos += sin(convert_radian(game->cam->angle)) * PLAYER_SPEED
		* (game->infos->res_width + game->infos->res_height) / 1600;
	}
}

void	move_backward(t_window *game)
{
	double y;
	double x;

	y = ((game->cam->ypos - (sin(convert_radian(game->cam->angle)) * 5.0 *
		PLAYER_SPEED * (game->infos->res_width + game->infos->res_height)
		/ 1600)) / (game->infos->res_height / game->infos->map_height));
	x = ((game->cam->xpos - (cos(convert_radian(game->cam->angle)) * 5.0 *
		PLAYER_SPEED * (game->infos->res_width + game->infos->res_height)
		/ 1600)) / (game->infos->res_width / game->infos->map_width));
	if (game->infos->map_content[(int)y][(int)x] != '1')
	{
		game->cam->xpos -= cos(convert_radian(game->cam->angle)) * PLAYER_SPEED
		* (game->infos->res_width + game->infos->res_height) / 1600;
		game->cam->ypos -= sin(convert_radian(game->cam->angle)) * PLAYER_SPEED
		* (game->infos->res_width + game->infos->res_height) / 1600;
	}
}

void	move_right(t_window *game)
{
	double y;
	double x;

	y = ((game->cam->ypos - (sin(convert_radian(game->cam->angle - 90.0)) * 5.0
		* PLAYER_SPEED * (game->infos->res_width + game->infos->res_height)
		/ 1600)) / (game->infos->res_height / game->infos->map_height));
	x = ((game->cam->xpos - (cos(convert_radian(game->cam->angle - 90.0)) * 5.0
		* PLAYER_SPEED * (game->infos->res_width + game->infos->res_height)
		/ 1600)) / (game->infos->res_width / game->infos->map_width));
	if (game->infos->map_content[(int)y][(int)x] != '1')
	{
		game->cam->xpos -= cos(convert_radian(game->cam->angle - 90.0)) *
			PLAYER_SPEED * (game->infos->res_width + game->infos->res_height)
			/ 1600;
		game->cam->ypos -= sin(convert_radian(game->cam->angle - 90.0)) *
			PLAYER_SPEED * (game->infos->res_width + game->infos->res_height)
			/ 1600;
	}
}

void	move_left(t_window *game)
{
	double y;
	double x;

	y = ((game->cam->ypos - (sin(convert_radian(game->cam->angle + 90.0)) * 5.0
		* PLAYER_SPEED * (game->infos->res_width + game->infos->res_height)
		/ 1600)) / (game->infos->res_height / game->infos->map_height));
	x = ((game->cam->xpos - (cos(convert_radian(game->cam->angle + 90.0)) * 5.0
		* PLAYER_SPEED * (game->infos->res_width + game->infos->res_height)
		/ 1600)) / (game->infos->res_width / game->infos->map_width));
	if (game->infos->map_content[(int)y][(int)x] != '1')
	{
		game->cam->xpos -= cos(convert_radian(game->cam->angle + 90.0)) *
			PLAYER_SPEED * (game->infos->res_width + game->infos->res_height)
			/ 1600;
		game->cam->ypos -= sin(convert_radian(game->cam->angle + 90.0)) *
			PLAYER_SPEED * (game->infos->res_width + game->infos->res_height)
			/ 1600;
	}
}

void	rotate(t_window *game, int direction)
{
	game->cam->angle += direction * ROTATE_SPEED
	* (game->infos->res_width + game->infos->res_height) / 1600;
	game->cam->angle = mod(game->cam->angle, 360.0);
}
