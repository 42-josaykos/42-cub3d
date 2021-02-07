/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_screenshot.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 12:17:32 by jonny             #+#    #+#             */
/*   Updated: 2020/06/03 17:08:21 by josaykos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			int_to_char(int n, unsigned char *src)
{
	src[0] = (unsigned char)(n);
	src[1] = (unsigned char)(n >> 8);
	src[2] = (unsigned char)(n >> 16);
	src[3] = (unsigned char)(n >> 24);
}

static void		bmp_header(t_window *game, int fd, int filesize)
{
	int				i;
	unsigned char	data[54];

	i = -1;
	while (++i < 54)
		data[i] = 0;
	data[0] = (unsigned char)('B');
	data[1] = (unsigned char)('M');
	int_to_char(filesize, data + 2);
	data[10] = (unsigned char)(54);
	data[14] = (unsigned char)(40);
	int_to_char(game->infos->res_width, data + 18);
	int_to_char(game->infos->res_height, data + 22);
	data[26] = (unsigned char)(1);
	data[28] = (unsigned char)(24);
	write(fd, data, 54);
}

/*
** Get the INT value of the pixel x/y (color)
*/

int				get_pixel(t_window *game, unsigned int x, unsigned int y)
{
	int pix;

	pix = *(int*)(game->data_ptr->addr + (4 * game->infos->res_width *
			(game->infos->res_height - 1 - y)) + (4 * x));
	return ((pix & 0xFF0000) | (pix & 0x00FF00) | (pix & 0x0000FF));
}

static void		bmp_pixels(t_window *game, int fd, int pad)
{
	unsigned char	zero[3];
	unsigned int	i;
	unsigned int	j;
	int				color;

	i = -1;
	while (++i < 3)
		zero[i] = 0;
	i = 0;
	while (i < game->infos->res_height)
	{
		j = 0;
		while (j < game->infos->res_width)
		{
			color = get_pixel(game, j, i);
			write(fd, &color, 3);
			write(fd, &zero, pad);
			j++;
		}
		i++;
	}
}

void			screenshot(t_window *game)
{
	int fd;
	int filesize;
	int pad;

	game->screenshot = 0;
	pad = (4 - (game->infos->res_width * 3) % 4) % 4;
	filesize = 54 + (3 * (game->infos->res_width + pad) *
													game->infos->res_height);
	if ((fd = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC |
														O_APPEND, 0666)) < 0)
		exit(0);
	bmp_header(game, fd, filesize);
	bmp_pixels(game, fd, pad);
	ft_printf("Image saved in ./screenshot.bmp !\n");
	mlx_destroy_image(game->mlx_ptr, game->data_ptr->img_ptr);
	del_mem(game->data_ptr);
	quit_game(game);
}
