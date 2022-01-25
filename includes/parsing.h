//
// Created by Dmitry Novikov on 25.01.2022.
//

#ifndef PARSING_H
#define PARSING_H

#include "../libs/libft/libft.h"
#include "minirt.h"
#include "objects.h"
#include "error_msgs.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>



#define COLOR_ERROR "\033[31m"
#define COLOR_OK "\033[32m"
#define COLOR_END "\033[0m"



#define ERROR_RGB -1

//typedef struct s_ambient
//{
//	float	lighting; //[0.0,1.0]
//	short	rgb[3]; //[0-255][0-255][0-255]
//} t_ambient;
//
////typedef struct s_camera
////{
////	float	x;
////	float	y;
////	float	z;
////	float	ox; //[-1,1]
////	float	oy; //[-1,1]
////	float	oz; //[-1,1]
////	char	fov; //[0,180]
////} t_camera;
//
//typedef struct s_light
//{
//	float	x;
//	float	y;
//	float	z;
//	float	brightness; //[0.0,1.0]
//	char	r; //[0-255]
//	char	g; //[0-255]
//	char	b; //[0-255]
//} t_light;
//
//typedef struct s_objects
//{
//	t_ambient	*ambient;
//	t_camera	*camera;
//	t_light		*light;
//	char	identifier[2];
//	float	x;
//	float	y;
//	float	z;
//	float	ox; //[-1,1]
//	float	oy; //[-1,1]
//	float	oz; //[-1,1]
//	float	d;
//	float	h;
//	char	r; //[0-255]
//	char	g; //[0-255]
//	char	b; //[0-255]
//////	Sphere
////	identifier: sp
////	∗ x,y,z coordinates of the sphere center: 0.0,0.0,20.6
////	∗ the sphere diameter: 12.6
////	∗ R,G,B colors in range [0-255]: 10, 0, 255
////
//////	Plane
////	identifier: pl
////	∗ x,y,z coordinates: 0.0,0.0,-10.0
////	∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
////			0.0,0.0,1.0
////	∗ R,G,B colors in range [0-255]: 0, 0, 255
////
//////	Cylinder
////	∗ identifier: cy
////			cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
////	∗ x,y,z coordinates: 50.0,0.0,20.6
////	∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
////			0.0,0.0,1.0
////	∗ the cylinder diameter: 14.2
////	∗ the cylinder height: 21.42
////	∗ R,G,B colors in range [0,255]: 10, 0, 255
//
//////	Cone, Hyperboloid, Paraboloid
//
//	struct s_objects *next;
//} t_objects;

void	ft_parsing(char *file_name, t_minirt *minirt);
float	ft_atof(char *line, int *i);
int		fl_rgb_hex(int r, int g, int b);

#endif
