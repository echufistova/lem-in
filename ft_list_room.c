//
// Created by Yevheniya CHUFISTOVA on 2019-01-10.
//

#include "lem_in.h"

t_list_room *ft_list_room_new(t_room room)
{
    int i;
    t_list_room *res;

    i = -1;
    if (!(res = (t_list_room*)malloc(sizeof(t_list_room))))
		return (NULL);
    if (!(res->name = (void*)malloc(ft_strlen(room.name))))
    {
			free(res);
			return (NULL);
    }
    res->name = room.name;
    res->links_amount = room.links_amount;
    res->flag = 0;
    res->links = (char**)malloc(sizeof(char*) * room.links_amount);
    while (++i < room.links_amount)
        res->links[i] = room.links[i];
    res->next = NULL;
    return (res);
}

int ft_list_room_find(t_list_room *room_list, char *name)
{
    while (room_list)
    {
        if (ft_strcmp(room_list->name, name) == 0)
            return (1);
        room_list = room_list->next;
    }
    return (0);
}

int ft_list_size(t_list_room *room_list)
{
    int i;

    i = 0;
    while (room_list)
    {
        room_list = room_list->next;
        i++;
    }
    return (i);
}

void print_list(t_list_room *room_list)
{
    while (room_list)
    {
        ft_printf("%s->", room_list->name);
        room_list = room_list->next;
    }
}

void ft_list_room_add(t_list_room **alst, t_list_room *new)
{
    if (alst && *alst)
        new->next = *alst;
    *alst = new;
}

t_list_room find_parent(char *room_name, t_list_room *way)
{
    t_list_room *dop;

    dop = way;
    while (ft_strcmp(way->name, room_name) != 0)
    {
        way = way->next;
    }
//    ft_printf("PARENT : %s\n", way->parent);
    return (*way);
}