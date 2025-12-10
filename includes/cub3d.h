/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 09:42:07 by latabagl          #+#    #+#             */
/*   Updated: 2025/12/10 17:06:51 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIN_WIDTH 1024
# define WIN_HEIGHT 512
# define TILESIZE 64

# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>

#include <stdio.h> // printf
#include <stdlib.h> // free, exit
#include <math.h> // sin(double angle); angle is in radian  floor()

# define PI 3.1415926535

typedef struct s_player
{
	void		*sprite;
	double			px;
	double			py;
	double			pdx; // delta x
	double			pdy;
	double			pa; // angle
}				t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_player	player;
	char		**map;
	void		*wall;
	void		*floor;
	void		*red_px;
}				t_game;

#endif