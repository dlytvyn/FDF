/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 12:17:06 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/03/30 12:17:08 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include "../libmlx/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include "../ft_printf/libft/libft.h"

# define WINDOW_X 1500
# define WINDOW_Y 1000
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

//
//typedef struct s_draw {
//    int         drawStart;
//    int         drawEnd;
//    int         tex_pixel;
//    int         img_pixel;
//}t_draw;
//

typedef struct  s_textures {
    int         texture_x;
    int         tex_type;
    double      wall_x;
    double      textureFloor_x;
    double      textureFloor_y;
    double      wall;
    double      player;
    double      current;
}               t_textures;


typedef struct      s_casting{
    double          dir_x;
    double          dir_y;
    int             stepX;
    int             stepY;
    int             mapX;
    int             mapY;
    int             hit;
    int             side;
    double          perpendicular_wall;
    int             lineH;
    double          sideDistX;
    double          sideDistY;
    double          deltaDistX;
    double          deltaDistY;
    t_textures      textures;
}                   t_casting;




typedef struct		s_gen
{
    int             **map;
	int				*field;
	char			*buf;
	char			**array;
	t_casting       casting;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				map_height;
	int				map_width;
	double          pos_x;
	double          pos_y;
	double          plane_x;
	double          plane_y;
	double          time;
	double          old_time;
	void			*init;
	void			*window;
	void			*image;
	double			scale;
	int				flag;
}					t_gen;

void				centering(t_gen *gen);
void				minus_coor(t_gen *gen);
void				plus_coor(t_gen *gen);
void				increase(t_gen *gen, int a);
void				check_colors(t_gen *gen);
int					ft_atoi_base(char *nb, int base);
int					is_let(char *str);
int					is_hexa(char *str);
int					is_valid_data(char *str);
int					array_len(char **ar);
int					manage_keys(int key, t_gen *gen);
void				max_xy(t_gen *gen);
void				move_down(t_gen *gen);
void				move_up(t_gen *gen);
void				move_to_left(t_gen *gen);
void				move_to_right(t_gen *gen);
void				rotate_matrix(t_gen *gen, int key);
void				print_in_window(t_gen *gen);
void				reader(t_gen *gen, int fd);
void				get_scale(t_gen *gen);
void				ft_scale(t_gen *gen);
int					exit_x(t_gen *gen);
void				clear(t_gen *gen);
int					ft_printf(const char *format, ...);
void				show_str(t_gen *gen);
void				free_struct(t_gen *gen);
void				free_array(char **array);

#endif
