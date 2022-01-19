/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:30:24 by lbaela            #+#    #+#             */
/*   Updated: 2022/01/18 21:04:27 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

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
}				t_object;

t_object	*new_sphere(t_vector *center, float radius);

#endif
