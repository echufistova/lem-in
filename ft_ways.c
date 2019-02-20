/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ways.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychufist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 18:26:31 by ychufist          #+#    #+#             */
/*   Updated: 2019/02/19 18:26:35 by ychufist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void bzero_ways(t_farm *farm)
{
    int i;

    i = 0;
    while (i < farm->room_amount)
    {
        if (farm->rooms[i].flag != 2)
            farm->rooms[i].flag = 0;
        i++;
    }
}

void get_way(t_farm *farm, t_list_room *way)
{
    t_list_room *rm;
    t_list_room *dop;

    bzero_ways(farm);
    while (way->next)
        way = way->next;
    farm->ways[farm->ways_amount] = ft_list_room_new(farm->rooms[
            farm->start_room_id]);
    dop = farm->ways[farm->ways_amount];
    rm = way->prev;
    while (ft_strcmp(rm->name, farm->rooms[farm->end_room_id].name) != 0)
    {
        farm->ways[farm->ways_amount]->next = ft_list_room_new(farm->rooms[
                is_room(*farm, rm->name)]);
        farm->ways[farm->ways_amount] = farm->ways[farm->ways_amount]->next;
        farm->rooms[is_room(*farm, rm->name)].flag = 2;
        rm = rm->prev;
    }
    farm->ways[farm->ways_amount]->next = ft_list_room_new(farm->rooms[
            is_room(*farm, rm->name)]);
    farm->ways[farm->ways_amount] = dop;
    farm->ways[farm->ways_amount]->size = ft_list_size(farm->ways[
            farm->ways_amount]) - 1;
    farm->ways_amount++;
    find_ways(farm);
}

t_list_room *find_ways(t_farm *farm)
{
    int j;
    t_list_room *way;
    t_list_room *dop2;
    t_list_room *dop;

    way = ft_list_room_new(farm->rooms[farm->end_room_id]);
    dop = way;
    dop2 = way;
    while (dop2)
    {
        j = -1;
        while (++j < dop2->links_amount)
        {
            if (farm->rooms[is_room(*farm, dop2->links[j])].flag != 1 &&
                farm->rooms[is_room(*farm, dop2->links[j])].flag != 2)
            {
                if (is_room(*farm, way->name) != farm->end_room_id)
                    farm->rooms[is_room(*farm, way->name)].flag = 1;
                if (is_room(*farm, dop2->links[j]) != farm->end_room_id)
                {
                    way->next = ft_list_room_new(farm->rooms[is_room(*farm,
                                                             dop2->links[j])]);
                    way = way->next;
                    way->prev = dop2;
                    if (is_room(*farm, way->name) == farm->start_room_id)
                    {
                        get_way(farm, dop);
                        return (way);
                    }
                }
            }
        }
        dop2 = dop2->next;
    }
    bzero_ways(farm);
    return (NULL);
}

void print_ways(t_farm farm)
{
    int i;
    t_list_room *ways;

    i = 0;

    while (i < farm.ways_amount)
    {
        ways = farm.ways[i];
        ft_printf("%d) %d : ",  i + 1, ways->size);
        while (ways)
        {
            ft_printf("%s -> ", ways->name);
            if (ways->next)
                ways = ways->next;
            else
                break;
        }
        ft_printf("\n");
        i++;
    }
    ft_printf("\n");
}