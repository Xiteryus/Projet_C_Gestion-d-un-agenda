//
// Created by samue on 23/10/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include "cell.h"

#include <math.h>
#include "timer.h"

#ifndef PROJET_V1_FICHIER_H
#define PROJET_V1_FICHIER_H

typedef struct s_d_list
{
    int max_level;
    t_d_cell **t_heads;

} t_d_list;

t_d_cell* create_cell(int,int);
t_d_list* create_list(int);

void instertcellaniv(t_d_cell*,t_d_list*);
void displaylevelcell(t_d_list* , int);
void displaynivlist(t_d_list*);
void trierliste(t_d_list *l, int i);
void list();
void rechercheclassique(t_d_list *);
void recherchedichotomie(t_d_list *l);

#endif //PROJET_V1_FICHIER_H
