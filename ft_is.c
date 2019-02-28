/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychufist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 18:23:08 by ychufist          #+#    #+#             */
/*   Updated: 2019/02/19 18:23:11 by ychufist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void write_error(char *s)
{
    write(1, "\e[31m", 5);
    ft_printf("%s\n", s);
    write(1, "\e[0m", 4);
}

int is_valid_name(t_farm farm, const char *name)
{
    t_list_room *dop;

    dop = farm.dop;

    if (name[0] == 'L' || name[0] == '#' ||
            (name[0] == '-' && ft_strlen(name) == 1))
    {
        write_error("NAME ERROR\n");
        return (0);
    }
    while (dop->next)
    {
        if (ft_strcmp(dop->name, name) == 0)
        {
            write_error("THE SAME ROOM NAME IS PRESENT");
            return (0);
        }
        dop = dop->next;
    }
    return (1);
}

int is_valid_map(t_farm farm)
{
    if (farm.ants_amount < 1 || farm.ants_amount > 2147483647)
    {
        write_error("NOT GOOD AMOUNT OF ANTS. ERROR");
        return (0);
    }
    if (farm.start_room_id == -1)
    {
        write_error("THERE IS NO START ROOM. ERROR");
        return (0);
    }
    if (farm.end_room_id == -1)
    {
        write_error("THERE IS NO END ROOM. ERROR");
        return (0);
    }
    if (farm.room_amount < 2)
    {
        write_error("NOT ENOUGH ROOMS. ERROR");
        return (0);
    }
    return (1);
}

int is_coord(t_farm farm, t_list_room *room)
{
    t_list_room *dop2;

    dop2 = farm.dop;
    while (dop2->next)
    {
        if (dop2->coord.x == room->coord.x &&
            dop2->coord.y == room->coord.y)
        {
            write_error("THE ROOM WITH THE SAME COORD"
                        "IS PRESENT OR THERE ARE PROBLEMS WITH INPUT. ERROR");
            return (0);
        }

        dop2 = dop2->next;
    }
    return (1);
}