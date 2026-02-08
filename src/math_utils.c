/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 00:58:19 by alex              #+#    #+#             */
/*   Updated: 2025/04/03 05:21:42 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

size_t	ft_power_of(size_t num, int power)
{
	size_t	n_square;
	int		i;

	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	if (power == 1)
		return (num);
	if (power == 2)
		return (num * num);
	n_square = num * num;
	i = 2;
	while (i < power)
	{
		n_square = n_square * num;
		i++;
	}
	return (n_square);
}

double	power_of(double num, int power)
{
	double	n_square;
	int		i;

	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	if (power == 1)
		return (num);
	if (power == 2)
		return (n_square = num * num);
	n_square = num * num;
	i = 1;
	while (i < power)
	{
		n_square = n_square * num;
		i++;
	}
	return (n_square);
}
