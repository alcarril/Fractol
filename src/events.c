/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 08:43:31 by alex              #+#    #+#             */
/*   Updated: 2026/02/06 06:33:05 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	manage_key(int keysym, t_mlx_enviroment *mlx)
{
	if (keysym == XK_Escape)
		close_handler(mlx);
	if (keysym == XK_plus || keysym == XK_KP_Add)
	{
		mlx->img_data->max_iter += 10;
	}
	else if (keysym == XK_minus || keysym == XK_KP_Subtract)
	{
		mlx->img_data->max_iter -= 10;
	}
	manage_key2(keysym, mlx);
	return (0);
}

void	manage_key2(int keysym, t_mlx_enviroment *mlx)
{
	if (keysym == XK_Left)
	{
		mlx->img_data->with[0] -= (0.5 / mlx->img_data->zoom);
	}
	else if (keysym == XK_Right)
	{
		mlx->img_data->with[0] += (0.5 / mlx->img_data->zoom);
	}
	else if (keysym == XK_Up)
	{
		mlx->img_data->with[1] -= (0.5 / mlx->img_data->zoom);
	}
	else if (keysym == XK_Down)
	{
		mlx->img_data->with[1] += (0.5 / mlx->img_data->zoom);
	}
}

int	manage_mouse(int button, int x, int y, t_mlx_enviroment *mlx)
{
	int	k;

	k = x + y;
	if (button == Button5 && k > INT_MIN)
	{
		mlx->img_data->zoom *= 0.95;
	}
	else if (button == Button4)
	{
		mlx->img_data->zoom *= 1.05;
	}
	return (0);
}

int	close_handler(t_mlx_enviroment *mlx)
{
	mlx_destroy_image(mlx->mlx_var,
		mlx->img_data->img_var);
	mlx_destroy_window(mlx->mlx_var,
		mlx->window);
	mlx_destroy_display(mlx->mlx_var);
	if (mlx->img_data->config)
		free(mlx->img_data->config);
	free(mlx->mlx_var);
	exit(0);
}

void	destroy_mlx_componets(int (*f)(), int (*g)(), int (*t)(),
	t_mlx_enviroment *mlx)
{
	if (f != NULL)
		f(mlx->mlx_var, mlx->img_data->img_var);
	if (g != NULL)
		g(mlx->mlx_var, mlx->window);
	if (t != NULL)
		t(mlx->mlx_var);
	free(mlx->mlx_var);
}
