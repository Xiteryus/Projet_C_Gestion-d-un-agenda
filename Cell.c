//
// Created by samue on 01/12/2023.
//

#include "Cell.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Fonction qui cree une cellule
t_d_cell* create_cell(int val,int lev) {
    t_d_cell *s = (t_d_cell *) malloc(sizeof(t_d_cell));

    s->value = val;
    s->level = lev;
    s->t_level = (t_d_cell **) malloc(sizeof(t_d_cell *) * lev);
    //tableau qui stocke pointeur --> pointeur qui stock pointeur donc double étoile
    for (int i = 0; i < lev; i++) {
        s->t_level[i] = NULL;

    }
    return s;
}


