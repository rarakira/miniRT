/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:30:24 by lbaela            #+#    #+#             */
/*   Updated: 2022/01/19 13:20:58 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

typedef struct s_rgb
{
	int	r;
	int g;
	int b;
} t_rgb;

typedef struct s_ambient
{
	float	lighting_ratio; // [0.0,1.0]
	t_rgb 	rgb; // rgb -> hex conversion
	int		colour;
} t_ambient;

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
	int 		colour;
} t_light;

/*
Types in *CAPITAL*:
'S' = sphere, 'P' = plane, 'C' = cyllinder
*/
typedef struct s_object
{
	char		type;
	t_vector	*center;
	t_vector	*norm_v;
	float		radius;
	float		height;
	t_rgb		rgb; // rgb -> hex conversion
	int			colour;
	struct s_object *next;
	struct s_object *previous;
}				t_object;

void	ft_init_ambient(t_minirt *minirt);
void	ft_read_ambient(t_minirt *minirt, char *line);
void	ft_init_camera(t_minirt *minirt);
void	ft_read_camera(t_minirt *minirt, char *line);
void	ft_free_camera(t_minirt *minirt);
void	ft_init_light(t_minirt *minirt);
void	ft_read_light(t_minirt *minirt, char *line);
void	ft_init_objs_list(t_minirt *minirt);
void	ft_read_sphere(t_minirt *minirt, char *line);
void	ft_add_obj_to_lst(t_minirt *minirt, char *line);
t_object		*new_sphere(t_vector *center, float radius, int colour);

#endif
