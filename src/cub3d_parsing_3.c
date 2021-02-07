/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parsing_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:32:00 by josaykos          #+#    #+#             */
/*   Updated: 2020/07/30 19:14:44 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		get_sprite_texture(char *line, t_info *infos)
{
	if (line[0] == 'E' && line[1] == 'A')
	{
		while (*line == 'E' || *line == 'A' || *line == ' ' || *line == '\t')
			line++;
		infos->ea_text = ft_strdup(line);
	}
	else if (line[0] == 'S' && line[1] == ' ')
	{
		while (*line == 'S' || *line == ' ' || *line == '\t')
			line++;
		infos->sprite_text = ft_strdup(line);
	}
}

void		ft_get_texture(char *line, t_info *infos)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (line[0] == 'N' && line[1] == 'O')
	{
		while (*line == 'N' || *line == 'O' || *line == ' ' || *line == '\t')
			line++;
		infos->no_text = ft_strdup(line);
	}
	else if (line[0] == 'S' && line[1] == 'O')
	{
		while (*line == 'S' || *line == 'O' || *line == ' ' || *line == '\t')
			line++;
		infos->so_text = ft_strdup(line);
	}
	else if (line[0] == 'W' && line[1] == 'E')
	{
		while (*line == 'W' || *line == 'E' || *line == ' ' || *line == '\t')
			line++;
		infos->we_text = ft_strdup(line);
	}
	get_sprite_texture(line, infos);
}

void		check_angle(t_window *game, t_info *infos, int i, int j)
{
	if (infos->map_content[i - 1][j] == '1')
	{
		if (infos->map_content[i][j + 1] == '1' &&
				infos->map_content[i - 1][j + 1] != '1')
			error_message(game, "map error: incomplete angle (up right)");
		else if (infos->map_content[i][j - 1] == '1' &&
				infos->map_content[i - 1][j - 1] != '1')
			error_message(game, "map error: incomplete angle (up left)");
	}
	else if (infos->map_content[i + 1][j] == '1')
	{
		if (infos->map_content[i][j + 1] == '1' &&
				infos->map_content[i + 1][j + 1] != '1')
			error_message(game, "map error: incomplete angle (down right)");
		else if (infos->map_content[i][j - 1] == '1' &&
				infos->map_content[i + 1][j - 1] != '1')
			error_message(game, "map error: incomplete angle (down left)");
	}
}

void		check_zero_char(t_window *game, t_info *infos, int i, int j)
{
	if (i == 0 || i == infos->map_height - 1 || j == 0)
		error_message(game, "map error: hole in the walls");
	else if (infos->map_content[i][j + 1] == ' ' ||
			infos->map_content[i][j + 1] == '\0')
		error_message(game, "Map error: hole in the walls (right)");
	else if (i != 0 && (infos->map_content[i - 1][j] == ' ' ||
				infos->map_content[i - 1][j] == '\0'))
		error_message(game, "map error: hole int the walls (top)");
	else if (infos->map_content[i][j - 1] == ' ' ||
										infos->map_content[i][j + 1] == '\0')
		error_message(game, "Map error: hole in the walls (left)");
	else if (i != infos->map_height - 1 && (infos->map_content[i + 1][j] == ' '
									|| infos->map_content[i + 1][j] == '\0'))
		error_message(game, "map error: hole int the walls (bottom)");
	else if (infos->map_content[i - 1][j] == '1' ||
											infos->map_content[i + 1][j] == '1')
		check_angle(game, infos, i, j);
}

void		check_map_walls(t_window *game, t_info *infos)
{
	int		i;
	int		j;

	i = 0;
	while (i < infos->map_height)
	{
		j = 0;
		while (infos->map_content[i][j] != '\0')
		{
			if (infos->map_content[i][j] != '0' && infos->map_content[i][j] !=
			'1' && infos->map_content[i][j] != '2' && infos->map_content[i][j]
			!= ' ' && infos->map_content[i][j] != '\t' &&
			infos->map_content[i][j] != 'N' && infos->map_content[i][j] != 'S'
			&& infos->map_content[i][j] != 'W'
			&& infos->map_content[i][j] != 'E')
				error_message(game, "map error: bad character");
			if (infos->map_content[i][j] != '1' &&
			infos->map_content[i][j] != ' ' && infos->map_content[i][j] != '\0')
				check_zero_char(game, infos, i, j);
			j++;
		}
		i++;
	}
}
