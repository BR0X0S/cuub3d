/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:44:32 by hes-safi          #+#    #+#             */
/*   Updated: 2024/12/23 21:53:08 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialization(t_game *cub)
{
	cub->file = NULL;
	cub->split = NULL;
	cub->map = NULL;
	cub->map_tmp = NULL;
	cub->no = NULL;
	cub->so = NULL;
	cub->ea = NULL;
	cub->we = NULL;
	cub->fl[0] = -1;
	cub->fl[1] = -1;
	cub->fl[2] = -1;
	cub->cl[0] = -1;
	cub->cl[1] = -1;
	cub->cl[2] = -1;
	cub->rows = 0;
	cub->cols = 0;
	cub->mlx = NULL;
}

void	get_player_pos(char **map, t_player *player)
{
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				player->x = j;
				player->y = i;
				player->pixel_x = player->x * SQ_SIZE;
				player->pixel_y = player->y * SQ_SIZE;
				player->dir = map[i][j];
				return ;
			}
			j++;
		}
		i++;
	}
	return ;
}

double	set_angle(char dir)
{
	double	angle;

	if (dir == 'N')
		angle = 3 * PI / 2;
	else if (dir == 'E')
		angle = 0;
	else if (dir == 'S')
		angle = PI / 2;
	else
		angle = PI;
	return (angle);
}

void	game_init(t_game *cub)
{
	cub->w = 0;
	cub->s = 0;
	cub->a = 0;
	cub->d = 0;
	get_img_data(cub);
	cub->player_angle = set_angle(cub->player.dir);
}

int	main(int ac, char **av)
{
	t_game	cub;

	initialization(&cub);
	if (ac != 2)
		ft_error(&cub, "Argument Must be a single .cub File!");
	parsing(&cub, av[1]);
	printf("%sMap is Valid!%s\n", GREEN, OFF);
	cub.mlx = mlx_init();
	if (!cub.mlx)
		ft_error(&cub, "Mlx failed to initialize!");
	cub.win = mlx_new_window(cub.mlx, 1920, 1080, "Cub3D");
	game_init(&cub);
	mlx_hook (cub.win, 2, 1L << 0, key_press, &cub);
	mlx_hook (cub.win, 3, 1L << 1, key_release, &cub);
	mlx_hook (cub.win, 17, 0, escape, &cub);
	mlx_put_image_to_window(cub.mlx, cub.win, cub.img, 0, 0);
	mlx_loop_hook(cub.mlx, render_scene, &cub);
	mlx_loop(cub.mlx);
}
