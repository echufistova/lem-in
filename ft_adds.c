//
// Created by echufy on 27.12.18.
//

#include "lem_in.h"

void add_room(t_farm *farm)
{
    t_room *dop_rooms;
    int i;

    i = -1;
    if (farm->room_amount > 0)
    {
        dop_rooms = (t_room*)malloc(sizeof(t_room) * (farm->room_amount + 1));
        while (++i < farm->room_amount)
        {
            dop_rooms[i].name = ft_strdup(farm->rooms[i].name);
            dop_rooms[i].coord.x = farm->rooms[i].coord.x;
            dop_rooms[i].coord.y = farm->rooms[i].coord.y;
        }
        i = -1;
        ft_bzero(farm->rooms, sizeof(t_room *));
        farm->rooms = (t_room*)malloc(sizeof(t_room) * (farm->room_amount + 1));
        while (++i < farm->room_amount)
        {
            farm->rooms[i].name = ft_strdup(dop_rooms[i].name);
            farm->rooms[i].coord.x = dop_rooms[i].coord.x;
            farm->rooms[i].coord.y = dop_rooms[i].coord.y;
        }
    }
    farm->rooms[i].name = NULL;
    farm->rooms[i].coord.x = 0;
    farm->rooms[i].coord.y = 0;
}

void add_link(t_farm *farm, char *line, int i)
{
    int j;
    t_room dop_room;

    j = 0;
    dop_room.links = (char**)malloc(sizeof(char*) * (farm->rooms[i].links_amount + 1));
    dop_room.links_amount = farm->rooms[i].links_amount;
    while (j < farm->rooms[i].links_amount - 1)
    {
        dop_room.links[j] = ft_strdup(farm->rooms[i].links[j]);
        j++;
    }
    j = 0;
    while (j < farm->rooms[i].links_amount - 1)
        ft_bzero(farm->rooms[i].links[j++], sizeof(char*));
    farm->rooms[i].links = (char**)malloc(sizeof(char*) * (farm->rooms[i].links_amount + 1));
    while (j < farm->rooms[i].links_amount - 1)
    {
        farm->rooms[i].links[j] = ft_strdup(dop_room.links[j]);
        j++;
    }
    farm->rooms[i].links[j] = ft_strdup(line);
    j = 0;
    while (j < dop_room.links_amount - 1)
        ft_bzero(dop_room.links[j++], sizeof(char*));
    farm->rooms[i].links_amount++;

}