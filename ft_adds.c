/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychufist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 18:22:04 by ychufist          #+#    #+#             */
/*   Updated: 2019/03/02 19:42:32 by ychufist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_links(int size, int *links)
{
	int j;

	j = -1;
	while (++j < size)
	{
		ft_bzero(links, sizeof(int*));
		free(links[j]);
	}
	free(links);
}

void	add_link(t_farm *farm, char *line, int i)
{
	int		j;
	t_room	dop_room;

	j = 0;
	if (farm->rooms[i].links_amount > 0)
	{
		dop_room.name = NULL;
		dop_room.flag = 0;
		dop_room.links_amount = farm->rooms[i].links_amount;
		dop_room.links = (int*)malloc(sizeof(int) * farm->rooms[i].links_amount);
		j = -1;
		ft_printf("start\n");
		while (++j < farm->rooms[i].links_amount)
			dop_room.links[j] = farm->rooms[i].links[j];
		free(farm->rooms[i].links);
		farm->rooms[i].links = (int*)malloc(sizeof(int) *
				(farm->rooms[i].links_amount + 1));
		j = -1;
		while (++j < farm->rooms[i].links_amount)
			farm->rooms[i].links[j] = dop_room.links[j];
		ft_printf("end\n");
		free(dop_room.links);
	}
	else
		farm->rooms[i].links = (int*)malloc(sizeof(int));
	farm->rooms[i].links[j] = is_room(*farm, line);
	farm->rooms[i].links_amount++;
}

int		find_link(t_farm *farm, char *line, int k)
{
	t_point	ij;
	char	*dop;
	char	*name;

	ij.y = -1;
	dop = ft_strchr(line, '-');
	name = ft_strsub(line, 0, dop - line);
	dop++;
	ij.x = is_room(*farm, name);
	if (ij.x > -1 && is_room(*farm, dop) > -1)
	{
		while (++ij.y < farm->rooms[ij.x].links_amount)
			if (farm->rooms[ij.x].links[ij.y] == is_room(*farm, dop))
				return (1);
		if ((ij.y == farm->rooms[ij.x].links_amount ||
					ft_intlength(farm->rooms[ij.x].links[ij.y]) == 0))
			add_link(farm, dop, ij.x);
		if (++k < 2)
		{
			dop = ft_strcat(ft_strcat(dop, "-"), name);
			find_link(farm, dop, k);
		}
		ft_strdel(&name);
		return (1);
	}
	return (0);
}

int		is_room(t_farm farm, char *name)
{
	int i;

	i = 0;
	if (name)
	{
		while (i < farm.room_amount)
		{
			if (ft_strcmp(farm.rooms[i].name, name) == 0)
				return (i);
			i++;
		}
	}
	return (-1);
}
