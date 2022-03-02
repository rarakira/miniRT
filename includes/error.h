/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:45:03 by dredfort          #+#    #+#             */
/*   Updated: 2022/03/02 09:23:29 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

//TEXT COLORS
# define TC_ERROR	"\033[31m"
# define TC_OK		"\033[32m"
# define TC_END		"\033[0m"

//ERROR MESSAGES
# define EM_NO_ARG			"Scene description file not specified"
# define EM_NO_SCENE_FILE	"No scene description file specified"
# define EM_BAD_FORMAT		"Incorrect formatting of the scene description file"
# define EM_RGB_FORMAT		"Incorrect RGB color formatting"
# define EM_VCT_FORMAT		"Incorrect vector formatting"

# define EM_FILE_OPEN		"Failed to open scene description file"
# define EM_FILE_READING	"Unable to read scene description file"
# define EM_FILE_CLOSE		"Failed to close scene description file"

# define EM_AMBIENT_DECL	"Ambient is already declared in the scene"
# define EM_AMBIENT_NDECL	"No ambient is declared in the scene"
# define EM_AMBIENT_LIGHT	"Ambient lighting ratio not in [0, 1]"
# define EM_AMBIENT_COLOR	"Ambient R,G,B colors not in [0, 255]"

# define EM_CAMERA_DECL		"Camera is already declared in the scene"
# define EM_CAMERA_NDECL	"No camera is declared in the scene"
# define EM_CAMERA_ORIENT	"Camera x,y,z orientation vector not in [-1, 1]"
# define EM_CAMERA_NNORM	"Camera orientation vector not normalized"
# define EM_CAMERA_FOV		"Camera horizontal fow not in [0, 180]"

# define EM_LIGHT_DECL		"Light is already declared in the scene"
# define EM_LIGHT_NDECL		"No light is declared in the scene"
# define EM_LIGHT_BRIGHT	"Light brightness ratio not in [0, 1]"
# define EM_LIGHT_COLOR		"Light R,G,B colors not in [0, 255]"

# define EM_OBJECT_NDECL	"No object is declared in the scene"

# define EM_SPHERE_COLOR	"Sphere R,G,B colors not in [0, 255]"

# define EM_PLANE_ORIENT	"Plane x,y,z orientation vector not in [-1, 1]"
# define EM_PLANE_NNORM		"Plane orientation vector not normalized"
# define EM_PLANE_COLOR		"Plane R,G,B colors not in [0, 255]"

# define EM_CLND_ORIENT		"Cylinder x,y,z orientation vector not in [-1, 1]"
# define EM_CLND_NNORM		"Cylinder orientation vector not normalized"
# define EM_CLND_COLOR		"Cylinder R,G,B colors not in [0, 255]"

# define EM_CONE_ORIENT		"Cone x,y,z orientation vector not in [-1, 1]"
# define EM_CONE_NNORM		"Cone orientation vector not normalized"
# define EM_CONE_COLOR		"Cone R,G,B colors not in [0, 255]"

# define EM_MALLOC_LINE		"Failed to allocate memory for line"
# define EM_MALLOC_SCENE	"Failed to allocate memory for scene"
# define EM_MALLOC_LIGHT	"Failed to allocate memory for light"
# define EM_MALLOC_OBJECT	"Failed to allocate memory for object"
# define EM_MALLOC_LGHT_ARR	"Failed to allocate memory for lights array"
# define EM_MALLOC_OBJS_ARR	"Failed to allocate memory for objects array"
# define EM_MALLOC_VIEW		"Failed to allocate memory for view"

typedef struct s_scene				t_scene;

void	ft_free_scene(t_scene *scene);
void	ft_error(char *error_type, t_scene *scene);
void	ft_normal_error(char *error_type, t_vector *norm_v);
#endif
