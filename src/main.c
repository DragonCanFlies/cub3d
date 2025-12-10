/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latabagl <latabagl@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 09:43:29 by latabagl          #+#    #+#             */
/*   Updated: 2025/12/09 23:13:25 by latabagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_keypress(int key, t_game *game)
{
	int	speed = 4;

	if (key == XK_Escape)
		mlx_loop_end(game->mlx);
	else if (key == XK_w || key == XK_z || key == XK_Up)
		game->player.py -= speed;
	else if (key == XK_s || key == XK_Down)
		game->player.py += speed;
	else if (key == XK_a || key == XK_q || key == XK_Left)
		game->player.px -= speed;
	else if (key == XK_d || key == XK_Right)
		game->player.px += speed;
	return (0);
}

int	handle_close(t_game *game)
{
	mlx_loop_end(game->mlx);
	return (0);
}

int	handle_loop(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win, game->player.sprite,
			game->player.px, game->player.py);
	return (0);
}

int	play_game()
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
	game.player.sprite = mlx_xpm_file_to_image(game.mlx, "textures/player3.xpm", &s, &s);
	game.player.px = 100;
	game.player.py = 100;
	if (!game.player.sprite)
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
	mlx_destroy_window(game.mlx, game.win);
	mlx_destroy_display(game.mlx);
	free(game.mlx);
	return (1);
}

int	main(void)
{
	//char *map[] = {"111111", "100001", "100001", "1000N1", "111111", NULL};
	play_game();
}
