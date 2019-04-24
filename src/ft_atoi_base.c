/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 12:11:39 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/03/30 12:11:40 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static	int		ft_power(int base, int len)
{
	int	i;
	int	res;

	if (len == 0)
		return (1);
	i = 1;
	res = base;
	while (i < len)
	{
		res *= base;
		i++;
	}
	return (res);
}

static	int		convert_num(char c, int base)
{
	int	res;

	if (c >= '0' && c <= '9')
		res = c - 48;
	else if (c >= 'a' && c <= 'z')
		res = c - 97 + 10;
	else if (c >= 'A' && c <= 'Z')
		res = c - 65 + 10;
	else
		res = -1;
	if (res < base && res != -1)
		return (res);
	else
		return (-1);
}

static	int		num_len(char *str, int base)
{
	int	len;

	len = 0;
	while (str[len])
	{
		if (convert_num(str[len], base) == -1)
			break ;
		len++;
	}
	return (len);
}

int				ft_atoi_base(char *nb, int base)
{
	int	res;
	int	len;

	if (base == 10)
		return (ft_atoi(nb));
	while (*nb == ' ' || *nb == '\t' || *nb == '\n')
		nb++;
	res = 0;
	len = num_len(nb, base) - 1;
	while (*nb && len >= 0 && convert_num(*nb, base) != -1)
	{
		res += convert_num(*nb, base) * ft_power(base, len);
		nb++;
		len--;
	}
	return (res);
}
