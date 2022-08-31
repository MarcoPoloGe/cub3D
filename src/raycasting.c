/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktrosset <ktrosset@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:16:04 by ktrosset          #+#    #+#             */
/*   Updated: 2022/08/31 16:52:18 by ktrosset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/cub3D.h"

double	ft_get_sideDist(double nb)
{
	double	diff;
	double	sidedist;

	diff = 1 - (nb - (int) nb);
	sidedist = nb + diff;
	return (sidedist);
}

void	ft_calculate_impact_point(t_coord coord, t_ray *ray, t_data *data)
{
	t_coord		sidex;
	t_coord		sidey;
	int			i;
	t_impact	*resy;
	double		thisangle;

	if (ray->angle + data->camera.dir_angle > 180)
		thisangle = data->camera.dir_angle + ray->angle;
	else
		thisangle = data->camera.dir_angle + ray->angle;
	if (thisangle >= 360)
		thisangle -= 360;
	if (thisangle < 0)
		thisangle += 360;
	sidex.y = coord.y;
	if (thisangle < 180)
		sidex.x = ceil(coord.x);
	else
		sidex.x = floor(coord.x);
	if (thisangle < 90 || thisangle > 270)
		sidey.y = floor(coord.y);
	else
		sidey.y = ceil(coord.y);
	sidey.x = coord.x;
	if (thisangle > 180)
		sidey = ft_find_next_coord_y(coord, thisangle, sidey);
	else if (thisangle <= 180)
		sidey = ft_find_next_coord_y(coord, thisangle - 180, sidey);
	sidex = ft_find_next_coord_x(coord, thisangle + 90, sidex);
	i = -1;
	ray->impact = 0;
	resy = 0;
	while (resy == 0 && i < data->map_width)
	{
		if (++i != 0)
		{
			if (thisangle <= 90)
				sidey = ft_find_next_coord_y(sidey, thisangle - 180,
						ft_coord(sidey.y - 1, sidey.x));
			else if (thisangle <= 180)
				sidey = ft_find_next_coord_y(sidey, thisangle - 180,
						ft_coord(sidey.y + 1, sidey.x));
			else if (thisangle <= 270)
				sidey = ft_find_next_coord_y(sidey, thisangle,
						ft_coord(sidey.y + 1, sidey.x));
			else if (thisangle <= 360)
				sidey = ft_find_next_coord_y(sidey, thisangle,
						ft_coord(sidey.y - 1, sidey.x));
		}
		resy = ft_check_if_wall_hit_y(data, data->map, sidey, thisangle);
	}
	printf("angle: %f\n", thisangle);
	i = -1;
	while (ray->impact == 0 && i < data->map_height)
	{
		if (++i != 0)
		{
			if (thisangle <= 90)
				sidex = ft_find_next_coord_x(sidex, thisangle + 90,
						ft_coord(sidex.y, sidex.x + 1));
			else if (thisangle <= 180)
				sidex = ft_find_next_coord_x(sidex, thisangle + 90,
						ft_coord(sidex.y, sidex.x + 1));
			else if (thisangle <= 270)
				sidex = ft_find_next_coord_x(sidex, thisangle + 90,
						ft_coord(sidex.y, sidex.x - 1));
			else if (thisangle <= 360)
				sidex = ft_find_next_coord_x(sidex, thisangle + 90,
						ft_coord(sidex.y, sidex.x - 1));
		}
		ray->impact = ft_check_if_wall_hit_x(data, data->map, sidex, thisangle);
		if (ray->impact != 0)
		{
			if (resy && resy->distance < ray->impact->distance)
			{
				free(ray->impact);
				ray->impact = resy;
			}
		}
	}
	free(resy);
}
