#ifndef CUB_STRUCT_H
#define CUB_STRUCT_H

# define R_FLAG 0b00000001
# define NO_FLAG 0b00000010
# define SO_FLAG 0b00000100
# define WE_FLAG 0b00001000
# define EA_FLAG 0b00010000
# define S_FLAG 0b00100000
# define F_FLAG 0b01000000
# define C_FLAG 0b10000000
# define ALL_PARAMS 63

typedef struct s_dot {
	float x;
	float y;
} t_dot;

typedef struct s_texture {
	void *img;
	char *addr;
	int bpp;
	int llen;
	int endian;
	int width;
	int height;
} t_texture;

typedef struct s_wall_inter {
	int i;
	int j;
	float x;
	float y;
	int color;
	int type;
	double dist;
	double tex_w;
	double height;
} t_wall_inter;

typedef struct s_game {
	unsigned char	paramflag;
	int		width;
	int		height;
	t_texture no_tex;
	t_texture so_tex;
	t_texture we_tex;
	t_texture ea_tex;
	t_texture s_tex;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	int		f;
	int		c;
	void	*mlx_con;
	void	*window;
	void	*img;
	char	*imgadr;
	int		bpp;
	int		llen;
	int		endian;
	void	*map;
	int		mapwidth;
	int		mapheight;
	t_dot	player_pos;
	double		view_angle;

} t_game;

#endif
