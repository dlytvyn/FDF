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
# include "../minilibx/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../GNL/get_next_line.h"

# define WINDOW_X 1500
# define WINDOW_Y 1000
# define SCALE 50

typedef struct		s_fdf
{
	double			x;
	double			z;
	double			y;
	int				color;
}					t_fdf;

typedef struct		s_gen
{
	struct s_fdf	**list;
	int				*field;
	char			*buf;
	char			**array;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				w_h;
	int				w_w;
	int				max_x;
	int				max_y;
	int				min_x;
	int				min_y;
	void			*init;
	void			*window;
	void			*image;
	double			scale;
	double			diff_x;
	double			diff_y;
	double			deg_x;
	double			deg_y;
	double			deg_z;
	int				flag;
}					t_gen;

void				line(t_gen *gen, t_fdf t1, t_fdf t2);
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

#endif
