//
// Created by samue on 23/10/2023.
//

#ifndef PROJET_V1_CELL_H
#define PROJET_V1_CELL_H

typedef struct s_d_cell
{
    int value;
    int level;
    struct s_d_cell **t_level;

} t_d_cell;


#endif //PROJET_V1_CELL_H
