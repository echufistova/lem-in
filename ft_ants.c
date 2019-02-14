#include "lem_in.h"

t_ant *create_ants(int ants_amount) {
    int  i;

    i = 0;
    t_ant *ants = (t_ant*)malloc(sizeof(t_ant) * ants_amount);
    while( i < ants_amount ) {
        ants[i].number = i + 1;
        ants[i].way = NULL;
        ants[i].way_size = -1;
        ants[i].currnet_index = 0;
        i++;
    }
    return ants;
}