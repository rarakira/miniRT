/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_prototypes.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:30:50 by lbaela            #+#    #+#             */
/*   Updated: 2022/03/01 17:27:24 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_PROTOTYPES_H
# define STRUCTURE_PROTOTYPES_H

typedef struct s_minirt				t_minirt;
typedef struct s_scene				t_scene;
typedef struct s_vector				t_vector;
typedef struct s_point				t_point;
typedef struct s_intersection		t_intersection;
typedef struct s_ambient			t_ambient;
typedef struct s_camera				t_camera;
typedef struct s_light				t_light;
typedef struct s_object				t_object;
typedef struct s_rgb				t_rgb;
typedef struct s_eq					t_eq;

typedef struct s_plane
{
	float		w;
	float		h;
	float		x_pix;
	float		y_pix;
	int			mlx_x;
	int			mlx_y;
	float		x_angle;
	float		y_angle;
}			t_plane;

typedef struct s_rgb
{
	int			r;
	int			g;
	int			b;
}				t_rgb;

typedef struct s_vector
{
	float		x;
	float		y;
	float		z;
}				t_vector;

typedef struct s_point
{
	float		dist;
	int			color;
	char		type;
	t_vector	hit_coord;
	t_vector	norm_v;
	t_vector	light_dir;
	t_rgb		rgb;
	t_object	*obj;
}				t_point;

enum e_types
{
	BODY	= 1,
	CAP		= 2,
};

enum e_objects
{
	CYLINDER	= 'C',
	PLANE		= 'P',
	SPHERE		= 'S',
	CONE		= 'O',
	LIGHT		= 'L',
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

typedef struct s_object
{
	char				type;
	t_vector			center;
	t_vector			norm_v;
	float				radius;
	float				height;
	t_rgb				rgb;
	t_light				*light;

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

typedef struct s_ambient
{
	float		brightness;
	t_rgb		rgb;
}				t_ambient;

typedef struct s_camera
{
	t_vector	point;
	t_vector	orientation;
	float		fov;
}				t_camera;

typedef struct s_light
{
	t_vector			point;
	float				brightness;
	t_rgb				rgb;
	struct s_light		*next;
	struct s_light		*previous;
}						t_light;

typedef struct s_counters
{
	char	ambients;
	char	cameras;
	int		lights;
	int		objects;
}			t_counters;

typedef struct s_scene
{
	t_ambient		ambient;
	t_camera		camera;
	t_light			**lights;
	t_object		**objs;

	t_light			*light;
	t_object		*object;
	t_rgb			origin_color;
	t_counters		counter;
}					t_scene;

typedef struct s_pattern
{
	void	*img;
	void	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}			t_pattern;

typedef struct s_minirt {
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			size_x;
	int			size_y;
	t_scene		scene;
	t_pattern	texture;
	t_pattern	bump;
	char		apply_texture;
	char		apply_bump;
	char		apply_checkerboard;
}				t_minirt;

#endif
