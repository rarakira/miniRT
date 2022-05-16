/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:42:37 by lbaela            #+#    #+#             */
/*   Updated: 2022/02/08 20:52:35 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIN_WIDTH	1200
# define WIN_HEIGHT	800

# define MIN_DIST	0.0001
# define MAX_DIST	100000000.0

# define COL_RED		0x00D13632
# define COL_ORANGE		0x00E2571E
# define COL_YELLOW		0x00CDB924
# define COL_GREEN		0x00479E1B
# define COL_BLUE		0x001D829E
# define COL_VIOLET		0x00503FA9
# define COL_BLACK		0x002B2B2A

int							g_obj_n;

typedef struct s_minirt		t_minirt;
typedef struct s_vector		t_vector;
typedef struct s_point		t_point;
typedef struct s_ambient	t_ambient;
typedef struct s_camera		t_camera;
typedef struct s_light		t_light;
typedef struct s_object		t_object;
typedef struct s_scene		t_scene;
typedef struct s_rgb		t_rgb;

typedef struct s_rgb
{
	int			r;
	int			g;
	int			b;
}				t_rgb;

typedef struct s_minirt {
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;

	t_ambient	*ambient;
	t_camera	*camera;
	t_light		*light;
	t_object	*objs_lst;
	t_object	**objs;
}				t_minirt;

typedef struct s_vector
{
	float		x;
	float		y;
	float		z;
}				t_vector;

typedef struct s_point
{
	float		dist;
	int			colour;
	char		type;
	t_vector	hit_coord;
	t_vector	norm_v;
	t_rgb		rgb;
	t_object	*obj;
}				t_point;

/* drawing functions */
void		my_mlx_pixel_put(t_minirt *minirt, int x, int y, int color);
void		fill_background(t_minirt *minirt);
int			ft_rgb_hex(int t, t_rgb rgb);

/* hooks */
void		register_hooks(t_minirt *minirt);
int			key_hook(int keycode, t_minirt *minirt);

/* error and memory handling */
int			free_minirt(t_minirt *minirt);
void		exit_on_error(int err, char *msg);

/* ray tracing */
void		ray_tracing(t_minirt *minirt);
void		object_intersects(	t_minirt *minirt,
				t_object **objs, t_vector *ray, t_point *point);
float		sphere_intersects(t_camera *cam, t_object *obj, t_vector *ray);
float		plane_intersects(t_camera *cam, t_object *obj, t_vector *ray);
float		cylinder_intersects(t_camera *cam, t_object *obj, t_vector *ray);

/* vector functions */
t_vector	*new_vect(float x, float y, float z);
t_vector	vect_add(t_vector *v1, t_vector *v2);
t_vector	vect_substract(t_vector *v1, t_vector *v2);
float		vect_len(t_vector *vect);
void		normalise_vect(t_vector *vect);
float		vect_dot_product(t_vector *v1, t_vector *v2);
t_vector	vect_mult(t_vector *vect, float n);
t_vector	vect_div(t_vector *vect, float n);
t_vector	reflect_vector(t_vector ray, t_vector norm);
float		vector_scalar(t_vector v1, t_vector v2);

#endif
