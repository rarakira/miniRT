

#ifndef CAMERA_H
# define CAMERA_H

typedef struct s_vector	t_vector;

typedef struct s_camera
{
	t_vector	*origin;
	t_vector	*direction;
	float		angle;
}				t_camera;

void	ft_init_camera(t_minirt *minirt);
void	ft_read_camera(t_minirt *minirt, char *line);
void	ft_free_camera(t_minirt *minirt);

#endif
