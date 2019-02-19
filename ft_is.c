//
// Created by echufy on 31.01.19.
//

#include "lem_in.h"

void write_error(char *s)
{
    write(1, "\e[31m", 5);
    ft_printf("%s\n", s);
    write(1, "\e[0m", 4);
}

int is_valid_name(const char *name)
{
    if (name[0] == 'L' || name[0] == '#')
    {
        ft_printf("NAME ERROR\n");
        return (0);
    }
    return (1);
}

//int is_valid_name(t_farm farm, const char *name)
//{
//    int i;
//
//    if (name[0] == 'L' || name[0] == '#')
//    {
//        write_error("NAME ERROR\n");
//        return (0);
//    }
//    i = -1;
//    while (++i < farm.room_amount)
//    {
//        if (ft_strcmp(farm.rooms[i].name, name) == 0)
//        {
//            write_error("THE SAME ROOM NAME IS PRESENT");
//            return (0);
//        }
//    }
//    return (1);
//}

int is_valid_map(t_farm farm)
{
    if (farm.ants_amount < 1)
    {
        ft_printf("NAME ERROR\n");
        return (0);
    }
    if (farm.is_start == 0)
    {
        write_error("THERE IS NO START ROOM");
        return (0);
    }
    if (farm.is_end == 0)
    {
        write_error("THERE IS NO END ROOM");
        return (0);
    }
//    farm.room_amount++;
//    while (--farm.room_amount)
//    {
//        if (farm.rooms[farm.room_amount].links_amount < 1)
//        {
//            write_error("THE ROOM HAS NO LINKS");
//            return(0);
//        }
//    }
    return (1);
}

int is_coord(t_farm farm, t_room room)
{
    int i;

    i = -1;
    while (++i < farm.room_amount)
    {
        if (room.coord.x == farm.rooms[i].coord.x &&
            room.coord.y == farm.rooms[i].coord.y)
        {
            write_error("THE ROOM WITH THE SAME COORD IS PRESENT");
            return (0);
        }
    }
    return (1);
}

