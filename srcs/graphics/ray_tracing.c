/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 21:10:32 by lbaela            #+#    #+#             */
/*   Updated: 2022/02/28 21:44:31 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "../../includes/minirt.h"

t_plane	get_projection_plane(float scene_w, float scene_h, float angle)
{
	t_plane	proj;
	float	ratio;

	ratio = scene_w / scene_h;
	proj.w = tan(angle / 2 * (M_PI / 180));
	proj.w *= 2;
	proj.h = proj.w / ratio;
	proj.x_pix = proj.w / scene_w;
	proj.y_pix = proj.h / scene_h;
	proj.mlx_y = 0;
	return (proj);
}

void	ray_tracing(t_minirt *minirt)
{
	float		y_ray;
	float		x_ray;
	t_vector	ray;
	t_plane		proj;
	t_point		point;

	proj = get_projection_plane(WIN_WIDTH, WIN_HEIGHT,
			minirt->scene.camera.fov);
	proj.y_angle = (WIN_HEIGHT / 2.0);
	while (proj.y_angle >= (WIN_HEIGHT / 2.0) * -1.0)
	{
		proj.mlx_x = 0;
		y_ray = proj.y_pix * proj.y_angle--;
		proj.x_angle = (WIN_WIDTH / 2) * -1.0;
		while (proj.x_angle <= (WIN_WIDTH / 2.0))
		{
			x_ray = proj.x_pix * proj.x_angle++;
			ray = new_vect(x_ray, y_ray, -1.0);
			normalise_vect(&ray);
			object_intersects(minirt, minirt->scene.objs, ray, &point);
			my_mlx_pixel_put(minirt, proj.mlx_x++, proj.mlx_y, point.color);
		}
		proj.mlx_y++;
	}
}
