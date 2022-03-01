/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dredfort <dredfort@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:32:15 by dredfort          #+#    #+#             */
/*   Updated: 2022/02/24 16:35:09 by dredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../libs/minilibx_macos/mlx.h"

static void	ft_first_object_selection(t_minirt *minirt, t_object *tmp_obj)
{
	minirt->scene.object = tmp_obj;
	minirt->scene.origin_color = tmp_obj->rgb;
	if (minirt->scene.object->type == 'L')
	{
		minirt->scene.light = minirt->scene.object->light;
		minirt->scene.object->rgb = ft_get_rgb(65, 255, 125);
	}
	else
		minirt->scene.object->rgb = ft_get_rgb(255, 125, 0);
}

static void	ft_deselect_object(t_minirt *minirt)
{
	minirt->scene.object->rgb = minirt->scene.origin_color;
	minirt->scene.object = 0;
	minirt->scene.light = 0;
	minirt->scene.origin_color = ft_get_rgb(0, 0, 0);
}

static void	ft_change_selected_object(t_minirt *minirt, t_object *tmp_obj)
{
	minirt->scene.object->rgb = minirt->scene.origin_color;
	minirt->scene.object = tmp_obj;
	minirt->scene.origin_color = tmp_obj->rgb;
	if (minirt->scene.object->type == 'L')
	{
		minirt->scene.light = minirt->scene.object->light;
		minirt->scene.object->rgb = ft_get_rgb(65, 255, 125);
	}
	else
		minirt->scene.object->rgb = ft_get_rgb(255, 125, 0);
}

static void	ft_cancel_selection(t_minirt *minirt)
{
	minirt->scene.object = 0;
	minirt->scene.light = 0;
	minirt->scene.origin_color = ft_get_rgb(0, 0, 0);
}

void	ft_object_selection(int mx, int my, t_minirt *minirt)
{
	t_plane		proj;
	t_vector	ray;
	t_point		point;
	t_object	*tmp_obj;

	mx = mx - (WIN_WIDTH / 2);
	my = (WIN_HEIGHT / 2.0) - my;
	proj = get_projection_plane(WIN_WIDTH, WIN_HEIGHT,
			minirt->scene.camera.fov);
	ray = new_vect(mx * proj.x_pix, my * proj.y_pix, -1.0);
	normalise_vect(&ray);
	tmp_obj = object_intersects(minirt, minirt->scene.objs, ray, &point);
	if (!minirt->scene.object && tmp_obj)
		ft_first_object_selection(minirt, tmp_obj);
	else if ((minirt->scene.object && !tmp_obj)
		|| (tmp_obj && minirt->scene.object == tmp_obj))
		ft_deselect_object(minirt);
	else if (minirt->scene.object && tmp_obj && minirt->scene.object != tmp_obj)
		ft_change_selected_object(minirt, tmp_obj);
	else
		ft_cancel_selection(minirt);
	ray_tracing(minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->img, 0, 0);
}
