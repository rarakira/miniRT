

#include <stdlib.h>

#include "../../includes/minirt.h"
#include "../../includes/camera.h"
#include "../../includes/parsing.h"
#include "../../includes/error_msgs.h"

//t_camera	*create_camera(t_vector *org, t_vector *dir, float angle)
//{
//	t_camera	*camera;
//
//	camera = malloc(sizeof(t_camera));
//	if (camera == NULL)
//		exit_on_error(-1, ERR_MALLOC);
//	camera->origin = org;
//	camera->direction = dir;
//	camera->angle = angle;
//	return (camera);
//}

void	ft_free_camera(t_minirt *minirt)
{
	if (minirt->camera)
	{
		if (minirt->camera->origin)
		{
			if (minirt->camera->direction)
				free(minirt->camera->direction);
			free(minirt->camera->origin);
		}
		free(minirt->camera);
	}
}

void	ft_print_camera(t_minirt *minirt)
{
	printf(COLOR_OK"\n########## CAMERA ##########\n");
	printf("[ORIGIN] x: %f, y: %f, z: %f\n",
		   minirt->camera->origin->x,
		   minirt->camera->origin->y,
		   minirt->camera->origin->z);
	printf("[DIRECTION] x: %f, y: %f, z: %f\n",
		   minirt->camera->direction->x,
		   minirt->camera->direction->y,
		   minirt->camera->direction->z);
	printf("[ANGLE] %f\n", minirt->camera->angle);
	printf("---------- ------ ----------\n"COLOR_END);

}



void	ft_init_camera(t_minirt *minirt)
{
	minirt->camera = malloc(sizeof(t_camera));
	if (!minirt->camera)
	{
		write(2, ERROR_MALLOC, ft_strlen(ERROR_MALLOC));
		ft_free_camera(minirt);
		exit(ERROR_MALLOC_CAMERA);
	}
	minirt->camera->origin = malloc(sizeof(t_vector));
	if (!minirt->camera->origin)
	{
		write(2, ERROR_MALLOC, ft_strlen(ERROR_MALLOC));
		ft_free_camera(minirt);
		exit(ERROR_MALLOC_CAMERA_ORIGIN);
	}
	minirt->camera->direction = malloc(sizeof(t_vector));
	if (!minirt->camera->direction)
	{
		write(2, ERROR_MALLOC, ft_strlen(ERROR_MALLOC));
		ft_free_camera(minirt);
		exit(ERROR_MALLOC_CAMERA_DIRECTION);
	}
}

void	ft_read_camera(t_minirt *minirt, char *line)
{
	int i;

	i = 1;
	while (line[i] == ' ')
		i++;
	minirt->camera->origin->x = ft_atof(line, &i);
	minirt->camera->origin->y = ft_atof(line, &i);
	minirt->camera->origin->z = ft_atof(line, &i);
	while (line[i] == ' ')
		i++;
	minirt->camera->direction->x = ft_atof(line, &i);
	minirt->camera->direction->y = ft_atof(line, &i);
	minirt->camera->direction->z = ft_atof(line, &i);
	while (line[i] == ' ')
		i++;
	minirt->camera->angle = ft_atof(line, &i);
	ft_print_camera(minirt);
}
