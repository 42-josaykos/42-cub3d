/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_macos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 12:58:59 by jonny             #+#    #+#             */
/*   Updated: 2020/07/30 13:09:11 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_get_resolution(char *line, t_info *infos, void *mlx_ptr)
{
	int		i;

	(void)mlx_ptr;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		if (line[i] >= '0' && line[i] <= '9')
		{
			if (infos->res_width > 0)
			{
				infos->res_height = fmin(ft_atoi_index(line, &i), 1440);
				break ;
			}
			else
				infos->res_width = fmin(ft_atoi_index(line, &i), 2560);
		}
		i++;
	}
}
