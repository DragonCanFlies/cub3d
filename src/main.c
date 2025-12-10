/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 09:43:29 by latabagl          #+#    #+#             */
/*   Updated: 2025/12/10 17:39:20 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_wall(t_game *game, double x, double y)
{
	int col = floor(x / TILESIZE);
	int row = floor(y / TILESIZE);
	if (game->map[row][col] == '1')
		return (1);
	return (0);
}

// void	draw_line(t_game *game)
// {
// 	int	i = 0;

// 	while (!is_wall(game, game->player.px, game->player.py - i))
// 	{
// 		mlx_put_image_to_window(game->mlx, game->win, game->red_px,
// 		game->player.px + 3, game->player.py - i);
// 		i++;
// 	}
// }

void	draw_line(t_game *game)
{
	int checks = game->player.py / 64;
	while (checks--)
	{
		if (is_wall(game, game->player.px, checks * 64))
			break ;
	}
	int i = 0;
	while (i < (((int)game->player.py / 64 - checks - 1)) * 64 + (int)game->player.py % 64)
	{
		mlx_put_image_to_window(game->mlx, game->win, game->red_px,
		game->player.px + 3, game->player.py - i);
		i++;
	}
}

void	draw_map(t_game *game)
{
	int	size = 64;

	for (int row = 0; game->map[row]; row++)
		for (int col = 0; game->map[row][col]; col++)
	{
		if (game->map[row][col] == '1')
		{
			mlx_put_image_to_window(game->mlx, game->win, game->wall,
			col * size, row * size);
		}
		else
		{
			mlx_put_image_to_window(game->mlx, game->win, game->floor,
			col * size, row * size);
		}
	}
}
// int	handle_keypress(int key, t_game *game)
// {
// 	float	speed = 8.0;

// 	if (key == XK_Escape)
// 		mlx_loop_end(game->mlx);
// 	if (key == XK_w || key == XK_z || key == XK_Up)
// 		if (!is_wall(game, game->player.px, game->player.py - speed))
// 			game->player.py -= speed;
// 	if (key == XK_s || key == XK_Down)
// 		if (!is_wall(game, game->player.px, game->player.py + 4 + speed))
// 			game->player.py += speed;
// 	if (key == XK_a || key == XK_q || key == XK_Left)
// 		if (!is_wall(game, game->player.px - speed, game->player.py))
// 			game->player.px -= speed;
// 	if (key == XK_d || key == XK_Right)
// 		if (!is_wall(game, game->player.px + 4 + speed, game->player.py))
// 			game->player.px += speed;
// 	return (0);
// }

int	handle_keypress(int key, t_game *game)
{
	if (key == XK_Escape)
		mlx_loop_end(game->mlx);
	if (key == XK_w || key == XK_z || key == XK_Up)
	{
		game->player.px += game->player.pdx;
		game->player.py += game->player.pdy;
	}
	if (key == XK_s || key == XK_Down)
	{
		game->player.px -= game->player.pdx;
		game->player.py -= game->player.pdy;
	}
	if (key == XK_a || key == XK_q || key == XK_Left)
	{
		game->player.pa += 0.1;
		if (game->player.pa > 2 * PI)
			game->player.pa -= 2 * PI;
		game->player.pdx = cos(game->player.pa);
		game->player.pdy = sin(game->player.pa);
	}
	if (key == XK_d || key == XK_Right)
	{
		game->player.pa -= 0.1;
		if (game->player.pa < 0)
			game->player.pa += 2 * PI;
		game->player.pdx = cos(game->player.pa);
		game->player.pdy = sin(game->player.pa);
	}
	return (0);
}

int	handle_close(t_game *game)
{
	mlx_loop_end(game->mlx);
	return (0);
}

int	handle_loop(t_game *game)
{
	draw_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->player.sprite,
			game->player.px, game->player.py);
	//draw_line(game);
	return (0);
}

int	play_game(char **map)
{
	t_game	game;

	game.mlx = mlx_init();
	if (!game.mlx)
		exit(0);

	game.win = mlx_new_window(game.mlx, 
			WIN_WIDTH, 
			WIN_HEIGHT, 
			"Cub3D");
	if (!game.win)
	{
		mlx_destroy_display(game.mlx);
		free(game.mlx);
		exit(0);
	}
	
	int		s;
	game.player.sprite = mlx_xpm_file_to_image(game.mlx, "sprites/player_box.xpm", &s, &s);
	game.wall = mlx_xpm_file_to_image(game.mlx, "textures/nwall64.xpm", &s, &s);
	game.floor = mlx_xpm_file_to_image(game.mlx, "textures/nfloor64.xpm", &s, &s);
	game.red_px = mlx_xpm_file_to_image(game.mlx, "sprites/cyan_px.xpm", &s, &s);
	
	game.player.px = 100.0;
	game.player.py = 100.0;
	game.player.pdx = 0;
	game.player.pdy = 1;
	game.player.pa = PI / 2;
	game.map = map;
	if (!game.player.sprite) // !floor !wall
	{
		mlx_destroy_window(game.mlx, game.win);
		mlx_destroy_display(game.mlx);
		free(game.mlx);
		exit(0);
	}

	mlx_hook(game.win, KeyPress, KeyPressMask, handle_keypress, &game);
	mlx_hook(game.win, DestroyNotify, StructureNotifyMask, handle_close, &game);

	mlx_string_put(game.mlx, game.win, 0, 0, 0xFFFFFF, "Cub3D");
	mlx_loop_hook(game.mlx, handle_loop, &game);
	mlx_loop(game.mlx);

	if (game.player.sprite)
		mlx_destroy_image(game.mlx, game.player.sprite);
	if (game.wall)
		mlx_destroy_image(game.mlx, game.wall);
	if (game.floor)
		mlx_destroy_image(game.mlx, game.floor);
	if (game.red_px)
		mlx_destroy_image(game.mlx, game.red_px);
	mlx_destroy_window(game.mlx, game.win);
	mlx_destroy_display(game.mlx);
	free(game.mlx);
	return (1);
}

int	main(void)
{
	char *map[] = {"11111111",
				   "10100001", 
				   "10100001", 
				   "10100001", 
				   "10000001", 
				   "10000101", 
				   "10000001", 
				   "11111111", 
				   NULL};
	play_game(map);
}
