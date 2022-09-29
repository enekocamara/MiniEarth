/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:42:14 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/28 17:14:26 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>   


/*void	cuadricula(double min_x, double min_y, double max_x, double max_y, double iter_x, double iter_y)
{
	printf();
}*/

int	random_number(int max)
{
	return (rand() % max);
}

void	grid(int i, int num, double y)
{
	double x;
	int		z;
	double	radious = 5;
	double	step;
	
	step = 10;
	x = i % (int)sqrt(num);
	z = i / (int)sqrt(num);
	printf("%lf,%lf,%lf ", x * step,y,z * step);
}

void	sea(int maxx, int minx, int maxy, int miny, int maxz, int minz)
{
	double x;
	double	y;
	double	z;
	x = random_number(maxx + minx) - minx;
	y = random_number(maxy + miny) - miny;
	z = random_number(maxz + minz) - minz;
	printf("%lf,%lf,%lf ", x, y, z);
}

void	normal(double x, double y,double z)
{
	printf("%lf,%lf,%lf ",x, y,z);
}


void	value(double value)
{
	printf("%lf ", value);
}

void	color(double x, double y, double z)
{
	printf("%lf,%lf,%lf ", x,y,z);
}

void	sphere(int num)
{
	int	i;

	i = 0;
	while(i < num)
	{
		printf("sp ");
		//grid(i, num, 10);
		sea(20, 20, 20, 20, 0, 1);
		value(1);
		color(100,100,255);
		printf("\n");
		i++;
	}
}

void	cilinder(int num)
{
	int	i;

	i = 0;
	while(i < num)
	{
		printf("cy ");
		grid(i, num, 0);
		normal(0,1,0);
		value(1);
		value(10);
		color(50,50,150);
		printf("\n");
		i++;
	}
}


int	main(void)
{
	int	fd;

	char	*name;
	name = "trial.rt";
	fd = open(name, O_RDWR | O_CREAT | O_TRUNC);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	//printf("A 0.3 255,255,255\nC 62.5,120,62.5 0,-1,0 120\nL 62.5,400,62.5 1 255,255,255\n");
	sphere(500);
	//cilinder(100);
	return (0);
}