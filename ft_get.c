/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychufist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 19:55:03 by ychufist          #+#    #+#             */
/*   Updated: 2019/03/02 19:55:04 by ychufist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int get_cood(t_farm *farm, char **line, int n)
{
    int i;
    char *dopline;

    i = 0;
    dopline = *line;
    while ((*line)[i] == ' ')
        i++;
    while ((*line)[i] != ' ' && (*line)[i] != '\0')
    {
        if (!ft_isdigit((*line)[i++]))
        {
            write_error("INCORRECT INPUT. ERROR");
            return (0);
        }
    }
    (*line)++;
    if (n == 1)
        farm->init->coord.x = ft_atoi(dopline);
    else if (n == 2)
        farm->init->coord.y = ft_atoi(dopline);
    return (1);
}

int get_info(t_farm *farm, char *line, int *i)
{
    char *dop;
    char *dop2;

    if ((*i) == 0)
    {
        farm->ants_amount = ft_atoi(line);
        (*i)++;
    }
    else if (ft_strchr(line, '-') == NULL)
    {
        dop = ft_strchr(line, ' ');
        dop2 = ft_strsub(line, 0, dop - line);
        if (!is_valid_name(*farm, dop2))
            return (0);
        farm->init->id = farm->room_amount;
        farm->init->name = ft_strdup(dop2);
        ft_strdel(&dop2);
        if (get_cood(farm, &dop, 1) == 0)
            return (0);
        dop = ft_strchr(dop, ' ');
        if (get_cood(farm, &dop, 2) == 0)
            return (0);
        if (!is_coord(*farm, farm->init))
            return (0);
        room_init(farm);
    }
    return (1);
}

int get_start_end(t_farm *farm, char *line)
{
    if (ft_strcmp(line, "##start") == 0)
    {
        farm->start_room_id = farm->room_amount;
        return (1);
    }
    else if (ft_strcmp(line, "##end") == 0)
    {
        farm->end_room_id = farm->room_amount;
        return (1);
    }
    else if (line[0] == '#')
        return (1);
    return (0);
}