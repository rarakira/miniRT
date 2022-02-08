/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:45:58 by lbaela            #+#    #+#             */
/*   Updated: 2022/01/19 11:05:16 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

typedef struct s_vector	t_vector;

typedef struct s_camera
{
	t_vector	*origin;
	t_vector	*direction;
	float		angle;
}				t_camera;

t_camera	*create_camera(t_vector *org, t_vector *dir, float angle);

#endif
