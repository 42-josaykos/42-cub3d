/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 12:05:57 by jonny             #+#    #+#             */
/*   Updated: 2020/08/03 18:11:43 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	error_message(t_window *game, char *str)
{
	ft_printf("Error: %s\n", str);
	quit_game(game);
}

int		map_errors(t_info *infos)
{
	if (infos->res_width < 320 || infos->res_height < 240)
		check_res(infos);
	return (1);
}

void	*init_game(void)
{
	t_window *game;

	if (!(game = ft_calloc(sizeof(t_window), 1)))
		return (NULL);
	game->mlx_ptr = mlx_init();
	return (game);
}

void	*check_args(int argc, char **argv, t_window *game)
{
	if (argc == 2)
	{
		get_info(argv[1], game);
		if (game->infos == NULL || !map_errors(game->infos))
			error_message(game, "Map data error (1)");
		return (game->infos);
	}
	else if (argc == 3)
	{
		if (!ft_strncmp(argv[2], "--save", 6) && ft_strlen(argv[2]) == 6)
			game->screenshot = 1;
		else
			error_message(game,
				"Incorrect arguments: Usage: ./Cub3D <map filepath> [--save]");
		get_info(argv[1], game);
		if (game->infos == NULL || !map_errors(game->infos))
			error_message(game, "Map data error (2)");
		return (game->infos);
	}
	else
		error_message(game,
				"Incorrect arguments: Usage: ./Cub3D <map filepath> [--save]");
	return (NULL);
}
