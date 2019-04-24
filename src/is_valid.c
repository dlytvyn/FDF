///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   is_valid.c                                         :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2018/03/30 12:11:51 by dlytvyn           #+#    #+#             */
///*   Updated: 2018/03/30 12:11:52 by dlytvyn          ###   ########.fr       */
///*                                                                            */
///* ************************************************************************** */
//
//#include "fdf.h"
//
//int		array_len(char **ar)
//{
//	int	i;
//
//	i = 0;
//	while (ar[i])
//		i++;
//	return (i);
//}
//
//int		is_valid_data(char *str)
//{
//	char	*com;
//	int		i;
//
//	com = ft_strdup("-0123456789,xabcdefABCDEF");
//	i = 0;
//	while (str[i])
//	{
//		if (ft_strchr(com, str[i]) == 0)
//		{
//			free(com);
//			return (0);
//		}
//		i++;
//	}
//	free(com);
//	return (1);
//}
//
//int		is_hexa(char *str)
//{
//	char	*com;
//	int		i;
//
//	com = ft_strdup("0123456789abcdefABCDEF");
//	i = 0;
//	while (str[i])
//	{
//		if (ft_strchr(com, str[i]) == 0)
//		{
//			free(com);
//			return (0);
//		}
//		i++;
//	}
//	free(com);
//	return (1);
//}
//
//int		is_let(char *str)
//{
//	char	*com;
//	int		i;
//
//	com = ft_strdup("abcdefABCDEF");
//	i = 0;
//	while (str[i])
//	{
//		if (ft_strchr(com, str[i]))
//		{
//			free(com);
//			return (1);
//		}
//		i++;
//	}
//	free(com);
//	return (0);
//}
