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

int is_answer(t_farm farm)
{
    int counter;
    int j;
    t_list_room *room_list;
    t_list_room *dop2;
    t_list_room *dop;

    counter = 1;
    room_list = ft_list_room_new(farm.rooms[farm.start_room_id]);
    dop = room_list;
    dop2 = room_list;
    while (dop2)
    {
        if (is_room(farm, dop2->name) == farm.end_room_id)
            return (1);
        j = -1;
        while (++j < dop2->links_amount)
        {
            if (!ft_list_room_find(dop, dop2->links[j]))
            {
                room_list->next = ft_list_room_new(farm.rooms[is_room(farm, dop2->links[j])]);
                room_list = room_list->next;
            }
        }
        dop2 = dop2->next;
        counter++;
    }
    ft_printf("NO WAY TO END :(\n");
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
        if (!find_link(farm, line, 0))
        {
            ft_printf("\n\nNO SUCH ROOM OR LINK. ERROR\n");
            return (0);
        }
    }
    return (1);
}

void init(t_farm *farm)
{
    farm->flag = 0;
    farm->room_amount = 0;
    farm->ways_amount = 0;
    farm->rooms = (t_room*) malloc(sizeof(t_room) * (farm->room_amount + 1));
}

int main(void)
{
	int i;
	int fd;
	char *line;
	t_farm farm;
    t_ant *ants;

	i = 0;
	fd = open("/Users/ychufist/lem-in/test", O_RDONLY);//"/home/echufy/lem-in/test", O_RDONLY);
	line = NULL;
    init(&farm);
	while (get_next_line(fd, &line) > 0)
	{
		ft_printf("%s\n", line);
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
	if (is_answer(farm))
    {
        ft_printf("\n");
        farm.ways = (t_list_room**) malloc(sizeof(t_list_room*));
        find_ways(&farm);
	    ants = create_ants(farm.ants_amount);
        move_ants(farm, ants);
    }
	return (0);
}