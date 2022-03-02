/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:42:37 by lbaela            #+#    #+#             */
/*   Updated: 2022/03/02 09:23:01 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIN_WIDTH	1200
# define WIN_HEIGHT	800

# define MIN_DIST		0.0001
# define MAX_DIST		100000000.0

# define COL_RED		0x00D13632
# define COL_ORANGE		0x00E2571E
# define COL_YELLOW		0x00CDB924
# define COL_GREEN		0x00479E1B
# define COL_BLUE		0x001D829E
# define COL_VIOLET		0x00503FA9
# define COL_BLACK		0x002B2B2A

# include <stdio.h>
# include "structure_prototypes.h"

void		ft_print_scene(t_scene *scene);

t_rgb		ft_pattern(t_object *obj, t_vector ray, t_minirt *minirt);
t_rgb		ft_checkerboard(t_object *sphere, t_point *point);

/* drawing functions */
void		ft_put_pixel(t_minirt *gl, int x, int y, int color);
void		my_mlx_pixel_put(t_minirt *minirt, int x, int y, int color);
void		fill_background(t_minirt *minirt);

/* colors */
int			ft_rgb_hex(int t, t_rgb rgb);
t_rgb		ft_get_rgb(int r, int g, int b);
t_rgb		ft_rgb2gray(t_rgb rgb);
t_rgb		invert_color(t_rgb color);
t_rgb		ft_rgb_brightness_adjustment(t_rgb rgb, float adjust);

/* hooks */
void		ft_register_hooks(t_minirt *minirt);

/* memory handling */
void		*ft_memset(void *b, int c, size_t len);

/* graphics */
void		ft_graphic_layer(t_scene *scene);
t_plane		get_projection_plane(float scene_w, float scene_h, float angle);
void		ray_tracing(t_minirt *minirt);
t_object	*object_intersects(t_minirt *minirt,
				t_object **objs, t_vector ray, t_point *point);
float		sphere_intersects(t_vector origin, t_object *obj, t_vector ray);
float		plane_intersects(t_vector origin, t_object *obj, t_vector ray);
float		cylinder_intersects(t_vector origin, t_object *obj, t_vector ray);
float		cone_intersects(t_vector origin, t_object *obj, t_vector ray);
t_vector	get_hit_direction(t_object *obj, t_vector ray);
int			get_cylinder_caps(	t_eq *caps,
				t_object *obj, t_vector ray, t_vector origin);
int			get_cone_cap(	t_eq *cap,
				t_object *obj, t_vector ray, t_vector origin);

/* light functions */
void		update_point_color(t_scene *scene, t_point *point, t_vector ray);

t_rgb		calc_rgb_light(t_rgb color, double light);
t_rgb		multiply_rgbs(t_rgb a, t_rgb b);
t_rgb		add_rgb_light(t_rgb a, t_rgb b);
t_rgb		invert_color(t_rgb color);

/* vector functions */
t_vector	new_vect(float x, float y, float z);
t_vector	vect_add(t_vector v1, t_vector v2);
t_vector	vect_substract(t_vector v1, t_vector v2);
float		vect_len(t_vector vect);
void		normalise_vect(t_vector *vect);
float		vect_dot_product(t_vector v1, t_vector v2);
t_vector	vect_mult(t_vector vect, float n);
t_vector	vect_div(t_vector vect, float n);
float		point_dist(t_vector v1, t_vector v2);
t_vector	ft_vector_rotate_cw(t_vector vector);
t_vector	ft_vector_rotate_ccw(t_vector vector);

#endif
