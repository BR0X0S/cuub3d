/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:49:01 by oumondad          #+#    #+#             */
/*   Updated: 2024/12/26 15:50:58 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line_dda(t_game *cub, double angle, double length, int color)
{
	double	x, y;
	double	x_end, y_end;
	double	delta_x, delta_y;
	double	steps;
	double	x_inc, y_inc;

	x = (int)cub->player.pixel_x + P_SIZE / 2;
	y = (int)cub->player.pixel_y + P_SIZE / 2;
	x_end = x + cos(angle) * length;
	y_end = y + sin(angle) * length;
	delta_x = x_end - x;
	delta_y = y_end - y;
	steps = fmax(fabs(delta_x), fabs(delta_y));
	x_inc = delta_x / steps;
	y_inc = delta_y / steps;
	for (int i = 0; i <= steps; i++)
	{
		// Plot the current point
		if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
			ft_pixelput(cub, (int)round(x), (int)round(y), color);
		x += x_inc;
		y += y_inc;
	}
}

//victors

double	raycast_dda(t_game *cub, double angle, int *hit_x, int *hit_y)
{
	double	x, y;
	double	x_inc, y_inc;
	double	length = 0;
	double	step_size = 1.0; // Step size for ray movement

	// Set starting point (player's position)
	x = (int)cub->player.pixel_x + P_SIZE / 2;
	y = (int)cub->player.pixel_y + P_SIZE / 2;

	// Calculate increments for each step
	x_inc = cos(angle) * step_size;
	y_inc = sin(angle) * step_size;

	// Perform DDA until a wall is hit
	while (1)
	{
		// Calculate current map cell
		int map_x = (int)(x / SQ_SIZE);
		int map_y = (int)(y / SQ_SIZE);

		// Check boundaries to prevent out-of-bounds access
		if (map_x < 0 || map_y < 0 || map_x >= cub->cols - 1 || map_y >= cub->rows - 1)
			break;

		// Check if the current cell is a wall
		if (cub->map[map_y][map_x] == '1')
		{
			// Set the hit coordinates if requested
			if (hit_x)
				*hit_x = x; 
			if (hit_y)
				*hit_y = y;
			break;
		}
		else if (cub->map[map_y][map_x] == ' ') // Empty space
		{
			if (hit_x) *hit_x = x;
			if (hit_y) *hit_y = y;
			break;
		}
		x += x_inc;
		y += y_inc;
		length += step_size;
	}
	return length; // Return the distance to the wall
}

void	render_3d(t_game *cub)
{
	double	fov_angle = PI / 3; // 60-degree field of view
	int		num_rays = SCREEN_WIDTH; // One ray per screen column
	double	angle_step = fov_angle / num_rays;
	double	start_angle = cub->player_angle - (fov_angle / 2);
	double	ray_angle;

	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		// Calculate the current ray angle
		ray_angle = start_angle + x * angle_step;

		// Cast the ray to find the distance to the wall
		double	distance_to_wall = raycast_dda(cub, ray_angle, NULL, NULL);

		// Correct for fish-eye distortion
		distance_to_wall *= cos(ray_angle - cub->player_angle);

		// Calculate the height of the wall slice
		double	projection_plane_dist = (SCREEN_WIDTH / 2) / tan(fov_angle / 2);
		int		wall_height = (int)((SQ_SIZE / distance_to_wall) * projection_plane_dist);

		// Determine the starting and ending points for the wall slice
		int		wall_top = (SCREEN_HEIGHT / 2) - (wall_height / 2);
		int		wall_bottom = (SCREEN_HEIGHT / 2) + (wall_height / 2);

		// Clamp values to screen dimensions
		if (wall_top < 0)
			wall_top = 0;
		if (wall_bottom >= SCREEN_HEIGHT)
			wall_bottom = SCREEN_HEIGHT - 1;

		// Draw the wall slice
		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			if (y < wall_top)
				ft_pixelput(cub, x, y, rgb_to_hex(cub->cl[0],cub->cl[1],cub->cl[2])); // Sky color
			else if (y > wall_bottom)
				ft_pixelput(cub, x, y, rgb_to_hex(cub->fl[0],cub->fl[1],cub->fl[2])); // Floor color
			else
			{
				ft_pixelput(cub, x, y, 0xFF0000); // Wall color
				// if (y % 2 == 0)
				// 	ft_pixelput(cub, x, y, 0x00FF00); // Wall color
			}
		}
	}
}

void	draw_fov_dda(t_game *cub, int num_rays, double fov_angle, int color)
{
	double	start_angle = cub->player_angle - (fov_angle / 2);
	double	angle_step = fov_angle / (num_rays - 1);
	double	ray_angle;

	for (int i = 0; i < num_rays; i++)
	{
		// Calculate the current ray angle
		ray_angle = start_angle + i * angle_step;

		// Find the length of the ray (distance to the wall)
		double length = raycast_dda(cub, ray_angle, NULL, NULL);
		if (length > 50)
			length = 50;
		// Draw the ray using DDA
		draw_line_dda(cub, ray_angle, length, color);
	}
}
