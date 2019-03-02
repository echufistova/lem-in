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

void get_way(t_farm *farm, t_list_room *way, int flag)
{
    t_list_room *rm;
    t_list_room *dop;
    t_list_room *tmp;

    bzero_ways(farm);
    tmp = way;
    while (way->next)
        way = way->next;
    farm->ways[farm->ways_amount] = ft_list_room_new(farm->rooms[
                                                             farm->start_room_id]);
    dop = farm->ways[farm->ways_amount];
    rm = way->prev;
    while (rm->id!= farm->end_room_id)
    {
        farm->ways[farm->ways_amount]->next = ft_list_room_new(farm->rooms[rm->id]);
        farm->ways[farm->ways_amount] = farm->ways[farm->ways_amount]->next;
        farm->rooms[rm->id].flag = 2;
        rm = rm->prev;
    }
    farm->ways[farm->ways_amount]->next = ft_list_room_new(farm->rooms[
                                                                   rm->id]);
    farm->ways[farm->ways_amount] = dop;
    farm->ways[farm->ways_amount]->size = ft_list_size(farm->ways[
                                                               farm->ways_amount]) - 1;
    if (farm->col != -1)
        farm->ways[farm->ways_amount]->color = farm->colors[farm->col++];
    if (farm->col == 5)
        farm->col = 0;
    farm->ways_amount++;
    free_list(&way);
    free_list(&tmp);
    find_ways(farm, flag);
}

void find_ways(t_farm *farm, int flag)
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
        if (flag == 1)
            break;
        j = -1;
        while (++j < dop2->links_amount)
        {
            ft_printf("fw %s %d %d %s\n", dop2->name, dop2->links_amount, dop2->links[j],
                      farm->rooms[dop2->links[j]].name);
            if (farm->rooms[dop2->links[j]].flag != 1 &&
                farm->rooms[dop2->links[j]].flag != 2)
            {
                if (way->id != farm->end_room_id && way->id != -1)
                    farm->rooms[way->id].flag = 1;
                if (way->links_amount == 1 && way->links[0] == farm->start_room_id)
                {
                    way->next = ft_list_room_new(farm->rooms[dop2->links[j]]);
                    way = way->next;
                    way->prev = dop2;
                    get_way(farm, dop, 1);
                    return ;
                }
                if (dop2->links[j] != farm->end_room_id)
                {
                    way->next = ft_list_room_new(farm->rooms[dop2->links[j]]);
                    way = way->next;
                    way->prev = dop2;
                    if (way->id == farm->start_room_id)
                    {
                        get_way(farm, dop, flag);
                        return ;
                    }
                }
            }
        }
        dop2 = dop2->next;
    }
    free_list(&way);
    free_list(&dop);
    bzero_ways(farm);
}

void print_ways(t_farm farm)
{
    int i;
    t_list_room *ways;

    i = 0;

    ft_printf("Amount of ways: %d\n", farm.ways_amount);
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

