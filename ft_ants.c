/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ants.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychufist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 18:22:36 by ychufist          #+#    #+#             */
/*   Updated: 2019/02/19 18:22:40 by ychufist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


t_ant *create_ants(int ants_amount) {
    int  i;

    i = 0;
    t_ant *ants;
    ants = (t_ant*)malloc(sizeof(t_ant) * ants_amount);
    while( i < ants_amount ) {
        ants[i].number = i + 1;
        ants[i].way = NULL;
        ants[i].way_size = -1;
        ants[i].currnet_index = 0;
        i++;
    }
    return ants;
}

int allAntsGotEnd(t_ant * ants, int ants_amount) {
    int i;

    i = -1;
    while(++i < ants_amount)
    {
        if(ants[i].currnet_index <= ants[i].way_size )
            return 0;
    }
    return 1;
}

void print_ants_movings(t_ant * ants, int ants_amount) {
    int  i;
    int  j;
    t_list_room     *tmp_way;

    i = -1;
    while(++i < ants_amount)
    {
        if(ants[i].currnet_index > ants[i].way_size)
            continue;
        tmp_way = ants[i].way;
        j = -1;
        while(++j < ants[i].currnet_index)
            tmp_way = tmp_way->next;
        if(ants[i].currnet_index != 0)
        {
            if (ants[i].way->color != NULL)
                write(1, ants[i].way->color, 5);
            ft_printf("L%d-%s ", ants[i].number, tmp_way->name);
            write(1, "\e[0m", 4);
        }
    }
    ft_printf("\n");
}

int get_ants(t_farm farm, t_ant *ants, int current_ants_number)
{
    int i;
    int j;
    int check_exp;

    i = -1;
    while (++i < farm.ways_amount)
    {
        check_exp = 0;
        j = -1;
        while (i != 0 && ++j < i)
            check_exp += farm.ways[i]->size - farm.ways[j]->size;
        if (farm.ants_amount - current_ants_number >= check_exp)
        {
            ants[current_ants_number - 1].way = farm.ways[i];
            ants[current_ants_number - 1].way_size =
                    ft_list_size(farm.ways[i]) - 1;
            ants[current_ants_number - 1].currnet_index++;
            current_ants_number++;
        }
    }
    return (current_ants_number);
}

int move_ants(t_farm farm, t_ant *ants)
{
    int j;
    int counter;
    int current_ants_number;

    counter = 0;
    current_ants_number = 1;
    while (current_ants_number <= farm.ants_amount ||
    !allAntsGotEnd(ants, farm.ants_amount))
    {
        if(current_ants_number <= farm.ants_amount)
            current_ants_number = get_ants(farm, ants, current_ants_number);
        print_ants_movings(ants, current_ants_number - 1);
        counter++;
        j = -1;
        while(++j < current_ants_number - 1)
            ants[j].currnet_index++;
    }
    return (counter);
}