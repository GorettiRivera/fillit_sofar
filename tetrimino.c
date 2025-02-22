/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrimino.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrivera- <mrivera-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 09:26:31 by mrivera-          #+#    #+#             */
/*   Updated: 2019/08/01 09:54:26 by mrivera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void				set_dimensions(t_tetrimino *tet)
{
	int		row;
	int		col;
	int		width;
	int		height;

	row = -1;
	width = 0;
	height = 0;
	while (++row < SIZE)
	{
		col = -1;
		while (++col < SIZE)
		{
			(tet->x[row] == tet->x[col]) ? width += 1 : width;
			(tet->y[row] == tet->y[col]) ? height += 1 : height;
		}
	}
	if ((width % SIZE) || (height % SIZE))
	{
		width += 4;
		height += 4;
	}
	tet->width = (width / 4);
	tet->height = (height / 4);
}

static char				***split_tetrimino(char **map)
{
	int		i;
	char	***fullmap;

	i = 0;
	if (!(fullmap = (char ***)malloc(sizeof(char **) * g_num_tetris + 1)))
		return (NULL);
	while (i < g_num_tetris)
	{
		fullmap[i] = ft_strsplit(map[i], '\n');
		i += 1;
	}
	return (fullmap);
}

static t_tetrimino		*new_tetriminos(int size)
{
	int			i;
	t_tetrimino	*new;
	t_tetrimino *head;

	if (!(new = (t_tetrimino *)malloc(sizeof(t_tetrimino) + 1)))
		return (NULL);
	head = new;
	i = 0;
	while (i++ < size)
	{
		if (!(new->next = (t_tetrimino *)malloc(sizeof(t_tetrimino) + 1)))
			return (NULL);
		new = new->next;
	}
	ft_memset(new, 0, (sizeof(t_tetrimino) + 1));
	return (head);
}

static t_tetrimino		*create_tetriminos(char ***fullmap, \
						t_tetrimino *tet, char letter, int *counter)
{
	t_tetrimino *head;

	head = tet;
	counter[0] = -1;
	while (++counter[0] < g_num_tetris)
	{
		counter[3] = 0;
		counter[1] = -1;
		while (++counter[1] < SIZE)
		{
			counter[2] = -1;
			while (++counter[2] < SIZE)
			{
				if (fullmap[counter[0]][counter[1]][counter[2]] == '#')
				{
					tet->x[counter[3]] = counter[1];
					tet->y[counter[3]++] = counter[2];
				}
			}
		}
		set_dimensions(tet);
		tet->letter = letter++;
		tet = tet->next;
	}
	return (head);
}

t_tetrimino				*tetrimino_map(char **map)
{
	int				*counter;
	char			***fullmap;
	t_tetrimino		*tetrimino;

	if (!(counter = (int *)malloc(sizeof(int) * 4)))
		return (NULL);
	if (!(fullmap = (char ***)malloc(sizeof(char **) * g_num_tetris + 1)))
		return (NULL);
	tetrimino = new_tetriminos(g_num_tetris);
	fullmap = split_tetrimino(map);
	return (create_tetriminos(fullmap, tetrimino, 'A', counter));
}
