/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dredfort <dredfort@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:04:01 by dredfort          #+#    #+#             */
/*   Updated: 2022/02/21 18:12:15 by dredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "../../includes/structure_prototypes.h"
#include "../../includes/minirt.h"

static void	*ft_get_pattern_addr(t_pattern pattern, double u, double v)
{
	int	x;
	int	y;

	x = (int)fmod(fmod(u, pattern.width) + pattern.width, pattern.width);
	y = (int)fmod(fmod(v, pattern.height) + pattern.height, pattern.height);
	x *= pattern.bits_per_pixel / 8;
	y *= pattern.size_line;
	return (pattern.addr + y + x);
}

static t_rgb	ft_rgb_pattern(t_pattern pattern, double u, double v,
							float brightness)
{
	t_rgb	tmp;
	void	*color;

	brightness += 1;
	if (brightness > 1)
		brightness = 1;
	if (brightness < 0)
		brightness = 0;
	color = ft_get_pattern_addr(pattern, u, v);
	tmp = ft_get_rgb((*(unsigned int *) color & 0x00ff0000) >> 16,
			(*(unsigned int *) color & 0x0000ff00) >> 8,
			(*(unsigned int *) color & 0x000000ff));
	tmp = ft_rgb_brightness_adjustment(tmp, brightness);
	return (tmp);
}

static void	ft_get_uv(t_object *obj, t_vector ray, double *u, double *v)
{
	t_vector	local;
	t_vector	ulocal;
	double		costheta;

	local = vect_substract(obj->hit.norm_v, ray);
	ulocal = local;
	normalise_vect(&ulocal);
	costheta = vect_dot_product(ulocal, ft_vector_rotate_cw(obj->hit.norm_v));
	*u = sqrt(vect_dot_product(local, ulocal)) * costheta * 700;
	costheta = vect_dot_product(ulocal, ft_vector_rotate_ccw(obj->hit.norm_v));
	*v = sqrt(vect_dot_product(local, ulocal)) * costheta * 700;
}

t_rgb	ft_pattern(t_object *obj, t_vector ray, t_minirt *minirt)
{
	double	u;
	double	v;
	t_rgb	rgb_texture;
	t_rgb	rgb_bump;

	ft_get_uv(obj, ray, &u, &v);
	if (minirt->texture.img && minirt->apply_texture)
		rgb_texture = ft_rgb_pattern(minirt->texture, u, v, 0.75);
	if (minirt->bump.img && minirt->apply_bump)
		rgb_bump = ft_rgb_pattern(minirt->bump, u, v, 0.8);
	if (minirt->apply_texture == 1 && !minirt->apply_bump)
		return (ft_rgb_brightness_adjustment(rgb_texture, 0.6));
	else if (!minirt->apply_texture && minirt->apply_bump)
		return (multiply_rgbs(obj->rgb, ft_rgb2gray(rgb_bump)));
	else if (minirt->apply_texture == 1 && minirt->apply_bump)
		return (multiply_rgbs(rgb_texture, ft_rgb2gray(rgb_bump)));
	else
		return (obj->rgb);
}
