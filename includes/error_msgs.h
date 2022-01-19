/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msgs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:42:06 by lbaela            #+#    #+#             */
/*   Updated: 2022/01/18 22:11:32 by lbaela           ###   ########.fr       */
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

#endif
