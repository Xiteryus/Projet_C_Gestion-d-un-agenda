//
// Created by samue on 23/10/2023.
//

#include "List.h"
#include "stdio.h"
#include <malloc.h>


//Fonction qui cree une liste
t_d_list * create_list(int x){
    t_d_list *l = (t_d_list*) malloc(sizeof(t_d_list));// Alloue de la mémoire pour la structure Liste

    l->max_level = x;
    l->t_heads = (t_d_cell**) malloc(sizeof(t_d_cell*)*x);
    for (int i = 0; i < x; i++) {
        l->t_heads[i] = NULL;
    }
    return l;
}
//Fonction qui inssert une cellule dans une liste en la triant
void Insert_Cell_To_List(t_d_cell *cellule, t_d_list *liste) {
    int niveau = cellule->level;

    // Assurez-vous que la cellule est initialisée correctement
    cellule->t_level = (t_d_cell **)malloc(sizeof(t_d_cell *) * (niveau + 1));
    for (int i = 0; i <= niveau; i++) {
        cellule->t_level[i] = NULL;
    }

    for (niveau; niveau >= 0; niveau--) {
        t_d_cell *actuel = liste->t_heads[niveau];
        t_d_cell *precedent = NULL;
        while (actuel != NULL && actuel->value < cellule->value) {
            precedent = actuel;
            actuel = actuel->t_level[niveau];
        }

        if (precedent == NULL) {
            cellule->t_level[niveau] = liste->t_heads[niveau];
            liste->t_heads[niveau] = cellule;
        } else {
            cellule->t_level[niveau] = actuel;
            precedent->t_level[niveau] = cellule;
        }
    }
}

    //Fonction qui affiche une cellule avec ces niveaux
void Display_Cell(t_d_list *l, int x) {

    t_d_cell *temp = l->t_heads[x];//premier temporaire pour parcourir la liste
    t_d_cell *temp2 = l->t_heads[0];//deuxieme temporaire pour l'option bonnus
    while (temp != NULL) {//on parcourt la liste pour afficher les cellule
        if (temp->value == temp2->value) {
            printf(">[%3d|@-]--", temp->value);//affichage des cellules
            temp = temp->t_level[x];
        }
        else
            printf("-----------"); //option bonus qui alligne les cellules

        temp2 = temp2->t_level[0];

    }
    printf(">NULL");
}


void Display_List(t_d_list *l){
    for(int i=0; i<=l->max_level-1;i++){//on parcourt la liste du niveau 0 au niveau max
        printf("[list head_%d @-]--",i);//affichage de chaque niveau
        Display_Cell(l,i);//on appelle la fonction qui affiche les cellule
        printf("\n");
    }
}


//Fonction qui crée une liste
t_d_list *Create_List(int valeur) {
    int x, n=1,y = 1,val=0;
    x = valeur;
    t_d_cell *c;
    for (int i = 0; i < x; i++)//meme utilité que la fonction pow
        n *= 2;
    t_d_list *l = create_list(x);//creation de liste
    int t[n - 1];
    t_d_cell *c1;
    for (int j = 0; j < n - 1; j++) {
        t[j] = 0;
    }
    int k = 2;
    for (int i = 2; i <= n - 1; i = (int) pow(2, k++)) {//creation d'un tableau contenant 0 1 0 2 0 3 .....

        for (int j = i - 1; j < n - 1; j = j + i) {
            t[j] = t[j] + 1;
        }

    }

    printf("\n");
    for (int i = 0; i < n - 1; i++) {
        //printf("%d / %d \n",i,t[i]);
        c = create_cell(i,t[i]);
        Insert_Cell_To_List(c, l);//insertion de la cellule en fonction du tableau crée precedement
    }

    //Display_List(l);

    return l;

}
//Recherche classique pour une valeur dans une liste
 int Classic_Research(t_d_list *l,int x){
    int val=x,i=0;

     t_d_cell *temp = l->t_heads[0];
     while (temp != NULL) {//on parcourt la liste avec l'aide d'un temporaire
         if(temp->value == val){

             return i;//on retourne la valeur si elle existe dans la liste
         }
         i++;
         temp = temp->t_level[0];


     }
    return -1;//on retourne -1 si la valeur n'est pas dans la liste
}

//Recherche dichotomique pour une valeur dans une liste
int Dichotomy_Research(t_d_list *l, int x) {
    int level = l->max_level - 1;
    t_d_cell *current = l->t_heads[level];//on commence par partir du niveau le plus haut dans la liste

    while (level >= 0 && current != NULL) {
        if (current->value == x) {
            return 1;//on retourne si la valeur est dans la liste
        }
        if (current->t_level[level] != NULL && current->t_level[level]->value <= x) {
            current = current->t_level[level];
        } else {
            level--;//on descend d'un niveau

        }
    }
    return 0;//on retourne si la valeur n'est pas dans la liste
}





