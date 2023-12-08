//
// Created by samue on 23/10/2023.
//

#include "List.h"
#include "stdio.h"
#include <malloc.h>


//Fonction qui cree une liste
t_d_list * create_list(int x){
    t_d_list *l = (t_d_list*) malloc(sizeof(t_d_list));

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

    t_d_cell *temp = l->t_heads[x];
    t_d_cell *temp2 = l->t_heads[0];
    while (temp != NULL) {
        if (temp->value == temp2->value) {
            printf(">[%3d|@-]--", temp->value);
            temp = temp->t_level[x];
        }
        else
            printf("-----------"); //option bonus qui alligne les cellules

        temp2 = temp2->t_level[0];

    }
    printf(">NULL");
}


void Display_List(t_d_list *l){
    for(int i=0; i<=l->max_level-1;i++){
        printf("[list head_%d @-]--",i);
        Display_Cell(l,i);
        printf("\n");
    }
}


//Fonction qui crée une liste
t_d_list *Create_List(int valeur) {
    int x, n=1,y = 1,val=0;
    x = valeur;
    t_d_cell *c;
    for (int i = 0; i < x; i++)
        n *= 2;
    t_d_list *l = create_list(x);
    int t[n - 1];
    t_d_cell *c1;
    for (int j = 0; j < n - 1; j++) {
        t[j] = 0;
    }
    int k = 2;
    for (int i = 2; i <= n - 1; i = (int) pow(2, k++)) {

        for (int j = i - 1; j < n - 1; j = j + i) {
            t[j] = t[j] + 1;
        }

    }
    for (int j = 0; j < n - 1; j++) {
        //printf("%d\n", t[j]);
    }
    printf("\n");
    for (int i = 0; i < n - 1; i++) {
        //printf("%d / %d \n",i,t[i]);

        c = create_cell(i,t[i]);
        Insert_Cell_To_List(c, l);
    }

    //Display_List(l);

    return l;

}
//Recherche classique pour une valeur dans une liste
 int Classic_Research(t_d_list *l,int x){
    int val=x,i=0;

     t_d_cell *temp = l->t_heads[0];
     while (temp != NULL) {
         if(temp->value == val){

             return i;
         }
         i++;
         temp = temp->t_level[0];


     }
    return -1;
}
//Recherche dichotomique pour une valeur dans une liste
int Dichotomy_Research(t_d_list *l, int x) {
    int level = l->max_level - 1;
    t_d_cell *current = l->t_heads[level];

    while (level >= 0 && current != NULL) {
        if (current->value == x) {
            // Valeur trouvée, renvoyer quelque chose de significatif ou la position si nécessaire
            return current->value+1;  // Dans cet exemple, renvoie simplement 1 pour indiquer que la valeur est trouvée
        } else {
            if (current->value < x) {
                current = current->t_level[0];
            }
            else {
                // Descendre d'un niveau
                level--;
                current = l->t_heads[level];  // Descendre d'un niveau

            }
        }
    }

    return 0; // Valeur non trouvée
}




