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

<<<<<<< HEAD
int is_valid_name(const char *name)
{
    if (name[0] == 'L' || name[0] == '#')
    {
        ft_printf("NAME ERROR\n");
        return (0);
    }
    return (1);
}

int is_room(t_farm farm, char *name)
{
    int i;

    i = 0;
    while (i < farm.room_amount)
    {
        if (ft_strcmp(farm.rooms[i].name, name) == 0)
            return (i);
        i++;
    }
    return (-1);
}

int find_link(t_farm *farm, char *line)
{
    int i;
    int j;
    char *dop;
    char *name;

    j = 0;
    dop = ft_strchr(line, '-');
    name = ft_strsub(line, 0, dop - line);
    dop++;
    i = is_room(*farm, name);
    if (i > -1 && is_room(*farm, dop) > -1)
    {
        while (j < farm->rooms[i].links_amount - 1)
        {
            if (ft_strcmp(farm->rooms[i].links[j], dop) == 0)
            {
                farm->rooms[is_room(*farm, dop)].links_amount++;
                break;
            }
            j++;
        }
        if (j == farm->rooms[i].links_amount || ft_strlen(farm->rooms[i].links[j]) == 0)
            add_link(farm, dop, i);
        return (1);
    }
    return (0);
}

int get_info(t_farm *farm, char *line, int *i)
{
    char *dop;

    if ((*i)++ == 0)
        farm->ants_amount = ft_atoi(line);
    else if (ft_strchr(line, '-') == NULL && farm->flag == 0)
    {
        add_room(farm);
        dop = ft_strchr(line, ' ');
        farm->rooms[farm->room_amount].name = ft_strsub(line, 0, dop - line);
        if (!is_valid_name(farm->rooms[farm->room_amount].name))
            return (0);
        farm->rooms[farm->room_amount].coord.x = ft_atoi(dop++);
        farm->rooms[farm->room_amount].coord.y = ft_atoi(ft_strchr(dop, ' '));
        farm->rooms[farm->room_amount++].links_amount = 0;
    }
    else if (ft_strchr(line, '-') != NULL && farm->flag == 0)
    {
        if (!find_link(farm, line))
        {
            ft_printf("\n\nNO SUCH ROOM OR LINK. ERROR\n");
            return (0);
        }
    }
    return (1);
}

int main(void)
{
    int i;
    int fd;
    char *line;
    t_farm farm;

    i = 0;
    fd = open("/Users/ychufist/lem-in/lem-in/test", O_RDONLY);
    line = NULL;
    farm.flag = 0;
    farm.room_amount = 0;
    farm.rooms = (t_room*)malloc(sizeof(t_room) * (farm.room_amount + 1));
    while (get_next_line(fd, &line) > 0)
    {
//		ft_printf("gnl : %s\n", line);
        if (line[0] != '#')
        {
            if (!get_info(&farm, line, &i))
                return (0);
        }
        else if (ft_strstr(line, "start") != NULL)
            farm.start_room_id = farm.room_amount;
        else if (ft_strstr(line, "end") != NULL)
            farm.end_room_id = farm.room_amount;
        ft_strdel(&line);
    }
    i = farm.end_room_id;
    ft_printf("room amount %d\n", farm.room_amount);
//    while (i < farm.room_amount)
//    {
        //write(1, "\e[34m", 5);
        ft_printf("%d) ", i);
        ft_printf("room name %s ", farm.rooms[i].name);
        ft_printf("room coord x %d ", farm.rooms[i].coord.x);
        ft_printf("room coord y %d ", farm.rooms[i].coord.y);
        ft_printf("links amount %d\n", farm.rooms[i].links_amount);
        i++;
//    }
    //write(1, "\e[0m", 4);
    i = 0;
    while (i < farm.rooms[farm.end_room_id].links_amount)
    {
        ft_printf("%s-%s\n", farm.rooms[farm.end_room_id].name, farm.rooms[farm.end_room_id].links[i]);
        i++;
    }
    ft_printf("\n\nokk");
    return (0);
=======
void add_link(t_farm *farm, char *line, int i)
{
	int j;
	t_room dop_room;

	j = 0;
//	ft_printf("hello7\n");
	dop_room.links = (char**)malloc(sizeof(char*) * (farm->rooms[i].links_amount + 1));
	while (j < farm->rooms[i].links_amount)
	{
		dop_room.links[j] = farm->rooms[i].links[j];
		j++;
	}
	j = 0;
	while (j < farm->rooms[i].links_amount)
		ft_bzero(farm->rooms[i].links[j++], sizeof(char*));
	farm->rooms[i].links = (char**)malloc(sizeof(char*) * (farm->rooms[i].links_amount + 1));
	while (j < farm->rooms[i].links_amount)
	{
		farm->rooms[i].links[j] = dop_room.links[j];
		j++;
	}
	farm->rooms[i].links[j] = line;
	j = 0;
	while (j < dop_room.links_amount)
		ft_bzero(dop_room.links[j++], sizeof(char*));
	farm->rooms[i].links_amount++;
}

void find_link(t_farm *farm, char *line)
{
	int i;
	int j;
	char *dop;
	char *name;

	i = 0;
	j = 0;
	dop = ft_strchr(line, '-');
	ft_printf("hello5\n");
	name = ft_strsub(line, 0, dop - line);
	dop++;
	while (i < farm->room_amount && ft_strcmp(farm->rooms[i].name, name) != 0)
		i++;
	if (ft_strcmp(farm->rooms[i].name, name) == 0)
	{
		while (j < farm->rooms[i].links_amount && ft_strlen(farm->rooms[i].links[j]) != 0)
		{
			if (ft_strcmp(farm->rooms[i].links[j], dop) == 0)
				break;
			j++;
		}
		if (j == farm->rooms[i].links_amount || ft_strlen(farm->rooms[i].links[j]) == 0)
		{
			ft_printf("hello6\n");
			add_link(farm, dop, i);
		}
	}
}

void add_room(t_farm *farm)
{
	t_room *dop_rooms;
	int i;

	ft_printf("hello1\n");
	i = 0;
	if (farm->room_amount > 0) {
		dop_rooms = (t_room*)malloc(sizeof(t_room) * (farm->room_amount + 1));
		while (i < farm->room_amount) {
			dop_rooms[i].name = farm->rooms[i].name;
			dop_rooms[i].coord.x = farm->rooms[i].coord.x;
			dop_rooms[i].coord.y = farm->rooms[i].coord.y;
			i++;
		}
		ft_printf("hello2\n");
		i = 0;
		ft_bzero(farm->rooms, sizeof(t_room *));
		farm->rooms = (t_room*)malloc(sizeof(t_room) * (farm->room_amount + 1));
		while (i < farm->room_amount)
		{
			farm->rooms[i].name = dop_rooms[i].name;
			farm->rooms[i].coord.x = dop_rooms[i].coord.x;
			farm->rooms[i].coord.y = dop_rooms[i].coord.y;
			i++;
		}
	}
	farm->rooms[i].name = NULL;
	farm->rooms[i].coord.x = 0;
	farm->rooms[i].coord.y = 0;
}

void get_info(t_farm *farm, char *line, int *i)
{
	char *dop;

	ft_printf("hello\n");
	if ((*i)++ == 0)
		farm->ants_amount = ft_atoi(line);
	else if (ft_strchr(line, '-') == NULL)
	{
		add_room(farm);
		dop = ft_strchr(line, ' ');
		farm->rooms[farm->room_amount].name = ft_strsub(line, 0, dop - line);
		farm->rooms[farm->room_amount].coord.x = ft_atoi(dop++);
		farm->rooms[farm->room_amount].coord.y = ft_atoi(ft_strchr(dop, ' '));
		farm->rooms[farm->room_amount].links_amount = 0;
		farm->room_amount++;
	}
	else if (ft_strchr(line, '-') != NULL)
	{
		ft_printf("hello4\n");
		find_link(farm, line);
	}
}

int main(int ac, char **av)
{
	int i;
	int fd;
	char *line;
	t_farm farm;

	i = 0;
	fd = open("/Users/ychufist/lem-in/test", O_RDONLY);
	line = NULL;
	//init(&farm);
	farm.room_amount = 0;
	farm.rooms = (t_room*)malloc(sizeof(t_room) * (farm.room_amount + 1));
	while (get_next_line(fd, &line) > 0)
	{
//		ft_printf("gnl : %s\n", line);
		if (ft_strchr(line, '#') == NULL)
			get_info(&farm, line, &i);
		ft_strdel(&line);
	}
	i = 0;
	while (i < farm.room_amount)
	{
		ft_printf("room name %s ", farm.rooms[i].name);
		ft_printf("room coord x %d ", farm.rooms[i].coord.x);
		ft_printf("room coord y %d ", farm.rooms[i].coord.y);
		ft_printf("links amount %d\n", farm.rooms[i].links_amount);
		i++;
	}
	i = 0;
	while (i < farm.rooms[0].links_amount)
	{
		ft_printf("%s-%s\n", farm.rooms[0].name, farm.rooms[0].links[i]);
		i++;
	}
	return (0);
>>>>>>> 034f97cf9a848ec5d8f411045e977e846311b432
}