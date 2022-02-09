/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 21:10:32 by lbaela            #+#    #+#             */
/*   Updated: 2022/02/09 19:00:43 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "../../includes/minirt.h"
#include "../../includes/error_msgs.h"
#include "../../includes/objects.h"

typedef struct s_plane
{
	float	w;
	float	h;
	float	x_pix;
	float	y_pix;
}			t_plane;

t_plane	*get_projection_plane(float scene_w, float scene_h, float angle)
{
	t_plane	*proj;
	float	ratio;

	proj = malloc(sizeof(t_plane));
	if (proj == NULL)
		exit_on_error(-1, ERR_MALLOC);
	ratio = scene_w / scene_h;
	proj->w = tan(angle / 2 * (M_PI / 180));
	proj->w *= 2;
	proj->h = proj->w / ratio;
	proj->x_pix = proj->w / scene_w;
	proj->y_pix = proj->h / scene_h;
	return (proj);
}

void	ray_tracing(t_minirt *minirt)
{
	int			mlx_x;
	int			mlx_y;
	float		x_angle;
	float		y_angle;
	float		y_ray;
	float		x_ray;
	t_vector	*ray;
	t_plane		*proj;
	t_point		point;

	mlx_y = 0;
	proj = get_projection_plane(WIN_WIDTH, WIN_HEIGHT,
			minirt->camera->angle);
	y_angle = (WIN_HEIGHT / 2.0);
	while (y_angle >= (WIN_HEIGHT / 2.0) * -1.0)
	{
		mlx_x = 0;
		y_ray = y_angle * proj->y_pix;
		x_angle = (WIN_WIDTH / 2) * -1.0;
		while (x_angle <= (WIN_WIDTH / 2.0))
		{
			x_ray = x_angle * proj->x_pix;
			ray = new_vect(x_ray, y_ray, -1.0);
			normalise_vect(ray);
			object_intersects(minirt, minirt->objs, *ray, &point);
			my_mlx_pixel_put(minirt, mlx_x, mlx_y, point.colour);
			free(ray);
			mlx_x++;
			x_angle++;
		}
		mlx_y++;
		y_angle--;
	}
}
