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
    int niveau = cellule->level ;
    for (niveau; niveau >= 0; niveau--){
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
    /*int level = c->level;
    t_d_cell *temp,*temp2;
    if (l->t_heads[0] == NULL){
        for (int i = level; i >= 0; i--) {
            c->t_level[i] = l->t_heads[i];
            l->t_heads[i] = c;
        }
    }

    else {

        for (int i = level; i >= 0; i--){
            temp = l->t_heads[i];
                if (temp->value < c->value) {

                    while (temp->t_level[i] != NULL) {
                        printf("5");
                        c->t_level[i] = temp->t_level[i];
                        temp->t_level[i] = c;
                        temp = temp->t_level[i];
                        temp->t_level[i] = NULL;

                    }
                }
                else{
                    c->t_level[i] = l->t_heads[i];
                    l->t_heads[i] = c;
                }
            }

        }
    }


    if (l->t_heads[0] == NULL){
        for (int i = level; i >= 0; i--) {
            c->t_level[i] = l->t_heads[i];
            l->t_heads[i] = c;
        }
    }

    else {

        for (int i = level; i >= 0; i--){
            while (l->t_level[i] != NULL){
                if (l->t_heads[i]->value < c->value){
                    c->t_level[i] = l->t_heads[i]->t_level[i];
                    l->t_heads[i]->t_level[i] = c;
                    l = l->t_heads[i];
                }
                else{
                    c->t_level[i] = l->t_heads[i];
                    l->t_heads[i] = c;
                }
            }

        }
    }
}

*/

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
void Create_List() {
    int x, n=1,y = 1,val=0;
    printf("Entrez la valeur n : \n");
    scanf(" %d", &x);
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


    Display_List(l);

    printf("Quel recherche voulez-vous effectuer ?  0 pour dichotomique /  1 pour classique ");
    scanf("%d",&y);

    if (y==0) {
        printf("Saisir la valeur a rechercher");
        scanf("%d", &val);
        Dichotomy_Research(l,val);

    }
    if(y==1){
        //printf("Saisir la valeur a rechercher");
        //scanf("%d", &val);
        startTimer();
        for(int i=0;i<1000000;i++) {
            Classic_Research(l, rand() % 7);
        }
        stopTimer();
        displayTime();
    }
}
//Recherche classique pour une valeur dans une liste
 void Classic_Research(t_d_list *l,int x){
    int val=x,i=0;

     t_d_cell *temp = l->t_heads[0];
     while (temp != NULL) {
         if(temp->value == val){

             printf("Position %d",i);
             break;
         }
         i++;
         temp = temp->t_level[0];


     }

}
//Recherche dichotomique pour une valeur dans une liste
void Dichotomy_Research(t_d_list *l,int x){
    int taille_logique = l->max_level-1;
    int g = 0, m, d, pos, arret = 0, val = x;

    m = l->t_heads[taille_logique--]->value;
    pos = m-1;
    printf("%d\n", pos);
    while (taille_logique>0){

        if (m==val){
            taille_logique = 0;
        }
        else{
            if (val < m){
                m = l->t_heads[taille_logique]->value;
                pos=pos-2;
                printf("%d\n", pos);

            }
            else{
                t_d_cell *temp = l->t_heads[taille_logique];
                while (temp->t_level[taille_logique]!=NULL){
                    temp = temp ->t_level[taille_logique];
                }
                m = temp->value;
                pos=pos+2;
                printf("%d\n", pos);

            }
            taille_logique--;
        }
    }
    if(pos>=0)
        printf("\nPosition %d",pos);
    else
        printf("Valeur pas trouvé ");
}


