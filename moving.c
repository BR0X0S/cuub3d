/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 07:47:39 by oumondad          #+#    #+#             */
/*   Updated: 2024/12/11 17:11:04 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_game *cub, double direction)
{
	double	next_x;
	double	next_y;

	next_x = cub->player.pixel_x + cos(cub->player_angle + direction) * SPEED;
	next_y = cub->player.pixel_y + sin(cub->player_angle + direction) * SPEED;
	if (cub->map[(int)(next_y / SQ_SIZE)][(int)(next_x / SQ_SIZE)] != '1' &&
		cub->map[(int)((next_y + P_SIZE - 1) / SQ_SIZE)]
		[(int)(next_x / SQ_SIZE)] != '1' &&
		cub->map[(int)(next_y / SQ_SIZE)]
		[(int)((next_x + P_SIZE - 1) / SQ_SIZE)] != '1' &&
		cub->map[(int)((next_y + P_SIZE - 1) / SQ_SIZE)]
		[(int)((next_x + P_SIZE - 1) / SQ_SIZE)] != '1')
	{
		cub->player.pixel_x = next_x;
		cub->player.pixel_y = next_y;
	}
}

void	walk_left(t_game *cub)
{
	double	next_x;
	double	next_y;

	next_x = cub->player.pixel_x + cos(cub->player_angle - PI / 2) * SPEED;
	next_y = cub->player.pixel_y + sin(cub->player_angle - PI / 2) * SPEED;
	if (cub->map[(int)(next_y / SQ_SIZE)][(int)(next_x / SQ_SIZE)] != '1' &&
		cub->map[(int)((next_y + P_SIZE - 1) / SQ_SIZE)]
		[(int)(next_x / SQ_SIZE)] != '1' &&
		cub->map[(int)(next_y / SQ_SIZE)]
		[(int)((next_x + P_SIZE - 1) / SQ_SIZE)] != '1' &&
		cub->map[(int)((next_y + P_SIZE - 1) / SQ_SIZE)]
		[(int)((next_x + P_SIZE - 1) / SQ_SIZE)] != '1')
	{
		cub->player.pixel_x = next_x;
		cub->player.pixel_y = next_y;
	}
}

void	walk_right(t_game *cub)
{
	double	next_x;
	double	next_y;

	next_x = cub->player.pixel_x + cos(cub->player_angle + PI / 2) * SPEED;
	next_y = cub->player.pixel_y + sin(cub->player_angle + PI / 2) * SPEED;
	if (cub->map[(int)(next_y / SQ_SIZE)][(int)(next_x / SQ_SIZE)] != '1' &&
		cub->map[(int)((next_y + P_SIZE - 1) / SQ_SIZE)]
		[(int)(next_x / SQ_SIZE)] != '1' &&
		cub->map[(int)(next_y / SQ_SIZE)]
		[(int)((next_x + P_SIZE - 1) / SQ_SIZE)] != '1' &&
		cub->map[(int)((next_y + P_SIZE - 1) / SQ_SIZE)]
		[(int)((next_x + P_SIZE - 1) / SQ_SIZE)] != '1')
	{
		cub->player.pixel_x = next_x;
		cub->player.pixel_y = next_y;
	}
}

int	key_press(int key, t_game *cub)
{
	if (key == 65307)
		escape(cub);
	else if (key == W_KEY)
		cub->w = 1;
	else if (key == S_KEY)
		cub->s = 1;
	else if (key == A_KEY)
		cub->a = 1;
	else if (key == D_KEY)
		cub->d = 1;
	else if (key == LEFT_KEY)
		cub->left = 1;
	else if (key == RIGHT_KEY)
		cub->right = 1;
	return (0);
}

int	key_release(int key, t_game *cub)
{
	if (key == W_KEY)
		cub->w = 0;
	if (key == S_KEY)
		cub->s = 0;
	if (key == A_KEY)
		cub->a = 0;
	if (key == D_KEY)
		cub->d = 0;
	if (key == LEFT_KEY)
		cub->left = 0;
	if (key == RIGHT_KEY)
		cub->right = 0;
	return (0);
}
