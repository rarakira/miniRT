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
	t_rgb 	colour; // rgb -> hex conversion
} t_ambient;

typedef struct s_vector	t_vector;

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
	int			colour;
	struct s_object *next;
	struct s_object *previous;
}				t_object;

void	ft_init_ambient(t_minirt *minirt);
void	ft_read_ambient(t_minirt *minirt, char *line);
t_object		*new_sphere(t_vector *center, float radius, int colour);

#endif
