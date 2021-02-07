/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 13:49:01 by josaykos          #+#    #+#             */
/*   Updated: 2020/07/30 20:01:44 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			create_trgb(int t, int r, int g, int b)
{
	return (b << 24 | g << 16 | r << 8 | t);
}

void		ft_load_textures(t_window *game, char *filename, int i)
{
	int param[3];
	int fd;

	game->texture[i] = ft_calloc(sizeof(t_texture), 1);
	game->texture[i]->text_ptr = mlx_xpm_file_to_image(game->mlx_ptr, filename,
						&game->texture[i]->width, &game->texture[i]->height);
	param[0] = 32;
	param[1] = game->texture[i]->width * 4;
	param[2] = 0;
	if ((fd = open(filename, O_RDONLY)) >= 0)
		game->texture[i]->data = mlx_get_data_addr(game->texture[i]->text_ptr,
											&param[0], &param[1], &param[2]);
	else
	{
		game->texture[i]->data = NULL;
		error_message(game, "Texture error");
	}
	close(fd);
}

t_texture	**ft_init_textures(t_window *game)
{
	if (game->infos->so_text == NULL || game->infos->no_text == NULL
			|| game->infos->ea_text == NULL || game->infos->we_text == NULL)
		error_message(game, "Texture info is missing");
	ft_load_textures(game, game->infos->so_text, 0);
	ft_load_textures(game, game->infos->no_text, 1);
	ft_load_textures(game, game->infos->ea_text, 2);
	ft_load_textures(game, game->infos->we_text, 3);
	ft_load_textures(game, game->infos->sprite_text, 4);
	ft_load_textures(game, "texture/pistol1.xpm", 5);
	return (game->texture);
}

int			ft_sens(t_window *game, int x, int y)
{
	int rx;
	int ry;

	rx = game->infos->res_width / game->infos->map_width;
	ry = game->infos->res_height / game->infos->map_height;
	if (game->infos->map_content[(y - 1) / ry][x / rx] != '1'
			&& y > game->cam->ypos)
		return (0);
	if (game->infos->map_content[(y + 1) / ry][x / rx] != '1'
			&& y < game->cam->ypos)
		return (1);
	if (game->infos->map_content[y / ry][(x - 1) / rx] != '1'
			&& x > game->cam->xpos)
		return (2);
	if (game->infos->map_content[y / ry][(x + 1) / rx] != '1'
			&& x < game->cam->xpos)
		return (3);
	return (5);
}
