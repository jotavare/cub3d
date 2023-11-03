#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include "keys.h"

typedef struct	s_data {
	void	        *img;
	char	        *addr;
	int		        bits_per_pixel;
	int		        line_length;
	int		        endian;
}				t_data;

typedef struct	s_vars {
	void	        *mlx;
	void	        *win;
    int             x;
    int             y;
}				t_vars;

int	keypress(int keycode, t_vars *vars);
int keyrelease(int keycode, t_vars *vars);
int destroy(int keycode, t_vars *vars);
int motion(int button, int x, int y, t_vars *vars);

#endif