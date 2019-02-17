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


