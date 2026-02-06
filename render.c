/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 01:07:47 by alex              #+#    #+#             */
/*   Updated: 2026/02/06 06:45:53 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	scale_xy_to_image_coords(t_complex_factors *z, int x, int y)
{
	double	scale_x;
	double	scale_y;
	double	adjusted_x;
	double	adjusted_y;

	adjusted_y = (double)(y);
	adjusted_x = (double)(x);
	scale_y = (double)(MAND_MAX_Y - MAND_MIN_Y) / (HEIGHT - 0);
	scale_x = (double)(MAND_MAX_X - MAND_MIN_X) / (WIDTH - 0);
	z->real = MAND_MIN_X + (adjusted_x * scale_x);
	z->imaginary = MAND_MIN_Y + (adjusted_y * scale_y);
}

void	apply_zoom_and_moves(t_complex_factors	*z, t_image_data *img)
{
	z->real = (z->real / img->zoom) + img->with[0];
	z->imaginary = (z->imaginary / img->zoom) + img->with[1];
}

void	buffering_pixel(int x, int y, t_image_data *img, int color)
{
	unsigned int	offset;

	offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
	*(unsigned int *)(img->bit_map_address + offset) = color;
}

int	render_set(t_mlx_enviroment *mlx)
{
	t_complex_factors	z;
	int					pixel_color;
	int					x;
	int					y;

	x = -1 ;
	while (++x < HEIGHT)
	{
		y = -1;
		while (++y < WIDTH)
		{
			scale_xy_to_image_coords(&z, x, y);
			apply_zoom_and_moves(&z, mlx->img_data);
			pixel_color = mlx->img_data->set_def(mlx->img_data, &z);
			buffering_pixel(x, y, mlx->img_data, pixel_color);
		}
	}
	mlx_put_image_to_window(mlx->mlx_var, mlx->window,
		mlx->img_data->img_var, 0, 0);
	return (0);
}
