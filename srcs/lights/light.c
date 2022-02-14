/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:20:51 by lbaela            #+#    #+#             */
/*   Updated: 2022/02/14 17:24:18 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>

#include "../../includes/minirt.h"
#include "../../includes/parsing.h"
#include "../../includes/objects.h"

void	add_light(t_minirt *minirt, t_point *point)
{
	float		light;
	float		n_dot_l;
	t_rgb		ambient;
	t_rgb		diffuse;
	t_vector	l_len;

	/* add ambient lighting */
	light = minirt->ambient->lighting_ratio;
	ambient = calc_rgb_light(minirt->ambient->rgb, light);
	/* add diffuse lighting */
	l_len = vect_substract(*minirt->light->point, point->hit_coord);
	n_dot_l = vect_dot_product(point->norm_v, *minirt->light->point);
	if (n_dot_l <= 0.0 && point->type == 'P')
	{
		point->norm_v = vect_mult(point->norm_v, -1.0);
		n_dot_l *= -1.0;
	}
	if (n_dot_l > 0.0)
	{
		light = minirt->light->brightness_ratio * n_dot_l
			/ (vect_len(point->norm_v) * vect_len(l_len));
		diffuse = calc_rgb_light(minirt->light->rgb, light);
		ambient = add_rgb_light(ambient, diffuse);
	}
	point->rgb = multiply_rgbs(point->rgb, ambient);
	point->colour = ft_rgb_hex(0, point->rgb);
}

void	add_specular(t_vector ray, t_point *point, t_light *light)
{
	t_vector	reflect;
	t_rgb		spec;
	double		strength;
	float		r_dot_v;

	reflect = reflect_vector(vect_mult(*light->point, -1.0), point->norm_v);
	r_dot_v = vect_dot_product(reflect, ray);
	if (r_dot_v > 0.0)
	{
		strength = light->brightness_ratio
			* pow(r_dot_v / vect_len(reflect) * vect_len(ray), 32);
		spec = calc_rgb_light(light->rgb, 0.6 * strength);
		point->colour = ft_rgb_hex(0, add_rgb_light(point->rgb, spec));
	}
}

static int	intersection_exists(t_object **objs, t_point *point)
{
	t_vector	origin;
	t_vector	ray;
	float		res;
	int			i;

	i = 0;
	point->dist = MAX_DIST;
	ray = point->norm_v;
	origin = point->hit_coord;
	while (objs[i] != NULL)
	{
		if (objs[i]->type == 'S')
			res = sphere_intersects(origin, objs[i], ray);
		else if (objs[i]->type == 'C')
			res = cylinder_intersects(origin, objs[i], ray);
		else if (objs[i]->type == 'P')
			res = plane_intersects(origin, objs[i], ray);
		if (res != 0 && res < point->dist)
			point->dist = res;
		i++;
	}
	if (point->dist == MAX_DIST)
		return (0);
	return (1);
}

int	in_shadow(t_minirt *minirt, t_point *point, t_light *light)
{
	t_point		intersect;
	float		dist_to_light;
	float		dist_to_obj;

	intersect.hit_coord = vect_add(point->hit_coord, vect_mult(point->norm_v, 0.00001));
	intersect.norm_v = vect_substract(*light->point, intersect.hit_coord);
	normalise_vect(&intersect.norm_v);
	if (intersection_exists(minirt->objs, &intersect))
	{
		dist_to_light = vect_dist(point->hit_coord, *light->point);
		dist_to_obj = vect_dist(point->hit_coord, intersect.hit_coord);
		if (dist_to_obj < dist_to_light)
			return (1);
	}
	return (0);
}

void	ft_print_light(t_minirt *minirt)
{
	printf("\033[36m\n########## LIGHT ##########\n");
	printf("[POINT] x: %f, y: %f, z: %f\n",
		   minirt->light->point->x,
		   minirt->light->point->y,
		   minirt->light->point->z);
	printf("[BRIGHTNESS] %f\n", minirt->light->brightness_ratio);
	printf("[RGB] r: %d, g: %d, b: %d\n",
		   minirt->light->rgb.r,
		   minirt->light->rgb.g,
		   minirt->light->rgb.b);
	printf("[COLOR] %X\n", minirt->light->colour);
	printf("---------- ----- ----------\n"COLOR_END);
}

void	ft_init_light(t_minirt *minirt)
{
	minirt->light = malloc(sizeof(t_light));
	if (!minirt->light)
	{
		write(2, ERROR_MALLOC, ft_strlen(ERROR_MALLOC));
		ft_free_camera(minirt);
		exit(ERROR_MALLOC_LIGHT);
	}
	minirt->light->point = malloc(sizeof(t_vector));
	if (!minirt->light->point)
	{
		write(2, ERROR_MALLOC, ft_strlen(ERROR_MALLOC));
		ft_free_camera(minirt);
		free(minirt->light);
		exit(ERROR_MALLOC_LIGHT_ORIGIN);
	}
}

void	ft_read_light(t_minirt *minirt, char *line)
{
	int	i;

	i = 1;
	while (line[i] == ' ')
		i++;
	i = 1;
	while (line[i] == ' ')
		i++;
	minirt->light->point->x = ft_atof(line, &i);
	minirt->light->point->y = ft_atof(line, &i);
	minirt->light->point->z = ft_atof(line, &i);
	while (line[i] == ' ')
		i++;
	minirt->light->brightness_ratio = ft_atof(line, &i);
	while (line[i] == ' ')
		i++;
	minirt->light->rgb.r = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	minirt->light->rgb.g = ft_atoi(&line[++i]);
	while (ft_isdigit(line[i]))
		i++;
	minirt->light->rgb.b = ft_atoi(&line[++i]);
	minirt->light->colour = ft_rgb_hex(0, minirt->light->rgb);
//	printf("[RATIO] %f\n", minirt->ambient->lighting_ratio);
//	printf("[COLOR] r: %d, g: %d, b: %d\n", r, g, b);
//	minirt->ambient->colour = fl_rgb_hex(r, g, b);
	ft_print_light(minirt);
}
