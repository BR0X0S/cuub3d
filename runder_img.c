/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runder_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:36:27 by broxos            #+#    #+#             */
/*   Updated: 2024/12/23 21:56:01 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render_scene(t_game *cub)
{
	if (cub->left)
		cub->player_angle -= 0.1;
	if (cub->right)
		cub->player_angle += 0.1;
	if (cub->w)
		move_player(cub, 0);
	if (cub->s)
		move_player(cub, PI);
	if (cub->a)
		walk_left(cub);
	if (cub->d)
		walk_right(cub);
	mlx_clear_window(cub->mlx, cub->win);
	render_3d(cub);
	draw_map(cub);
	draw_player(cub, 0xFF0000);
	draw_fov_dda(cub, 1920, 60 * (PI / 180), 0x00FF00);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
	return (0);
}

int	rgb_to_hex(int r, int g, int b)
{
	if (r < 0) r = 0; if (r > 255) r = 255;
	if (g < 0) g = 0; if (g > 255) g = 255;
	if (b < 0) b = 0; if (b > 255) b = 255;
	return (r << 16) | (g << 8) | b;
}

void	ft_pixelput(t_game *data, int x, int y, int color)
{
	char	*tmp;

	if (x < 0 || x >= 1920 || y < 0 || y >= 1080)
		return ;
	if (!data || !data->addr)
		return ;
	tmp = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)tmp = color;
}

void	get_img_data(t_game *data)
{
	data->img = mlx_new_image(data->mlx, 1920, 1080);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
		&data->line_length, &data->endian);
}
