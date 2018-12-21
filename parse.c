/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychufist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:24:19 by ychufist          #+#    #+#             */
/*   Updated: 2018/12/18 14:25:28 by ychufist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_farm new_farm(int k, t_farm farm)
{
	t_farm dop_farm;
	int i;

	i = 0;
	ft_printf("%s\n", "hello2");
	dop_farm.rooms = (t_room*)malloc(sizeof(t_room) * k);
	while (i < k)
	{	
		dop_farm.rooms[i].room_name = farm.rooms[k].room_name;
		dop_farm.rooms[i].room_coord.x = farm.rooms[k].room_coord.x;
		dop_farm.rooms[i].room_coord.y = farm.rooms[k].room_coord.y;
	}
	ft_printf("%s\n", "hello3");
	return (dop_farm);
}

void get_info(int i, int *k, char *line, t_farm *farm)
{
	char *dop;
	t_farm dop_farm;

	// ft_printf("\n\n%s\n\n", line);

	farm->ants_amount = (i == 0) ? ft_atoi(line) : farm->ants_amount;
	ft_printf("%s\n", "hello1");
	
	if (i != 0 && ft_strchr(line, '-') == NULL && ft_strchr(line, '#') == NULL)
	{
		dop_farm = new_farm(*k, *farm);
		ft_printf("%s\n", "hello4");
		ft_bzero(farm, sizeof(t_farm));
		ft_printf("%s\n", "hello5");
		*farm = new_farm(*k, dop_farm);
		ft_printf("%s\n", "hello6");
		dop = ft_strchr(line, ' ');
		farm->rooms[*k].room_name = ft_strsub(line, 0, dop - line);
		ft_printf("NAME %s\n", farm->rooms[*k].room_name);
		farm->rooms[*k].room_coord.x = ft_atoi(dop++);
		farm->rooms[*k].room_coord.y = ft_atoi(ft_strchr(dop, ' '));
		ft_printf("room name %s ", farm->rooms[*k].room_name);
		ft_printf("room coord x %d ", farm->rooms[*k].room_coord.x);
		ft_printf("room coord y %d\n", farm->rooms[*k].room_coord.y);
		(*k)++;
	}
}

int main()
{
	int i;
	int k;
	int fd;
	char *line;
	t_farm farm;

	i = 0;
	k = 0;
	fd = open("test", O_RDONLY);
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		ft_printf("gnl : %s\n", line);
		ft_printf("%s\n", "hello");
		if (ft_strcmp(line, "##start") == 0 && ft_strcmp(line, "##start") == 0)
			continue;
		else 
			get_info(i, &k, line, &farm);
		if (i == 0)
			ft_printf("farm.ants_amount %d\n", farm.ants_amount);
		// if (k > 0)
		// {
		// 	ft_printf("here %s ", farm.rooms[k].room_name);
		// 	ft_printf("%d ", farm.rooms[k].room_coord.x);
		// 	ft_printf("%d\n", farm.rooms[k].room_coord.y);
		// }
		i = (ft_strcmp(line, "##start") == 0) ? 1 : i;
		i = (ft_strcmp(line, "##end") == 0) ? 2 : i;
		i = (i == 0) ? 3 : i;
		ft_strdel(&line);
		//k++;
	}
	ft_strdel(&line);
	system("leaks lem-in");
	return (0);
}
