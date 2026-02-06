/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cgi_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 01:09:46 by alex              #+#    #+#             */
/*   Updated: 2025/12/27 11:12:25 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

char	select_set_to_render(t_image_data *img, char **argv, int argz)
{
	if (!ft_strncmp(argv[1], "Mandelbrot", 10) && ft_strlen(argv[1]) == 10)
	{
		if (argz > 2)
			return (ft_putstr_fd("Too many arguments for Mandelbrot\n", 2), 0);
		img->name = "Mandelbrot";
		img->set_def = mandelbrot_set;
		img->config = load_args_table(argz - 2, argv);
	}
	else if (!ft_strncmp(argv[1], "Julia", 5) && ft_strlen(argv[1]) == 5)
	{
		if (argz != 4)
			return (ft_putstr_fd(JULIA_ERRORS, 2), 0);
		img->name = "Julia";
		img->set_def = julia_set;
		img->config = load_args_table(argz - 2, argv);
	}
	else
		return (ft_putstr_fd("You have to chose Mandelbrot or Julia\n", 2), 0);
	return (1);
}

char	setup_mlx_enviroment(t_mlx_enviroment *mlx, t_image_data *img)
{
	if (!mlx)
		return (0);
	mlx->mlx_var = mlx_init();
	if (!mlx->mlx_var)
		return (0);
	mlx->window = mlx_new_window(mlx->mlx_var, WIDTH, HEIGHT, img->name);
	if (!mlx->window)
		return (destroy_mlx_componets(0, mlx_destroy_window, 0, mlx), 0);
	img->img_var = mlx_new_image(mlx->mlx_var, HEIGHT, WIDTH);
	if (!img->img_var)
		return (destroy_mlx_componets(0, mlx_destroy_window,
				mlx_destroy_display, mlx), 0);
	img->bit_map_address = mlx_get_data_addr(img->img_var,
			&(img->bits_per_pixel), &(img->line_length), &(img->endian));
	if (!img->bit_map_address)
		return (destroy_mlx_componets(mlx_destroy_image, mlx_destroy_window,
				mlx_destroy_display, mlx), 0);
	img->bit_map_address_copy = img->bit_map_address;
	mlx->img_data = img;
	set_default_values(img);
	create_hooks(mlx);
	return (1);
}

void	set_default_values(t_image_data *img)
{
	int	origin_x;
	int	origin_y;

	if (WIDTH % 2 == 0)
		origin_x = WIDTH / 2;
	else
		origin_x = (WIDTH / 2) + 1;
	if (HEIGHT % 2 == 0)
		origin_y = HEIGHT / 2;
	else
		origin_y = (WIDTH / 2) + 1;
	img->origin[0] = origin_x;
	img->origin[1] = origin_y;
	img->with[0] = 0.0;
	img->with[1] = 0.0;
	img->zoom = 1.00;
	img->max_iter = 50;
}

void	create_hooks(t_mlx_enviroment *mlx)
{
	mlx_hook(mlx->window, KeyPress, KeyPressMask,
		manage_key, mlx);
	mlx_hook(mlx->window, ButtonPress, ButtonPressMask,
		manage_mouse, mlx);
	mlx_hook(mlx->window, DestroyNotify, StructureNotifyMask,
		close_handler, mlx);
	mlx_loop_hook(mlx->mlx_var, render_set, mlx);
}
