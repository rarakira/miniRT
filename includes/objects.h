/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:30:24 by lbaela            #+#    #+#             */
/*   Updated: 2022/02/15 13:18:27 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

typedef struct s_minirt		t_minirt;
typedef struct s_vector		t_vector;
typedef struct s_point		t_point;
typedef struct s_ambient	t_ambient;
typedef struct s_camera		t_camera;
typedef struct s_light		t_light;
typedef struct s_object		t_object;
typedef struct s_scene		t_scene;
typedef struct s_rgb		t_rgb;

typedef struct s_ambient
{
	float		lighting_ratio; // [0.0,1.0]
	t_rgb		rgb; // rgb -> hex conversion
	int			colour;
}				t_ambient;

typedef struct s_camera
{
	t_vector	*origin;
	t_vector	*direction;
	float		angle;
}				t_camera;

typedef struct s_light
{
	t_vector	*point;
	float		brightness_ratio; // [0.0,1.0]
	t_rgb		rgb; // rgb -> hex conversion
	int			colour;
}				t_light;

enum e_types
{
	body,
	cap,
};

enum e_objects
{
	CYLINDER,
	PLANE,
	SPHERE,
	CONE,
};

typedef struct s_intersection
{
	int			type;
	t_vector	point;
	t_vector	norm_v;
	float		m;
	float		dist;
	short		is_inside;
}				t_intersection;

/*
Types in *CAPITAL*:
'S' = sphere, 'P' = plane, 'C' = cylinder
*/
typedef struct s_object
{
	char				type;
	t_vector			*center;
	t_vector			*norm_v;
	float				radius;
	float				height;
	t_rgb				rgb; // rgb -> hex conversion
	int					colour;

	t_intersection		hit;
	struct s_object		*next;
	struct s_object		*previous;
}						t_object;

typedef struct s_eq
{
	float				a;
	float				b;
	float				c;
	float				discr;
	float				dist1;
	float				dist2;
	float				m1;
	float				m2;
}						t_eq;

void			ft_init_ambient(t_minirt *minirt);
void			ft_read_ambient(t_minirt *minirt, char *line);
void			ft_init_camera(t_minirt *minirt);
void			ft_read_camera(t_minirt *minirt, char *line);
void			ft_free_camera(t_minirt *minirt);
void			ft_init_light(t_minirt *minirt);
void			ft_read_light(t_minirt *minirt, char *line);
void			ft_init_objs_list(t_minirt *minirt);
void			ft_read_sphere(t_minirt *minirt, char *line);
void			ft_read_plane(t_minirt *minirt, char *line);
void			ft_read_cylinder(t_minirt *minirt, char *line);
void			ft_add_obj_to_lst(t_minirt *minirt, char *line);
t_object		*new_sphere(t_vector *center, float radius, int colour);

t_rgb			calc_rgb_light(t_rgb colour, double light);
t_rgb			multiply_rgbs(t_rgb a, t_rgb b);
t_rgb			add_rgb_light(t_rgb a, t_rgb b);

#endif
