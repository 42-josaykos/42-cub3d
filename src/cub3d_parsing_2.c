/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parsing_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 16:09:26 by josaykos          #+#    #+#             */
/*   Updated: 2020/08/05 13:25:08 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			check_res(t_info *infos)
{
	if (infos->res_width > 0 && infos->res_width < 320)
		infos->res_width = 320;
	if (infos->res_height > 0 && infos->res_height < 240)
		infos->res_height = 240;
	return (1);
}

void		ft_init_orientation(char c, t_camera *cam)
{
	if (c == 'E')
		cam->angle = 0;
	else if (c == 'S')
		cam->angle = 90;
	else if (c == 'W')
		cam->angle = 180;
	else if (c == 'N')
		cam->angle = -90;
}

void		check_position_validity(t_window *game, int x, int y)
{
	if (y == 0 || y == game->infos->map_height - 1 || x == 0)
		error_message(game, "map error: bad player position");
	else if (game->infos->map_content[y][x + 1] == ' ' ||
			game->infos->map_content[y][x + 1] == '\0')
		error_message(game, "Map error: bad player position(right)");
	else if (y != 0 && (game->infos->map_content[y - 1][x] == ' ' ||
				game->infos->map_content[y - 1][x] == '\0'))
		error_message(game, "map error: bad player position (top)");
	else if (game->infos->map_content[y][x - 1] == ' ' ||
									game->infos->map_content[y][x + 1] == '\0')
		error_message(game, "Map error: bad player position (left)");
	else if (y != game->infos->map_height - 1
			&& (game->infos->map_content[y + 1][x] == ' '
			|| game->infos->map_content[y + 1][x] == '\0'))
		error_message(game, "map error: bad player position (bottom)");
	else if (game->infos->map_content[y - 1][x] == '1' ||
									game->infos->map_content[y + 1][x] == '1')
		check_angle(game, game->infos, y, x);
}

void		ft_init_position(t_window *game, t_camera *cam, int x, int y)
{
	int block_width;
	int block_height;

	if (cam->xpos != 0 || cam->ypos != 0)
		error_message(game, "map error : multiple player positions");
	block_width = game->infos->res_width / game->infos->map_width;
	block_height = game->infos->res_height / game->infos->map_height;
	cam->xpos = x * block_width + (block_width / 2.0);
	cam->ypos = y * block_height + (block_height / 2.0);
	check_position_validity(game, x, y);
}

t_camera	*get_position(t_window *game)
{
	int			y;
	int			x;

	y = 0;
	if (!(game->cam = ft_calloc(sizeof(t_camera), 1)))
		return (NULL);
	while (y < game->infos->map_height)
	{
		x = 0;
		while (game->infos->map_content[y][x])
		{
			if (game->infos->map_content[y][x] &&
					(game->infos->map_content[y][x] == 'E' ||
					game->infos->map_content[y][x] == 'S' ||
					game->infos->map_content[y][x] == 'W' ||
					game->infos->map_content[y][x] == 'N'))
			{
				ft_init_orientation(game->infos->map_content[y][x], game->cam);
				ft_init_position(game, game->cam, x, y);
			}
			x++;
		}
		y++;
	}
	return (game->cam);
}
