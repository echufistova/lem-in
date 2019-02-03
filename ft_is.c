//
// Created by echufy on 31.01.19.
//

#include "lem_in.h"

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

