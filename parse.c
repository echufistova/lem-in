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
//    print_list(dop);
    ft_printf("NO WAY TO END :(\n");
    return (0);
}

void bzero_ways(t_farm *farm)
{
    int i;

    i = 0;
    while (i < farm->room_amount)
    {
        if (farm->rooms[i].flag != 2)
            farm->rooms[i].flag = 0;
//        ft_printf("room -  \"%s\", flag - %d \n", farm->rooms[i].name, farm->rooms[i].flag);
        i++;
    }
}

void get_way(t_farm *farm, t_list_room *way)
{
    int i;
    t_list_room *rm;
    t_list_room *dop;

    i = 0;

    bzero_ways(farm);
    while (way->next)
        way = way->next;
    farm->ways[farm->ways_amount] = ft_list_room_new(farm->rooms[farm->start_room_id]);
    dop = farm->ways[farm->ways_amount];
    ft_printf("\n\nway : %s\n", way->name);
    ft_printf("dop : %s\n", dop->name);
    rm = way->prev;
    while (ft_strcmp(rm->name, farm->rooms[farm->end_room_id].name) != 0)
    {
        farm->ways[farm->ways_amount]->next = ft_list_room_new(farm->rooms[is_room(*farm, rm->name)]);
        farm->ways[farm->ways_amount] = farm->ways[farm->ways_amount]->next;
        ft_printf("parent : %s\n", rm->name);
        farm->rooms[is_room(*farm, rm->name)].flag = 2;
        rm = rm->prev;
    }
    farm->ways[farm->ways_amount]->next = ft_list_room_new(farm->rooms[is_room(*farm, rm->name)]);
    farm->ways[farm->ways_amount] = dop;
    ft_printf("\n");
    farm->ways[farm->ways_amount]->size = ft_list_size(farm->ways[farm->ways_amount]) - 1;
    print_list(farm->ways[farm->ways_amount]);
    farm->ways_amount++;
    ft_printf("\n");
    find_ways(farm);
}

void print_farm(t_farm farm)
{
    int i = 0;

    ft_printf("print farm \n");
    while (i < farm.ways_amount)
    {
        ft_printf("list size: %d, ", farm.ways[i]->size);
        print_list(farm.ways[i]);
        ft_printf("\n");
        i++;
    }
}

t_list_room *find_ways(t_farm *farm)
{
    int i;
    int j;
    t_list_room *way;
    t_list_room *dop2;
    t_list_room *dop;

    way = ft_list_room_new(farm->rooms[farm->end_room_id]);
    dop = way;
    dop2 = way;
    while (dop2)
    {
        j = -1;
        while (++j < dop2->links_amount)
        {
//            ft_printf("flag - %d u room - %s\n", farm.rooms[is_room(farm, dop2->links[j])].flag, farm.rooms[is_room(farm, dop2->links[j])].name);
            if (farm->rooms[is_room(*farm, dop2->links[j])].flag != 1 &&
                    farm->rooms[is_room(*farm, dop2->links[j])].flag != 2)
            {
                if (is_room(*farm, way->name) != farm->end_room_id)
                    farm->rooms[is_room(*farm, way->name)].flag = 1;// просмотрена
                if (is_room(*farm, dop2->links[j]) != farm->end_room_id)//надо сделать проверку на предыдущую связь
                {
                    way->next = ft_list_room_new(farm->rooms[is_room(*farm, dop2->links[j])]);
                    ft_printf("room : %s, ", farm->rooms[is_room(*farm, dop2->links[j])].name);
                    way = way->next;
                    way->prev = dop2;
                    ft_printf("dop2: %s\n", dop2->name);
                    ft_printf("parent : %s\n", farm->rooms[is_room(*farm, dop2->name)].name);
                    if (is_room(*farm, way->name) == farm->start_room_id)
                    {
                        ft_printf("end: ");
                        print_list(dop);
                        ft_printf("    ways am: %d\n", farm->ways_amount);
                        get_way(farm, dop);
                        ft_printf("\n");
                        return (way);
                    }
                }
            }
        }
        dop2 = dop2->next;
    }
    ft_printf("stranno\n");
    print_list(dop);
    ft_printf("\n\n");
    bzero_ways(farm);
    print_farm(*farm);
    return (NULL);
}

int find_link(t_farm *farm, char *line, int k)
{
    t_point ij;
    char *dop;
    char *name;

    ij.y = -1;
    dop = ft_strchr(line, '-');
    name = ft_strsub(line, 0, dop - line);
    dop++;
    ij.x = is_room(*farm, name);
    if (ij.x > -1 && is_room(*farm, dop) > -1)
    {
        while (++ij.y < farm->rooms[ij.x].links_amount)
            if (ft_strcmp(farm->rooms[ij.x].links[ij.y], dop) == 0)
                return (1);
        if ((ij.y == farm->rooms[ij.x].links_amount ||
            ft_strlen(farm->rooms[ij.x].links[ij.y]) == 0))
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

int allAntsGotEnd(t_ant * ants, int ants_amount) {
    int i;

    i = -1;
    while(++i < ants_amount)
    {
        if(ants[i].currnet_index <= ants[i].way_size ) {
            return 0;
        }
    }
    return 1;
}

void print_ants_movings(t_ant * ants, int ants_amount) {
    int  i;
    int  j;
    t_list_room     *tmp_way;

    i = -1;
    while(++i < ants_amount)
    {
        if(ants[i].currnet_index > ants[i].way_size)
            continue;
        tmp_way = ants[i].way;
        j = -1;
        while(++j < ants[i].currnet_index)
        {
            tmp_way = tmp_way->next;
        }
        if(ants[i].currnet_index != 0) ft_printf("L%d-%s ", ants[i].number, tmp_way->name);
    }
    ft_printf("\n");
}

void move_ants2(t_farm farm, t_ant *ants)
{
    int i;
    int j;
    int counter;
    int check_exp;
    int current_ants_number;

    counter = 0;
    current_ants_number = 1;
    while (current_ants_number <= farm.ants_amount || !allAntsGotEnd(ants, farm.ants_amount))
    {
        if(current_ants_number <= farm.ants_amount)
        {
            i = -1;
            while (++i < farm.ways_amount)
            {
                check_exp = 0;
                j = -1;
                while (i != 0 && ++j < i)
                    check_exp += farm.ways[i]->size - farm.ways[j]->size;
                if (farm.ants_amount - current_ants_number >= check_exp)
                {
                    ants[current_ants_number - 1].way = farm.ways[i];
                    ants[current_ants_number - 1].way_size = ft_list_size(farm.ways[i]) - 1;
                    ants[current_ants_number - 1].currnet_index++;
                    current_ants_number++;
                }
            }
        }
        print_ants_movings(ants, current_ants_number - 1);
        counter++;
        j = -1;
        while(++j < current_ants_number - 1)
            ants[j].currnet_index++;
    }
    ft_printf("\nlines - %d\n", counter);
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
	fd = open("/home/echufy/lem-in/test", O_RDONLY);//"/Users/ychufist/lem-in/test", O_RDONLY);//
	line = NULL;
    init(&farm);
	while (get_next_line(fd, &line) > 0)
	{
		ft_printf("gnl : %s\n", line);
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
        farm.ways = (t_list_room**) malloc(sizeof(t_list_room*));
        find_ways(&farm);
	    ants = create_ants(farm.ants_amount);
        move_ants2(farm, ants);
    }
	return (0);
}