//
// Created by echufy on 27.12.18.
//

#include "lem_in.h"

void dop(t_farm *farm, char *name, t_point ij, int i, int id)
{
    farm->rooms[i].id = id;
    farm->rooms[i].name = name;
    farm->rooms[i].coord.x = ij.x;
    farm->rooms[i].coord.y = ij.y;
}

void add_room(t_farm *farm)
{
    t_room *dop_rooms;
    int i;

    i = 0;
    if (farm->room_amount > 0)
    {
        i = -1;
        dop_rooms = (t_room*)malloc(sizeof(t_room) * (farm->room_amount + 1));
        while (++i < farm->room_amount)
        {
            dop_rooms[i].id = farm->rooms[i].id;
            dop_rooms[i].name = farm->rooms[i].name;
            dop_rooms[i].coord.x = farm->rooms[i].coord.x;
            dop_rooms[i].coord.y = farm->rooms[i].coord.y;
        }
        i = -1;
        ft_bzero(farm->rooms, sizeof(t_room *));
        farm->rooms = (t_room*)malloc(sizeof(t_room) * (farm->room_amount + 1));
        while (++i < farm->room_amount)
            dop(farm, dop_rooms[i].name, dop_rooms[i].coord, i, dop_rooms[i].id);
        ft_bzero(dop_rooms, sizeof(t_room *));
    }
    farm->rooms[i].name = NULL;
    farm->rooms[i].coord.x = 0;
    farm->rooms[i].coord.y = 0;
}


void freeshka(int size, char **links)
{
    int j;

    j = -1;
    while (++j < size)
    {
        ft_bzero(links[j], sizeof(char*));
        free(links[j]);
    }
    free(links);
}

void add_link(t_farm *farm, char *line, int i)
{
    int j;
    t_room dop_room;

    j = -1;
    dop_room.links = (char**)malloc(sizeof(char*) * (farm->rooms[i].links_amount));
    dop_room.links_amount = farm->rooms[i].links_amount;
    while (++j < farm->rooms[i].links_amount)
        dop_room.links[j] = ft_strdup(farm->rooms[i].links[j]);
    freeshka(farm->rooms[i].links_amount, farm->rooms[i].links);
    farm->rooms[i].links = (char**)malloc(sizeof(char*) * (farm->rooms[i].links_amount + 1));
    j = -1;
    while (++j < farm->rooms[i].links_amount)
        farm->rooms[i].links[j] = ft_strdup(dop_room.links[j]);
    farm->rooms[i].links[j] = ft_strdup(line);
    freeshka(dop_room.links_amount, dop_room.links);
    farm->rooms[i].links_amount++;
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

int is_room(t_farm farm, char *name)
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