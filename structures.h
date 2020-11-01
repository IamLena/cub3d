/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 20:28:55 by nalecto           #+#    #+#             */
/*   Updated: 2020/11/01 01:22:21 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# define R_FLAG 0b00000001
# define NO_FLAG 0b00000010
# define SO_FLAG 0b00000100
# define WE_FLAG 0b00001000
# define EA_FLAG 0b00010000
# define S_FLAG 0b00100000
# define F_FLAG 0b01000000
# define C_FLAG 0b10000000
# define ALL_PARAMS 255

typedef struct	s_dot {
	double	x;
	double	y;
}				t_dot;

typedef struct	s_texture {
	void	*img;
	char	*addr;
	int		bpp;
	int		llen;
	int		endian;
	int		width;
	int		height;
}				t_texture;

typedef struct	s_wall_inter
{
	int			i;
	int			j;
	double		x;
	double		y;
	t_texture	*tex;
	double		tex_w;
	double		dist;
	double		height;
}				t_wall_inter;

typedef struct	s_sprite_list
{
	double					y;
	double					x;
	double					height;
	double					width;
	double					dist;
	int						cnt;
	t_texture				*tex;
	struct s_sprite_list	*next;
}				t_sprite;

typedef struct	s_game {
	unsigned char	paramflag;
	void			*mlx_con;
	void			*window;
	t_texture		result;
	t_texture		no_tex;
	t_texture		so_tex;
	t_texture		we_tex;
	t_texture		ea_tex;
	t_texture		s_tex;
	int				f;
	int				c;
	void			*map;
	int				mapwidth;
	int				mapheight;
	t_dot			player_pos;
	double			view_angle;
	t_sprite		*sprites;
	int				rc;
	char			*msg;
	t_wall_inter	*walls;
}				t_game;
#endif
