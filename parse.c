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
        if (dop2->id == farm.end_room_id)
            return (1);
        j = -1;
        while (++j < dop2->links_amount)
        {
            if (!ft_list_room_find(dop, dop2->links[j]))
            {
                room_list->next = ft_list_room_new(farm.rooms[dop2->links[j]]);
                room_list = room_list->next;
            }
        }
        dop2 = dop2->next;
        counter++;
    }
    write_error("NO WAY TO END :(");
    return (0);
}

void make_room(t_farm *farm)
{
    int i;
//    t_list_room *dop;
    t_list_room *dop2;

    i = 0;
    farm->rooms = (t_room*)malloc(sizeof(t_room) * farm->room_amount);
    dop2 = farm->dop;
    while (dop2->next)
    {
        farm->rooms[i].id = dop2->id;
        farm->rooms[i].name = ft_strdup(dop2->name);
        farm->rooms[i].coord.x = dop2->coord.x;
        farm->rooms[i].coord.y = dop2->coord.y;
        farm->rooms[i].links_amount = dop2->links_amount;
        dop2 = dop2->next;
//        free((farm->dop)->name);
//        free(farm->dop);
//        farm->dop = dop;
        i++;
    }
}


int get_info(t_farm *farm, char *line, int *i)
{
    char *dop;
    char *dop2;

    if ((*i)++ == 0)
        farm->ants_amount = ft_atoi(line);
    else if (ft_strchr(line, '-') == NULL)
    {
        dop = ft_strchr(line, ' ');
        dop2 = ft_strsub(line, 0, dop - line);
        if (!is_valid_name(*farm, dop2))
            return (0);
        ft_strdel(&dop2);
        farm->init->id = farm->room_amount;
        farm->init->name = ft_strsub(line, 0, dop - line);
        farm->init->coord.x = ft_atoi(dop++);
        farm->init->coord.y = ft_atoi(ft_strchr(dop, ' '));
        if (!is_coord(*farm, farm->init))
            return (0);
        farm->init->links_amount = 0;
        farm->init->next = (t_list_room*)malloc(sizeof(t_list_room));
        farm->init = farm->init->next;
        farm->init->next = NULL;
        farm->room_amount++;
    }
    return (1);
}

void init(t_farm *farm)
{
    int		i;

    i = 0;
    farm->colors = (char **)ft_memalloc(sizeof(char *) * 5);
    while (i < 5)
        farm->colors[i++] = (char *)ft_memalloc(sizeof(char) * 8);
    farm->colors[0] = ft_strcpy(farm->colors[0], "\e[91m");
    farm->colors[1] = ft_strcpy(farm->colors[1], "\e[92m");
    farm->colors[2] = ft_strcpy(farm->colors[2], "\e[93m");
    farm->colors[3] = ft_strcpy(farm->colors[3], "\e[94m");
    farm->colors[4] = ft_strcpy(farm->colors[4], "\e[95m");
    farm->flag = 0;
    farm->room_amount = 0;
    farm->ways_amount = 0;
    farm->start_room_id = -1;
    farm->end_room_id = -1;
    farm->init = (t_list_room*)malloc(sizeof(t_list_room));
    farm->init->next = NULL;
    farm->dop = farm->init;
    farm->col = 0;
}

void free_farm(t_farm *farm)
{
    int i;

    i = -1;
//    while (++i < farm->room_amount)
//    {
//        free_links(farm->rooms[i].links_amount, farm->rooms[i].links);
//        ft_strdel(&farm->rooms[i].name);
//    }
//    free(farm->rooms);
    while (++i < farm->ways_amount)
    {
        ft_lstrm_del(&farm->ways[i]);
    }

}

void bonuses(t_farm farm, const char *b1, const char *b2)
{
    if (b1[0] == '-' && b1[1] == 'c')//to turn on colors
        ft_printf("colors\n");
    if (b2[0] == '-' && b2[1] == 'w')//to turn on colors
    {
        print_ways(farm);
    }

}

int main(void)
{
    int i;
    int fd;
    char *line;
    t_farm farm;
    t_ant *ants;

    i = 0;
    fd = open("/Users/ychufist/lem-in/test", O_RDONLY);
    line = NULL;
    init(&farm);
    while (get_next_line(fd, &line) > 0)
    {
        if (ft_strlen(line) != 0) {
            write(1, line, ft_strlen(line));
            write(1, "\n", 1);
            if (line[0] != '#' && ft_strchr(line, '-') == NULL)
            {
                if (!get_info(&farm, line, &i))
                    return (0);
            }
            else if (line[0] != '#' && ft_strchr(line, '-') != NULL)
            {
                if (farm.flag == 0)
                {
                    make_room(&farm);// сделали комнаты
                    farm.flag = 1;
                }
                if (!find_link(&farm, line, 0))
                {
                    write_error("NO SUCH ROOM OR LINK. ERROR");
                    return (0);
                }
            } else if (ft_strstr(line, "start") != NULL)
                farm.start_room_id = farm.room_amount;
            else if (ft_strstr(line, "end") != NULL)
                farm.end_room_id = farm.room_amount;
            ft_strdel(&line);
        }
    }
    if (is_valid_map(farm) && is_answer(farm))
    {
        ft_printf("\n");
        farm.ways = (t_list_room**) malloc(sizeof(t_list_room*));
        find_ways(&farm, 0);
//        bonuses(farm, av[1], av[2]);
        ft_printf("kolvo ways %d\n", farm.ways_amount);
        ants = create_ants(farm.ants_amount);
        move_ants(farm, ants);
    }
//    system("leaks lem-in");
    return (0);
}