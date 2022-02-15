/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msgs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:42:06 by lbaela            #+#    #+#             */
/*   Updated: 2022/02/15 14:33:12 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MSGS_H
# define ERROR_MSGS_H

# define ERR_MALLOC			"Error\nMemory allocation failed\n"
# define ERR_ARGS			"Error\nWrong # of arguments: ./fdf map_file\n"
# define ERR_MAP			"Error\nBad formatting of the map_file\n"
# define ERR_READING		"Error\nCannot read the map_file\n"
# define ERR_FD_OPEN		"Error\nCould not open the map_file\n"
# define ERR_FD_CLOSE		"Error\nCould not close the map_file\n"
# define ERR_IS_DIR			"Error\nThe file is a directory, not a map\n"
# define ERR_MLX			"Error\nMLX initiation failed\n"
# define ERR_WIN			"Error\nWindow initiation failed\n"
# define ERR_IMG			"Error\nError on image initiation\n"

#define SUCCES								0
#define ERROR_FILE_OPEN						1

#define ERROR_MALLOC_LINE					2
#define ERROR_MALLOC_AMBIENT				3
#define ERROR_MALLOC_CAMERA					4
#define ERROR_MALLOC_CAMERA_ORIGIN			5
#define ERROR_MALLOC_CAMERA_DIRECTION		6
#define ERROR_MALLOC_LIGHT					7
#define ERROR_MALLOC_LIGHT_ORIGIN			8
#define ERROR_MALLOC_OBJECTS_LIST			9

#define ERROR_MALLOC		"Error\nMemory allocation failed\n"

#endif
