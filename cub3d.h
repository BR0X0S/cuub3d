/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:44:38 by hes-safi          #+#    #+#             */
/*   Updated: 2024/12/24 21:08:07 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*-- LIBRARIES --*/

// # include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>
# include "mlx/mlx.h" //his is the path to the minilibx library.

/*--- DEFINES ---*/

# define OFF "\033[0m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"

# define PI 3.14159265358979323846
# define FOV 60 // * (PI / 180)
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

# define UP_KEY 65362
# define DOWN_KEY 65364
# define LEFT_KEY 65361
# define RIGHT_KEY 65363

# define W_KEY 119//65362
# define S_KEY 115//65364
# define A_KEY 97//65361
# define D_KEY 100//65363

# define SQ_SIZE 16 // Size of each grid square
# define SPEED 4 // Speed of player movement 
# define P_SIZE 10 // Size of player square

/*--- STRUCTS ---*/

typedef struct s_player
{
	// pixel_x and pixel_y are the player's position in pixels.
	int		x;
	int		y;
	double		pixel_x; // == x * SQ_SIZE
	double		pixel_y; // == y * SQ_SIZE
	char	dir;
	// check fonction "get_player_pos"
}				t_player;

typedef struct s_line
{
	double	x1;
	double	y1;
	double	delta_x;
	double	delta_y;
	int		steps;
	double	x_inc;
	double	y_inc;
	double	x;
	double	y;
	int		i;
}				t_line;

typedef struct s_game
{
	int			left;
	int			right;
	int			w;
	int			s;
	int			a;
	int			d;
	void		*win;
	char		*file;
	char		**map;
	char		**map_tmp;
	char		**split;
	char		*no;
	char		*so;
	char		*ea;
	char		*we;
	int			fl[3];
	int			cl[3];
	int			rows;
	int			cols;
	void		*mlx;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	void		*img;
	double		line_x;
	double		line_y;
	double		player_x;
	double		player_y;
	double		player_angle; // In radians
	t_player	player; // Position Player struct
	t_line		line;
}				t_game;

/*-- UTILITIES --*/

void	ft_error(t_game *cub, char *str);
void	ft_free(void *ptr);
void	free_array(char **arr);
void	print_array(char **arr);		// Debugging
void	print_elements(t_game *cub);	// Debugging
int		ft_strlen(char *str);
int		ft_atoi(char *str);
int		counter(char *s, char c);
char	*ft_strdup(char *str);
char	*ft_strjoin(char *s1, char *s2, int flag);
char	*read_file(int fd);
char	**ft_split(char const *s, char c);

/*-- FUNCTIONS --*/

void	initialization(t_game *cub);
void	parsing(t_game *cub, char *str);
void	read_map(t_game *cub, char *str);
void	check_map(t_game *cub);
void	get_elements(t_game *cub);
int		path_setter(t_game *cub, char *str);
int		color_setter(t_game *c, char *s);
void	converter(t_game *cub, char **arr, char c);
void	map_elements(t_game *cub, char **map);
void	create_map(t_game *cub);
int		is_map(char *str);
int		is_walkable(char c);
void	check_dupes(t_game *cub);
int		check_bounds(t_game *cub, char **arr, int i, int j);
void	check_pathing(t_game *cub);
void	get_player_pos(char **map, t_player *player);

/*-- DRAWING --*/

void	draw_player(t_game *cub, int color);
void	draw_map(t_game *cub);
void	ft_pixelput(t_game *data, int x, int y, int color);
void	get_img_data(t_game *data);
int		render_scene(t_game *cub);
int		rgb_to_hex(int r, int g, int b);
void	draw_line_dda(t_game *cub, double angle, double length, int color);

/*-- MOVEMENT --*/

int		escape(t_game *cub);
int		key_press(int keycode, t_game *cub);
void	walk_right(t_game *cub);
void	walk_left(t_game *cub);
void	move_player(t_game *cub, double direction);
int		key_release(int key, t_game *cub);

/*NEED TO DELETE AFER BROXOS END HIS PART*/

// void	draw_line_dda(t_game *cub, t_line *line, double angle, double length, int color);
void	draw_fov_dda(t_game *cub, int num_rays, double fov_angle, int color);
double	raycast_dda(t_game *cub, double angle, int *hit_x, int *hit_y);
void	render_3d(t_game *cub);

#endif