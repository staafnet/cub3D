/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:47:13 by rgrochow          #+#    #+#             */
/*   Updated: 2025/01/05 23:42:16 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
# include "../mlx_linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <string.h>
# include <ctype.h>

#define WIDTH 800
#define HEIGHT 600
#define MOVE_SPEED 0.05
#define ROTATE_SPEED 1.0

typedef struct s_data {
    
} t_data;

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
	int floor_color;
    int ceiling_color;
}	t_image;

typedef struct s_player
{
	char	player_dir;
	double	player_x;
	double	player_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;


/*
typedef struct s_game
{
	void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    double  posX, posY;
    double  dirX, dirY;
    double  planeX, planeY;
    int     move_forward;
    int     move_backward;
    int     move_left;
    int     move_right;
    double  pitch;


	t_map	map;
	t_image	image;
	t_path	path;
    t_player player;
} t_game;


*/
typedef struct s_texture
{
    void    *img;
    int     *data;
    int     width;
    int     height;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}   t_texture;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_game
{
	t_map	map;
    void        *mlx;
    void        *win;
    void        *img;
    int          screen_width;
    int          screen_height;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
    double      posX, posY;
    double      dirX, dirY;
    double      planeX, planeY;
    int paused;
    int         move_forward;
    int         move_backward;
    int         move_left;
    int         move_right;
    double      pitch;


    t_image     image;
    t_path      path;
    t_player    player;

    // Add texture variables
    t_texture   north_texture;
    t_texture   south_texture;
    t_texture   west_texture;
    t_texture   east_texture;

} t_game;

/* ************************************************************************** */
/*                                    FILE_MAP                                */
/* ************************************************************************** */


/* check.c */
void	check_map_file(char *map_file);
/* utils.c */
int		count_lines(const char *map_file);
char	*read_line(int fd);
int file_exists(const char *path);
void	init_map_file(t_game *game, char *map_file);

/* ************************************************************************** */
/*                                      GAME                                  */
/* ************************************************************************** */
/* init.c */
void	init_game(t_game *game, char *map_file);
/* utils.c */
int		count_lines(const char *map_file);

void	check_game(t_game *game);
int		close_window(t_game *game);



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
/*                                     PLAYER                                 */
/* ************************************************************************** */
/* check.c */
int		check_player(t_game *game, char *line, int height);
/* init.c */
void	init_player(t_game *game);

/* ************************************************************************** */
/*                                     UTILS                                  */
/* ************************************************************************** */
void	ft_error(char *status, void *data);
int		ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif