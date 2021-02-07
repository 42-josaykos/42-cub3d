/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:59:30 by alpascal          #+#    #+#             */
/*   Updated: 2020/08/03 18:11:43 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	camera(t_window *game)
{
	double			x;
	double			y;
	double			angle;

	game->xscreen = 0;
	angle = game->cam->angle - (90.0 - FOV);
	ft_draw_ground(game);
	while (angle < game->cam->angle + (90.0 - FOV))
	{
		x = game->cam->xpos;
		y = game->cam->ypos;
		raycast(game, x, y, angle);
		angle += (FOV / game->infos->res_width);
	}
	ft_display_sprites(game);
	ft_draw_interface(game);
}

void	test_event(t_window *game)
{
	if (game->key == MOVE_LEFT)
		move_left(game);
	if (game->key == MOVE_RIGHT)
		move_right(game);
	if (game->key == MOVE_UP)
		move_forward(game);
	if (game->key == MOVE_DOWN)
		move_backward(game);
	if (game->key == LOOK_LEFT)
		rotate(game, -1);
	if (game->key == LOOK_RIGHT)
		rotate(game, 1);
}

int		update_frame(t_window *game)
{
	game->data_ptr = create_img(game);
	test_event(game);
	camera(game);
	if (game->screenshot == 1)
		screenshot(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
								game->data_ptr->img_ptr, 0, 0);
	mlx_destroy_image(game->mlx_ptr, game->data_ptr->img_ptr);
	del_mem(game->data_ptr);
	return (0);
}

void	check_data(t_window *game)
{
	if (!game->cam->xpos || !game->cam->ypos)
		error_message(game, "Map data error (3)");
	if (!game->infos->ceil_color || !game->infos->floor_color)
		error_message(game, "Color error");
}

int		main(int argc, char **argv)
{
	t_window	*game;

	game = init_game();
	check_args(argc, argv, game);
	get_position(game);
	check_data(game);
	game->key = 0;
	ft_init_sprite(game);
	ft_init_textures(game);
	mlx_loop_hook(game->mlx_ptr, update_frame, game);
	if (game->screenshot == 0)
	{
		game->win_ptr = mlx_new_window(game->mlx_ptr, game->infos->res_width,
											game->infos->res_height, "Cub3D");
		mlx_hook(game->win_ptr, 2, 1L << 0, deal_key, game);
		mlx_hook(game->win_ptr, 3, 1L << 1, key_release, game);
		mlx_hook(game->win_ptr, 17, 1L << 17, exit_hook, game);
	}
	mlx_loop(game->mlx_ptr);
	return (0);
}
