/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 12:13:15 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/03/30 12:13:16 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int array_len(char **ar)
{
    int i = 0;

    while (ar[i])
        i++;
    return (i);
}

static	void	separate_add(t_gen *gen)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (i < gen->map_height)
	{
		j = 0;
		gen->map[i] = (int*)malloc(sizeof(int) * gen->map_width);
		while (j < gen->map_width)
		{
			if (gen->array[i][j] < '0' || gen->array[i][j] > '9')
            {
                ft_printf("Invalid value in map\n");
                exit(0);
            }
			gen->map[i][j] = gen->array[i][j] - '0';
			++j;
		}
		i++;
	}
}

static	void	separate_data(t_gen *gen)
{
	gen->array = ft_strsplit(gen->buf, ' ');

    int i = 0;
    while (gen->array[i])
    {
        ft_printf("Line %s\n", gen->array[i]);
        i++;
    }


	ft_strdel(&gen->buf);
    ft_printf("Array len =  %d\n", array_len(gen->array));
	if (gen->map_height!= array_len(gen->array))
	{
		ft_printf("{red}%s{reset}\n", "Found wrong line length. Exiting.");
		exit_x(gen);
	}
	else if (array_len(gen->array) == 0)
	{
		ft_printf("{red}%s{reset}\n", "Error! No map found!");
		exit_x(gen);
	}
	gen->map = (int**)malloc(sizeof(int*) * gen->map_height);
	separate_add(gen);
}

static	void	go_out(void)
{
	ft_printf("{red}%s{reset}\n", "Error! There is no file or empty file!");
	exit(0);
}

void			reader(t_gen *gen, int fd)
{
	char	*tmp;
	char	*line;
	char	**array;

	if (get_next_line(fd, &line) <= 0)
		go_out();
	array = ft_strsplit(line, ' ');
	ft_strdel(&line);
	if (array_len(array) != 2)
    {
	    go_out();
    }
	else
    {
        gen->map_width = ft_atoi(array[0]);
        gen->map_height = ft_atoi(array[1]);
    }
    ft_printf("Width =  %d\n", gen->map_width);
    ft_printf("Height =  %d\n", gen->map_height);
	free_array(array);
	while (get_next_line(fd, &line))
	{
		tmp = ft_strdup(gen->buf);
		ft_strdel(&gen->buf);
		gen->buf = ft_strjoin(tmp, " ");
		ft_strdel(&tmp);
		tmp = ft_strdup(gen->buf);
		ft_strdel(&gen->buf);
		gen->buf = ft_strjoin(tmp, line);
		ft_strdel(&tmp);
		ft_strdel(&line);
	}
	separate_data(gen);
}
