/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_3_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziloughm <ziloughm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 23:40:19 by ziloughm          #+#    #+#             */
/*   Updated: 2023/01/19 15:48:51 by ziloughm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3D_bonus.h"

int	ft_ray_facing(float ray_ang, char *face)
{
	if (!face)
		return (-10);
	if (!ft_strcmp(face, "up_do"))
	{
		if (ray_ang > 0 && ray_ang < PI)
			return (SIZE_WIN);
		return (0);
	}
	if (!ft_strcmp(face, "le_ri"))
	{
		if (ray_ang <= (PI / 2) || ray_ang >= (PI * 3 / 2))
			return (1);
		return (0);
	}
	return (-10);
}

int	ft_end_win(t_data *data, float x, float y)
{
	if (x > 0 && x <= data->gm->map_w && \
	y > 0 && y <= data->gm->map_h)
		return (0);
	return (1);
}

int	ft_hit_type(int i, int j, int index, t_data *data)
{
	if ((data->gm->map[j][i] == '4' || data->gm->map[j][i] == '3') \
	&& (data->raycat->rays[index].door[0] == -1 \
	|| data->raycat->rays[index].door[1] == -1))
	{
		data->raycat->rays[index].door[0] = j;
		data->raycat->rays[index].door[1] = i;
	}
	(void)index;
	if (data->gm->map[j][i] == '1')
		return (1);
	else if (data->gm->map[j][i] == '3')
		return (3);
	else if (data->gm->map[j][i] == '4')
		return (4);
	else
		return (0);
}

int	ft_wall_grid(t_data *data, t_info in, int index)
{
	int	i;
	int	j;

	if (in.xhit < 0 || in.xhit >= data->gm->map_w || \
	in.yhit < 0 || in.yhit >= data->gm->map_h)
		return (1);
	i = (int)floor(in.xhit / SIZE_WIN);
	j = (int)floor(in.yhit / SIZE_WIN);
	if (i < 0 || i >= data->gm->nb_col || \
		j < 0 || j >= data->gm->nb_row)
		return (1);
	return (ft_hit_type(i, j, index, data));
}

float	ft_calc_distance(t_data *data, t_point point)
{
	float	x;
	float	y;

	x = pow((point.x - data->pp_y), 2);
	y = pow((point.y - data->pp_x), 2);
	return (sqrt(x + y));
}
