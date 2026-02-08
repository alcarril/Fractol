/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_treatment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 01:14:11 by alex              #+#    #+#             */
/*   Updated: 2025/04/03 04:46:34 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	fill_color_map_part1(int *color_map)
{
	color_map[0] = 0x36045d;
	color_map[1] = 0x420260;
	color_map[2] = 0x4d0062;
	color_map[3] = 0x580064;
	color_map[4] = 0x620066;
	color_map[5] = 0x6d0067;
	color_map[6] = 0x770068;
	color_map[7] = 0x820068;
	color_map[8] = 0x8c0068;
	color_map[9] = 0x960068;
	color_map[10] = 0x9f0067;
	color_map[11] = 0xa90066;
	color_map[12] = 0xb20065;
	color_map[13] = 0xba0063;
	color_map[14] = 0xc30361;
	color_map[15] = 0xcb115f;
	color_map[16] = 0xd31c5d;
	color_map[17] = 0xda255a;
	color_map[18] = 0xe12f58;
	color_map[19] = 0xe83855;
	color_map[20] = 0xee4151;
}

static void	fill_color_map_part2(int *color_map)
{
	color_map[21] = 0xf34a4e;
	color_map[22] = 0xf9534a;
	color_map[23] = 0xfd5d46;
	color_map[24] = 0xff6642;
	color_map[25] = 0xff6f3e;
	color_map[26] = 0xff7939;
	color_map[27] = 0xff8336;
	color_map[28] = 0xff8e37;
	color_map[29] = 0xff9838;
	color_map[30] = 0xffa238;
	color_map[31] = 0xffac37;
	color_map[32] = 0xffb535;
	color_map[33] = 0xffbe30;
	color_map[34] = 0xffc724;
	color_map[35] = 0xffd000;
	color_map[36] = 0xffda00;
	color_map[37] = 0xffe400;
	color_map[38] = 0xffed00;
	color_map[39] = 0xfff700;
}

int	get_color_from_palethe(int i, int max_i)
{
	int	color_map[40];

	fill_color_map_part1(color_map);
	fill_color_map_part2(color_map);
	return (select_color(color_map, i, max_i));
}

int	select_color(int *color_map, int i, int max_i)
{
	double	factor;

	factor = (39 / (double)max_i);
	i = factor * (double)i;
	if (i > 39)
		i = 39;
	else if (i < 0)
		i = 0;
	return (color_map[i]);
}
