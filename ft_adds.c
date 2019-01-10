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
    ft_printf("добавляем к комнате %s линк %s\n", farm->rooms[i].name, line);
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
    ft_printf("у комнаты %s %d линк(а)\n\n", farm->rooms[i].name, farm->rooms[i].links_amount);
}