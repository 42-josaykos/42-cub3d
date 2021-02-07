/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_linux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 13:01:08 by jonny             #+#    #+#             */
/*   Updated: 2020/07/30 13:02:21 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_get_resolution(char *line, t_info *infos, void *mlx_ptr)
{
	int i;
	int width;
	int height;

	i = 0;
	mlx_get_screen_size(mlx_ptr, &width, &height);
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] >= '0' && line[i] <= '9')
		{
			if (infos->res_width > 0)
			{
				infos->res_height = fmin(ft_atoi_index(line, &i), height);
				break ;
			}
			else
				infos->res_width = fmin(ft_atoi_index(line, &i), width);
		}
		i++;
	}
}
