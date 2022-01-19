/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:42:37 by lbaela            #+#    #+#             */
/*   Updated: 2022/01/19 09:55:52 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIN_WIDTH	1200
# define WIN_HEIGHT	800

typedef struct s_camera	t_camera;
typedef struct s_object	t_object;
typedef struct s_scene	t_scene;

typedef struct s_minirt {
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_scene		*scene;
}				t_minirt;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}				t_vector;

typedef struct s_scene
{
	t_camera	*cams;
	t_object	*objs;
	float		width;
	float		height;
}				t_scene;

/* scene init*/
t_scene		*new_scene(t_camera *cam, t_object *obj);

/* hooks */
void		register_hooks(t_minirt *minirt);
int			key_hook(int keycode, t_minirt *minirt);

/* error and memory handling */
int			free_minirt(t_minirt *minirt);
void		exit_on_error(int err, char *msg);

/* vector functions */
t_vector	*new_vect(float x, float y, float z);
t_vector	*vect_substract(t_vector *v1, t_vector *v2);
float		vect_len(t_vector *vect);
void		normalise_vect(t_vector *vect);
float		vect_dot_product(t_vector *v1, t_vector *v2);

#endif
