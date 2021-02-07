/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 11:23:58 by josaykos          #+#    #+#             */
/*   Updated: 2020/07/30 20:04:53 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		key_release(int key_code, t_window *game)
{
	(void)key_code;
	game->key = 0;
	return (0);
}

int		quit_game(t_window *game)
{
	free_textures(game);
	if (game->infos != NULL)
	{
		free_map(game);
		del_mem(game->infos->no_text);
		del_mem(game->infos->so_text);
		del_mem(game->infos->we_text);
		del_mem(game->infos->ea_text);
		del_mem(game->infos->sprite_text);
	}
	del_mem(game->infos);
	del_mem(game->cam);
	if (game->win_ptr != NULL)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	del_mem(game->mlx_ptr);
	del_mem(game);
	ft_printf("Cub3D closed\n");
	exit(0);
}

int		exit_hook(t_window *game)
{
	quit_game(game);
	return (0);
}

int		deal_key(int key_code, t_window *game)
{
	if (key_code == ESC)
		quit_game(game);
	else if (key_code == LEFT)
		game->key = MOVE_LEFT;
	else if (key_code == RIGHT)
		game->key = MOVE_RIGHT;
	else if (key_code == UP_1 || key_code == UP_2)
		game->key = MOVE_UP;
	else if (key_code == DOWN_1 || key_code == DOWN_2)
		game->key = MOVE_DOWN;
	else if (key_code == LEFT_ARROW)
		game->key = LOOK_LEFT;
	else if (key_code == RIGHT_ARROW)
		game->key = LOOK_RIGHT;
	return (0);
}
