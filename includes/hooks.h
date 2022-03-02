/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dredfort <dredfort@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 11:52:04 by dredfort          #+#    #+#             */
/*   Updated: 2022/02/28 12:09:41 by dredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "./minirt.h"
# include "./error.h"
# include "../libs/minilibx_macos/mlx.h"

//REGISTER_HOOKS
void	ft_register_hooks(t_minirt *minirt);

//EXIT
int		ft_exit_hook(int keycode, t_minirt *minirt);
int		ft_red_cross_hook(t_minirt *minirt);

//MOVE_UTILITIES
void	ft_axis_move_x(t_minirt *minirt, char sign);
void	ft_axis_move_y(t_minirt *minirt, char sign);
void	ft_axis_move_z(t_minirt *minirt, char sign);

//MOVE_QE
void	ft_q_move(t_minirt *minirt);
void	ft_e_move(t_minirt *minirt);

//MOVE_WASD
void	ft_w_move(t_minirt *minirt);
void	ft_a_move(t_minirt *minirt);
void	ft_s_move(t_minirt *minirt);
void	ft_d_move(t_minirt *minirt);

//ROTATION_UTILITIES
void	ft_get_sin_a_cos(float *cos_a, float *sin_a, char direction);
void	ft_objs_x_axis_rotation(t_object **objs, float cos_a, float sin_a);
void	ft_lights_x_axis_rotation(t_light **lights, float cos_a, float sin_a);
void	ft_objs_y_axis_rotation(t_object **objs, float cos_a, float sin_a);
void	ft_lights_y_axis_rotation(t_light **lights, float cos_a, float sin_a);

//ROTATION
void	ft_x_rotation(t_minirt *minirt, char direction);
void	ft_y_rotation(t_minirt *minirt, char direction);
void	ft_x_camera_rotation(t_scene *scene);
void	ft_y_camera_rotation(t_scene *scene);
void	ft_z_camera_rotation(t_scene *scene);

//CHANGE_SETTINGS
void	ft_change_radius(t_minirt *minirt, char sign);
void	ft_change_height(t_minirt *minirt, char sign);
void	ft_change_brightness(t_minirt *minirt, char sign);

//PATTERN_SETTINGS
void	ft_apply_texture(t_minirt *minirt);
void	ft_apply_bump(t_minirt *minirt);
void	ft_apply_checkerboard(t_minirt *minirt);

//OBJECT_SELECTION
void	ft_object_selection(int mx, int my, t_minirt *minirt);
#endif
