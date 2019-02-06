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
        {
//            print_list(dop);
            return (1);
        }
        j = -1;
        while (++j < dop2->links_amount)
        {
            if (!ft_list_room_find(dop, dop2->links[j]))
            {
                room_list->next = ft_list_room_new(farm.rooms[is_room(farm, dop2->links[j])]);
                if (is_room(farm, dop2->links[j]) != farm.end_room_id)
                    farm.rooms[is_room(farm, dop2->links[j])].level = counter;
//                ft_printf("name - %s, level - %d\n", farm.rooms[is_room(farm, dop2->links[j])].name,
//                farm.rooms[is_room(farm, dop2->links[j])].flag);
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



void get_way(t_farm *farm, t_list_room *way)
{
    int i;
    t_list_room rm;
    t_list_room *dop;
    t_list_room *dop2;

    i = 0;
    dop = way;
    dop2 = way;
    while (way->next)
        way = way->next;
    ft_printf("\nway :%s\n", way->name);
    ft_printf("dop :%s\n", dop->name);
    rm = *way;
    while (ft_strcmp(rm.name, farm->rooms[farm->end_room_id].name) != 0)
    {
        rm = find_parent(rm.name, dop);
        ft_printf("parent : %s\n", rm.parent);
        farm->rooms[is_room(*farm, rm.parent)].flag = 1;
        rm = find_parent(rm.parent, dop);
    }
}

t_list_room *find_ways(t_farm farm)
{
    int i;
    int j;
    t_list_room *way;
    t_list_room *dop2;
    t_list_room *dop;

    way = ft_list_room_new(farm.rooms[farm.end_room_id]);
    dop = way;
    dop2 = way;
    while (dop2)
    {
//        ft_printf("DOP2: %s\n", farm.rooms[is_room(farm, dop2->name)].name);
        if (is_room(farm, dop2->name) == farm.start_room_id)
        {
            ft_printf("end: ");
            print_list(dop);
            get_way(&farm, dop);
            ft_printf("\n");
            return (way);
        }
        j = -1;
        while (++j < dop2->links_amount)
        {
            if (farm.rooms[is_room(farm, dop2->links[j])].flag != 1)
            {
                if (is_room(farm, way->name) != farm.end_room_id)
                    farm.rooms[is_room(farm, way->name)].flag = 1;// просмотрена
                if (is_room(farm, dop2->links[j]) != farm.end_room_id)//надо сделать проверку на предыдущую связь
                {
                way->next = ft_list_room_new(farm.rooms[is_room(farm, dop2->links[j])]);
//                    ft_printf("next room : %s\n", farm.rooms[is_room(farm, dop2->links[j])].name);
                way = way->next;
                way->parent = farm.rooms[is_room(farm, dop2->name)].name;
//                ft_printf("parent : %s\n", farm.rooms[is_room(farm, dop2->name)].name);
                }
            }
        }
        dop2 = dop2->next;
    }
    ft_printf("stranno\n");
    print_list(dop);
    return (NULL);
}



//t_list_room **no_traffic_jams(t_farm farm)
//{
//    int i;
//    int j;
//    int k;
//    t_list_room **way;
//    t_list_room *dop;
//    t_list_room *dop2;
//
//    i = 0;
//    j = 0;
//    k = 0;
//    // ПЛОХО ВЫДЕЛЕНА ПАМЯТЬ!!!!!!!
//    way = (t_list_room**)malloc(sizeof(t_list_room*) * farm.room_amount);
//
//    while (i < farm.rooms[farm.end_room_id].links_amount)
//    {
//        way[i] = ft_list_room_new(farm.rooms[farm.end_room_id]);
//        dop = way[i];
//        while (is_room(farm, way[i]->name) != farm.start_room_id)// while not start
//        {
//            ft_printf("flag: %d \n", farm.rooms[is_room(farm, way[i]->name)].flag);
//            ft_printf("way[i]->name : %s\n", way[i]->name);
//            way[i]->level = ft_list_size(dop);
//            ft_printf("hello\n");
//            if (farm.rooms[is_room(farm, way[i]->links[j])].flag != 1)
//            {
//                way[i]->next = ft_list_room_new(farm.rooms[is_room(farm, way[i]->links[j])]);
//                ft_printf("hello1\n");
//                if (is_room(farm, way[i]->name) != farm.end_room_id)
//                        farm.rooms[is_room(farm, way[i]->name)].flag = 1;
//                ft_printf("flag: %d \n", farm.rooms[is_room(farm, way[i]->name)].flag);
//                ft_printf("FLAG : %s\n", way[i]->name);
//                way[i] = way[i]->next;
//                ft_printf("( if1 ) way[i]->name : %s\n", way[i]->name);
//                ft_printf("( if1 )  flag: %d \n", farm.rooms[is_room(farm, way[i]->name)].flag);
//            }
//            else
//                {
//                ft_printf("ELSE\n\n");
//                ft_printf("j : %d, link am %d\n", j, way[i]->links_amount);
//                while (same_name(dop, farm.rooms[is_room(farm, way[i]->links[k])].name) != 1
//                && k < way[i]->links_amount && farm.rooms[is_room(farm, way[i]->links[k])].flag != 1)
//                    k++;
//                if (k == 0)
//                {
//                    ft_printf("end:");
//                    print_list(dop);
//                    ft_printf("\n");
//                    return (way);
//                }
//                ft_printf("k: %d\n", k);
//                j = k;
//                }
//        }
//        ft_printf("\n\nhere\n\n");
//        print_list(dop);
//        ft_printf("len : %d\n\n", ft_list_size(dop));
//        i++;
//        j++;
//    }
//    return (NULL);
//}

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

int main(void) {
	int i;
	int fd;
	char *line;
	t_farm farm;
	t_list_room *way;

	i = 0;
	fd = open("/Users/ychufist/lem-in/test", O_RDONLY);//"/home/echufy/lem-in/test", O_RDONLY);//
	line = NULL;
	farm.flag = 0;
	farm.room_amount = 0;
	farm.rooms = (t_room *) malloc(sizeof(t_room) * (farm.room_amount + 1));
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

	i = 0;
	ft_printf("room amount %d\n", farm.room_amount);
    ft_printf("start %s\n", farm.rooms[farm.start_room_id].name);
    ft_printf("end %s\n", farm.rooms[farm.end_room_id].name);
    while (i < farm.room_amount)
    {
	//write(1, "\e[34m", 5);
	ft_printf("%d) ", i);
	ft_printf("room name %s ", farm.rooms[i].name);
	ft_printf("room coord x %d ", farm.rooms[i].coord.x);
	ft_printf("room coord y %d ", farm.rooms[i].coord.y);
	ft_printf("links amount %d\n", farm.rooms[i].links_amount);
	i++;
    }
	//write(1, "\e[0m", 4);
	i = 0;
	while (i < farm.rooms[299].links_amount) {
		ft_printf("%s-%s\n", farm.rooms[299].name, farm.rooms[299].links[i]);
		i++;
	}
	if (is_answer(farm))
    {
	    way = find_ways(farm);
        //way =
        //print_list(way);
    }
	ft_printf("\n\nokk");
	return (0);
}