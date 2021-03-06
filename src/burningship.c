/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BurningShip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnekhay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 21:32:36 by vnekhay           #+#    #+#             */
/*   Updated: 2018/03/31 22:39:19 by vnekhay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			burningship_envs(t_envs *f)
{
	f->max_circles = 50;
	f->closer = 220;
	f->x1 = -2.2;
	f->y1 = -2.5;
	f->color = 1600;
}

static	void	multitudeburningship(t_envs *f)
{
	f->x3 = f->x / f->closer + f->x1;
	f->y3 = f->y / f->closer + f->y1;
	f->x4 = 0;
	f->y4 = 0;
	f->circles = 0;
	while (f->x4 * f->x4 + f->y4 * f->y4 < 4
			&& f->circles < f->max_circles)
	{
		f->temp = f->x4 * f->x4 - f->y4 * f->y4 + f->x3;
		f->y4 = fabs(2 * f->x4 * f->y4) + f->y3;
		f->x4 = f->temp;
		f->circles++;
	}
	if (f->circles == f->max_circles)
		putpixel(f, f->x, f->y, 0x000000);
	else
		putpixel(f, f->x, f->y, (f->color * f->circles));
}

void			*start_burningship(void *mas)
{
	t_envs		*f;
	double		temp;

	f = (t_envs *)mas;
	f->x = 0;
	temp = f->y;
	while (f->x < 1000)
	{
		f->y = temp;
		while (f->y < f->y_m)
		{
			multitudeburningship(f);
			f->y++;
		}
		f->x++;
	}
	return (mas);
}

void			multiburningship(t_envs *f)
{
	t_envs		tab[8];
	pthread_t	t[8];
	int			i;

	i = 0;
	while (i < 8)
	{
		ft_memcpy((void*)&tab[i], (void*)f, sizeof(t_envs));
		tab[i].y = 100 * i;
		tab[i].y_m = 100 * (i + 1);
		i++;
	}
	i = 0;
	while (++i <= 8)
		pthread_create(&t[i - 1], NULL, start_burningship, &tab[i - 1]);
	while (i--)
		pthread_join(t[i], NULL);
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}
