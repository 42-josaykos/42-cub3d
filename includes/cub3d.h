/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:02:08 by alpascal          #+#    #+#             */
/*   Updated: 2020/07/30 19:59:54 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "fcntl.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>

# if LINUX
#  define ESC 0xFF1B
#  define LEFT 0x0061
#  define RIGHT 0x0064
#  define UP_1 0x0077
#  define UP_2 0xFF52
#  define DOWN_1 0x0073
#  define DOWN_2 0xFF54
#  define RIGHT_ARROW 0xFF53
#  define LEFT_ARROW 0xFF51
# else
#  define ESC 53
#  define LEFT 0
#  define RIGHT 2
#  define UP_1 126
#  define UP_2 13
#  define DOWN_1 125
#  define DOWN_2 1
#  define RIGHT_ARROW 124
#  define LEFT_ARROW 123
# endif

/*
** Keys mapping
*/

# define MOVE_LEFT 1
# define MOVE_RIGHT 2
# define MOVE_UP 3
# define MOVE_DOWN 4
# define LOOK_LEFT 5
# define LOOK_RIGHT 6
# define OPEN_MAP 7

# define FOV 60.0
# define ROTATE_SPEED 3.0
# define PLAYER_SPEED 3.0

typedef struct		s_vect2d
{
	double			x;
	double			y;
}					t_vect2d;

typedef struct		s_sprite
{
	double			xcenter;
	double			ycenter;
	double			angle;
	double			xscreen;
	int				distance;
}					t_sprite;

typedef struct		s_data
{
	void			*img_ptr;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;

typedef struct		s_camera
{
	double			xpos;
	double			ypos;
	double			angle;
}					t_camera;

typedef struct		s_color
{
	int				alpha;
	int				red;
	int				green;
	int				blue;

}					t_color;

typedef struct		s_info
{
	int				block_size;
	long int		res_width;
	long int		res_height;
	int				map_width;
	int				map_height;
	int				floor_color;
	int				ceil_color;
	char			*no_text;
	char			*so_text;
	char			*we_text;
	char			*ea_text;
	char			*sprite_text;
	unsigned char	floor[4];
	unsigned char	ceil[4];
	char			**map_content;
}					t_info;

typedef struct		s_texture
{
	int				width;
	int				height;
	char			*file;
	char			*data;
	void			*text_ptr;
}					t_texture;

typedef struct		s_window
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_data			*data_ptr;
	t_camera		*cam;
	t_sprite		*spr;
	t_info			*infos;
	t_texture		*texture[6];
	t_sprite		sprite[5];
	int				key;
	double			xscreen;
	int				sens;
	int				screenshot;
}					t_window;

void				ft_get_resolution(char *line, t_info *infos, void *mlx_ptr);

/*
** cub3d_raycasting.c
*/

void				raycast(t_window *game, double x, double y, double angle);

/*
** cub3d_utils_1.c
*/
t_info				*get_info(const char *str, t_window *game);
void				*create_img(t_window *game);

/*
** cub3d_utils_2.c
*/

int					ft_atoi_index(const char *str, int *index);
double				convert_radian(double nbr);
float				mod(float a, float b);
void				ft_print_infos(t_info *infos);

/*
** cub3d_events.c
*/

int					key_release(int key_code, t_window *game);
int					deal_key(int key_code, t_window *game);
int					exit_hook(t_window *game);
int					quit_game(t_window *game);

/*
** cub3d_moves.c
*/

void				move_backward(t_window *game);
void				move_forward(t_window *game);
void				move_right(t_window *game);
void				move_left(t_window *game);
void				rotate(t_window *game, int direction);

/*
** cub3d_parsing_1.c
*/

void				*init_map_content(const char *str, t_window *game,
																t_info *infos);
void				*ft_fill_map(const char *str, t_window *game,
														t_info *infos, int *i);
void				ft_parse_line(char *line, t_info *infos, void *mlx_ptr);

/*
** cub3d_parsing_2.c
*/

t_camera			*get_position(t_window *game);
int					check_res(t_info *infos);

/*
** cub3d_parsing_3.c
*/

void				ft_get_texture(char *line, t_info *infos);
void				check_map_walls(t_window *game, t_info *infos);
void				check_angle(t_window *game, t_info *infos, int i, int j);

/*
** cub3d_textures.c
*/

t_texture			**ft_init_textures(t_window *game);
int					ft_sens(t_window *game, int x, int y);

/*
** cub3d_graphics.c
*/

void				draw_pixel(t_window *game, unsigned int x, unsigned int y,
														unsigned char color[4]);
int					get_pixel (t_window *game, unsigned int x, unsigned int y);
void				get_color(t_texture *texture, int x, int y,
															unsigned char *ret);
void				draw_map(t_window *game);
void				ft_draw_ground(t_window *game);

/*
** cub3d_debug.c
*/

void				ft_draw_wall(int y1, int y2, unsigned char color[4],
																t_window *game);
void				get_floor_color(char *line, t_info *infos);
void				get_ceil_color(char *line, t_info *infos);
int					create_trgb(int t, int r, int g, int b);
void				ft_draw_line2(t_vect2d start, t_vect2d end,
										unsigned char color[4], t_window *game);
void				del_mem(void *data);

/*
** cub3d_screenshot.c
*/

void				screenshot(t_window *game);

/*
** cub3d_errors.c
*/

void				error_message(t_window *game, char *str);
int					map_errors(t_info *infos);
void				*init_game(void);
void				*check_args(int argc, char **argv, t_window *game);

/*
** cub3d_sprites.c
*/

void				ft_init_sprite(t_window *game);
void				ft_add_sprite(t_window *game, double x, double y,
															double angle);
void				ft_display_sprites(t_window *game);

/*
** cub3d_sprites2.c
*/

void				ft_draw_sprite(t_window *game, double sprite_height,
										double pixel_height, t_sprite *sprite);

/*
** cub3d_interface.c
*/

void				ft_draw_interface(t_window *game);

/*
** cub3d_interface2.c
*/

void				ft_draw_pointer(t_window *game);

/*
** cub3d_memory.c
*/

void				free_map(t_window *game);
void				free_textures(t_window *game);
void				free_sprites(t_window *game);

#endif
