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

void    free_list(t_list_room **dop)
{
    t_list_room *tmp;
    while (*dop)
    {
        tmp = (*dop)->next;
        free((*dop)->links);
        free(*dop);
        *dop = tmp;
    }
}

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

//int is_answer(t_farm farm)
//{
//    int j;
//    t_list_room *room_list;
//    t_list_room *dop2;
//    t_list_room *dop;
//
//    room_list = ft_list_room_new(farm.rooms[farm.start_room_id]);
//    dop = room_list;
//    dop2 = room_list;
//    while (dop2)
//    {
//        if (dop2->id == farm.end_room_id)
//        {
//            free_list(&dop);
//            return (1);
//        }
//        j = -1;
//        while (++j < dop2->links_amount)
//        {
//            if (!ft_list_room_find(dop, dop2->links[j]))
//            {
//                room_list->next = ft_list_room_new(farm.rooms[dop2->links[j]]);
//                room_list = room_list->next;
//            }
//        }
//        dop2 = dop2->next;
//    }
//    free_list(&dop);
//    write_error("NO WAY TO END :(");
//    return (0);
//}

void make_room(t_farm *farm)
{
    int i;
//    t_list_room *dop;
    t_list_room *dop2;

    i = 0;
    farm->rooms = (t_room*)malloc(sizeof(t_room) * farm->room_amount);
    dop2 = farm->dop;
    while (dop2)
    {
        farm->rooms[i].id = dop2->id;
        farm->rooms[i].name = ft_strdup(dop2->name);
        farm->rooms[i].coord.x = dop2->coord.x;
        farm->rooms[i].coord.y = dop2->coord.y;
        farm->rooms[i].links_amount = dop2->links_amount;
        farm->rooms[i].links = NULL;
        dop2 = dop2->next;
//        free((farm->dop)->name);
//        free(farm->dop);
//        farm->dop = dop;
        i++;
    }
}

int get_cood(t_farm *farm, char **line, int n)
{
    int i;
    char *dopline;

    i = 0;
    dopline = *line;
    while ((*line)[i] == ' ')
        i++;
    while ((*line)[i] != ' ' && (*line)[i] != '\0')
    {
        if (!ft_isdigit((*line)[i++]))
        {
            write_error("INCORRECT INPUT. ERROR");
            return (0);
        }
    }
    (*line)++;
    if (n == 1)
        farm->init->coord.x = ft_atoi(dopline);
    else if (n == 2)
        farm->init->coord.y = ft_atoi(dopline);
    return (1);
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
        {
            free(dop2);
            return (0);
        }
        free(dop2);
        farm->init->id = farm->room_amount;
        farm->init->name = ft_strsub(line, 0, dop - line);
        if (get_cood(farm, &dop, 1) == 0)
            return (0);
        dop = ft_strchr(dop, ' ');
        if (get_cood(farm, &dop, 2) == 0)
            return (0);
        if (!is_coord(*farm, farm->init))
            return (0);
        farm->init->links_amount = 0;
        farm->init->next = (t_list_room*)malloc(sizeof(t_list_room));
        ft_bzero(farm->init->next, sizeof(t_list_room));
        farm->init = farm->init->next;
        farm->init->next = NULL;
        farm->room_amount++;
    }
    return (1);
}

void init(t_farm *farm, char **av)
{
    int i;

    i = 0;
    if ((av[1] && av[1][0] == '-' && av[1][1] == 'c') || (av[2] && av[2][0] ==
    '-' && av[2][1] == 'c') || (av[3] && av[3][0] == '-' && av[3][1] == 'c'))
    {
        farm->colors = (char **) ft_memalloc(sizeof(char *) * 5);
        while (i < 5)
            farm->colors[i++] = (char *) ft_memalloc(sizeof(char) * 8);
        farm->colors[0] = ft_strcpy(farm->colors[0], "\e[91m");
        farm->colors[1] = ft_strcpy(farm->colors[1], "\e[92m");
        farm->colors[2] = ft_strcpy(farm->colors[2], "\e[93m");
        farm->colors[3] = ft_strcpy(farm->colors[3], "\e[94m");
        farm->colors[4] = ft_strcpy(farm->colors[4], "\e[95m");
        farm->col = 0;
    }
    else
        farm->col = -1;
    farm->flag = 0;
    farm->room_amount = 0;
    farm->ways_amount = 0;
    farm->start_room_id = -1;
    farm->end_room_id = -1;
    farm->init = (t_list_room*)malloc(sizeof(t_list_room));
    farm->init->next = NULL;
    farm->init->links_amount = 1;
    farm->dop = farm->init;
}

void free_farm(t_farm *farm)
{
    int i;

    i = -1;
    if (farm->col != -1)
    {
        while (++i < 5)
        {
            ft_bzero(farm->colors[i], sizeof(char *));
        }
        free(farm->colors);
    }
//    if (farm->room_amount > 0)
//    {
//        i = -1;
//        while (++i < farm->room_amount)
//        {
//            free(farm->rooms[i].links);
//            free(farm->rooms[i].name);
//        }
//        free(farm->rooms);
//    }
}

void work(t_farm *farm, char **av)
{
    t_ant *ants;

    if (is_valid_map(*farm) && is_answer(*farm))
    {
        ft_printf("\n");
        farm->ways = (t_list_room**) malloc(sizeof(t_list_room*));
        find_ways(farm, 0);
        bonus_ways(*farm, av);
        ants = create_ants(farm->ants_amount);
        farm->lines = move_ants(*farm, ants);
        free(ants);
        bonus_lines(*farm, av);
    }
    free_farm(farm);
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
    init(&farm, av);
    while (get_next_line(fd, &line) > 0)
    {
        if (ft_strlen(line) != 0)
        {
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
                    make_room(&farm);
                    farm.flag = 1;
                }
                if (!find_link(&farm, line, 0))
                {
                    write_error("NO SUCH ROOM OR LINK. ERROR");
                    return (0);
                }
            }
            else if (ft_strstr(line, "start") != NULL)
                farm.start_room_id = farm.room_amount;
            else if (ft_strstr(line, "end") != NULL)
                farm.end_room_id = farm.room_amount;
            ft_strdel(&line);
        }
    }
    work(&farm, av);
    the_end();
//    system("leaks lem-in");
    return (0 * ac);
}