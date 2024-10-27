/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:47:13 by rgrochow          #+#    #+#             */
/*   Updated: 2024/10/27 11:53:03 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx_linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <string.h>
# include <ctype.h>

/*
typedef struct s_image
{
	void	*img_ptr;
	int		width;
	int		height;
}	t_image;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		collectibles;
	int		exit;
	int		player;
}	t_map;

typedef struct s_player
{
	int	x;
	int	y;
	int	moves;
	int	collected;
}	t_player;
*/
#define MAP_WIDTH 240
#define MAP_HEIGHT 240

typedef struct s_path
{
	int	ex;
	int	front;
	int	rear;
	int	x;
	int	y;
}	t_path;

typedef struct s_image
{
	void	*img;
	char *north_texture;
    char *south_texture;
    char *west_texture;
    char *east_texture;
	int floor_color;
    int ceiling_color;
}	t_image;

typedef struct s_player
{
	char	player_dir;
	double	player_x;
	double	player_y;
	int		x;
	int		y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		collectibles;
	int		exit;
	int		player;
}	t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	map;
	t_image	image;
	t_path	path;
    char *addr;
    int bpp;
    int line_length;
    int endian;
    t_player player;
    int key_states[256];
} t_game;

/* ************************************************************************** */
/*                                    MAP_FILE                                */
/* ************************************************************************** */
/* init.c */
void	init_map_file(t_game *game, char *map_file);
/* check.c */
void	check_map_file(t_game *game, char *map_file);
/* utils.c */
int		count_lines(const char *map_file);
char	*read_line(int fd);
int file_exists(const char *path);

/* ************************************************************************** */
/*                                      MAP                                   */
/* ************************************************************************** */
/* clear.c */
void	clear_map(t_game *game);
void	close_game(t_game *game);
/* check.c */
void	check_map(t_game *game);
/* utils.c */
int		bfs(t_game *game, int **directions, int **visited);

/* ************************************************************************** */
/*                                     IMAGES                                 */
/* ************************************************************************** */
void	clear_images(t_game *game);

/* ************************************************************************** */
/*                                      GAME                                  */
/* ************************************************************************** */

void	check_game(t_game *game);
int		close_window(t_game *game);

/* ************************************************************************** */
/*                                     PLAYER                                 */
/* ************************************************************************** */
/* check.c */
int		check_player(t_game *game, char *line, int height);
/* init.c */
void	init_player(t_game *game);

/* ************************************************************************** */
/*                                     UTILS                                  */
/* ************************************************************************** */
int		ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif