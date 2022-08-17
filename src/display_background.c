#include "cub3D.h"

//dessine le top et bot en couleur
void	render_background(t_img *frame, t_assets assets)
{
	int	y;
	int	x;

	y = 0;
	while (y < frame->height)
	{
		x = 0;
		while (x < frame->width)
		{
			if (y < frame->height / 2)
				ft_put_pixel_frame(frame, y, x, encode_rgb(assets.f[0], assets.f[1], assets.f[2]));
			else
				ft_put_pixel_frame(frame, y, x, encode_rgb(assets.c[0], assets.c[1], assets.c[2]));
			x++;
		}
		y++;
	}
}
