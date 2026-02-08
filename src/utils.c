/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 01:13:38 by alex              #+#    #+#             */
/*   Updated: 2025/04/03 13:08:42 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double	ft_atodbl_aux(char *nptr, int *i, int sing);

double	ft_atodbl(const char *nptr)
{
	long	sing;
	int		i;

	sing = 1;
	i = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sing = -1;
		i++;
	}
	if (nptr[i] == '.')
		return (0);
	return (ft_atodbl_aux((char *)nptr, &i, sing));
}

static double	ft_atodbl_aux(char *nptr, int *i, int sing)
{
	long	num;
	int		point_control;
	double	result;
	int		div;

	point_control = 0;
	num = 0;
	div = -1;
	while ((nptr[*i] >= '0' && nptr[*i] <= '9') || nptr[*i] == '.')
	{
		if (nptr[*i] == '.' && point_control == 0)
		{
			div = *i;
			point_control = 1;
		}
		else if (point_control == 1 && nptr[*i] == '.')
			return (0);
		else
			num = num * 10 + (nptr[*i] - '0');
		(*i)++;
	}
	if (div == -1)
		return (num * sing);
	result = (double)num / (double)ft_power_of(10, *i - div - 1);
	return (result * sing);
}

char	**load_args_table(int num_args, char **argv)
{
	char	**table_args;
	int		i;

	if (num_args <= 0 || !argv)
		return (NULL);
	table_args = (char **)malloc(sizeof(char *) * (num_args + 1));
	if (!table_args)
		return (NULL);
	i = 0;
	while (i < num_args)
	{
		table_args[i] = argv[num_args + i];
		i++;
	}
	table_args[num_args] = NULL;
	return (table_args);
}
