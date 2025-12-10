/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 09:42:07 by latabagl          #+#    #+#             */
/*   Updated: 2025/12/09 22:52:24 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>

#include <stdio.h> // printf
#include <stdlib.h> // free, exit

typedef struct s_player
{
	void		*sprite;
	int			px;
	int			py;
}				t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_player	player;
}				t_game;

#endif