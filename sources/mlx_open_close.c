#include "mlx.h"
#include "world.h"
#include <stdlib.h>

int	handle_keypress(int keycode, t_display *disp)
{
	if (keycode == ESC
		|| (disp && !disp->mlx_ptr))
		disp->final = 1;
	return (0);
}

int	close_win(t_display *disp)
{
	if (disp)
		disp->final = 1;
	return (0);
}

int	render(t_display *display)
{
	if (display
		&& display->final == 0
		&& display->mlx_ptr)
	{
		mlx_put_image_to_window(display->mlx_ptr, display->mlx_window,
			display->mlx_image, 0, 0);
	}
	if (display
		&& display->final == 1)
	{
		clean_mlx_context(display);
		free(display->world->objects);
		exit(EXIT_SUCCESS);
	}
	return (0);
}
