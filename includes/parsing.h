/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:27:03 by dredfort          #+#    #+#             */
/*   Updated: 2022/03/01 20:17:18 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# include "structure_prototypes.h"

/* scene_inits */
t_light		*ft_light_init(t_scene *scene);
t_object	*ft_object_init(t_scene *scene);
t_light		**ft_lights_init(int i, t_scene *scene);
t_object	**ft_objects_init(int i, t_scene *scene);

/* scene_preparation */
void		ft_prepare_scene(t_scene *scene);
void		ft_camera_rotation(t_scene *scene);

/* scene_utilities */
t_light		**ft_convert_lights2arr(t_scene *scene);
t_object	**ft_convert_objects2arr(t_scene *scene);
void		ft_light_as_object(t_scene *scene, t_light *light);

//parsing_scene.c
void		ft_parsing_scene(int fd, int longest_line, t_scene *scene);

//parsing_scene_properties.c
char		ft_check_color(t_rgb c);
char		ft_check_orientation(t_vector v);
void		ft_parsing_ambient(t_scene *scene, char *str, int i);
void		ft_parsing_camera(t_scene *scene, char *str, int i);
void		ft_parsing_light(t_scene *scene, char *str, int i);

//parsing_scene_objects.c
void		ft_parsing_sphere(t_scene *scene, char *str, int i);
void		ft_parsing_plane(t_scene *scene, char *str, int i);
void		ft_parsing_cylinder(t_scene *scene, char *str, int i);
void		ft_parsing_cone(t_scene *scene, char *str, int i);

//utilities.c
void		ft_check_next_parametr(char *str, int i, t_scene *scene);
void		ft_count_separators(char *str, int *i, char *separator);
t_vector	ft_parsing_vector(char *str, int *i, t_scene *scene);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
void		*ft_memset(void *b, int c, size_t len);

//utilities_atoi_atof.c
int			ft_atoi(const char *str);
float		ft_atof(char *str, int *i);

//utilities_color.c
t_rgb		ft_adjust_rgb(t_rgb color);
int			ft_rgb2hex(char t, t_rgb color);
t_rgb		ft_get_rgb(int r, int g, int b);
t_rgb		ft_parsing_color(char *str, int i, t_scene *scene);

//utilities_string.c
size_t		ft_strlen(const char *s);
int			ft_longest_line(int fd);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
