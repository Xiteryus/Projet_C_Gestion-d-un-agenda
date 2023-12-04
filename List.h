//
// Created by samue on 23/10/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "timer.h"
#include "Cell.h"
#ifndef PROJET_V1_FICHIER_H
#define PROJET_V1_FICHIER_H
//Structures :

//LISTE
typedef struct s_d_list
{
    int max_level;
    t_d_cell **t_heads;

} t_d_list;
//-------------------------------

//Fonctions

//Creation celule et liste
t_d_cell* create_cell(int,int);
t_d_list* create_list(int);

//mettre une cellule dans une liste
void Insert_Cell_To_List(t_d_cell*,t_d_list*);

//afficher la liste
void Display_Cell(t_d_list* , int);
void Display_List(t_d_list*);

//creer la liste
void Create_List();

//recherche d'une valeur dans la liste
void Classic_Research(t_d_list *,int);
void Dichotomy_Research(t_d_list *l,int);

#endif //PROJET_V1_FICHIER_H
