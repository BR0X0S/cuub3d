/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 07:44:44 by oumondad          #+#    #+#             */
/*   Updated: 2024/12/23 21:50:26 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_game *cub, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < P_SIZE)
	{
		j = 0;
		while (j < P_SIZE)
		{
			ft_pixelput(cub, cub->player.pixel_x + i,
				cub->player.pixel_y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_square(t_game *cub, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < SQ_SIZE)
	{
		j = 0;
		while (j < SQ_SIZE)
		{
			ft_pixelput(cub, x * SQ_SIZE + i, y * SQ_SIZE + j, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_game *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == '1')
				draw_square(cub, j, i, 0x0000008B);
			else if (cub->map[i][j] == '0' || cub->map[i][j] == 'E'
			|| cub->map[i][j] == 'N' || cub->map[i][j] == 'W'
			|| cub->map[i][j] == 'S')
				draw_square(cub, j, i, 0x00ADD8E6);
			j++;
		}
		i++;
	}
}

double	line_length(t_game *cub, double angle)
{
	double	x;
	double	y;
	double	length;

	x = cub->player.pixel_x;
	y = cub->player.pixel_y;
	length = 0;
	while (cub->map[(int)(y / SQ_SIZE)][(int)(x / SQ_SIZE)] != '1')
	{
		x += cos(angle);
		y += sin(angle);
		length += 1;
	}
	return (length - 5);
}
