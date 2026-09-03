#include "../../minirt.h" 

void	escape_cfg(mlx_key_data_t keydata, void *param) 
{
	mlx_t *mlx;

    	mlx = (mlx_t *)param;
        if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        	mlx_close_window(mlx);
}
