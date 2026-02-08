/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 05:56:59 by alex              #+#    #+#             */
/*   Updated: 2026/02/06 06:44:49 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argz, char **argv)
{
	t_mlx_enviroment	mlx;
	t_image_data		img_data;

	if (argz < 2)
	{
		ft_putstr_fd("Need more arguments\n", 2);
		exit (0);
	}
	if (!select_set_to_render(&img_data, argv, argz))
		return (1);
	if (!setup_mlx_enviroment(&mlx, &img_data))
		return (1);
	mlx_loop(mlx.mlx_var);
	return (0);
}
