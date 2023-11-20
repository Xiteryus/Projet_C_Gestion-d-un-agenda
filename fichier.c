//
// Created by samue on 23/10/2023.
//

#include "fichier.h"
#include "stdio.h"

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

t_d_list * create_list(int x){
    t_d_list *l = (t_d_list*) malloc(sizeof(t_d_list));

    l->max_level = x;
    l->t_heads = (t_d_cell**) malloc(sizeof(t_d_cell*)*x);
    for (int i = 0; i < x; i++) {
        l->t_heads[i] = NULL;
    }
    return l;
}

void instertcellaniv(t_d_cell *cellule, t_d_list *liste) {
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

void trierliste(t_d_list *l, int i) {
    t_d_cell *p1;
    int x, templev,temp;

    p1 = l->t_heads[i];
    while (p1 != NULL && p1->t_level[i] != NULL) {
        if (p1->value > p1->t_level[i]->value){
            temp = p1->value;
            templev = p1->level;
            p1->value = p1->t_level[i]->value;
            p1->level = p1->t_level[i]->level;
            //temp->t_level[0]=p1->t_level[0];
            p1->t_level[i]->value = temp;
            p1->t_level[i]->level = templev;
            //printf("%d",p1->value);
        }
        else {
            //printf("%d",p1->value);
            p1 = p1->t_level[0];
        }
    }
}

    void displaylevelcell(t_d_list *l, int x) {

    t_d_cell *temp = l->t_heads[x];
    t_d_cell *temp2 = l->t_heads[0];
    while (temp != NULL) {
        if (temp->value == temp2->value) {
            printf(">[%3d|@-]--", temp->value);
            temp = temp->t_level[x];
        }
        else
            printf("-----------");

        temp2 = temp2->t_level[0];

    }
    printf(">NULL");
}

void displaynivlist(t_d_list *l){
    for(int i=0; i<=l->max_level-1;i++){
        printf("[list head_%d @-]--",i);
        displaylevelcell(l,i);
        printf("\n");
    }
}



void list() {
    int x, n=1,y = 1;
    printf("Entrez la valeur n : \n");
    scanf(" %d", &x);

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

    for (int i = 0; i < n - 1; i++) {
        c1 = create_cell(i, t[i]);
        instertcellaniv(c1, l);
    }


    displaynivlist(l);

    printf("Quel recherche voulez-vous effectuer ?  0 pour dichotomique /  1 pour classique ");
    scanf("%d",&y);

    if (y==0) {
        //startTimer();
        for(int i = 0;i<1000;i++)
            recherchedichotomie(l);
        //stopTimer();
        //displayTime();
    }
    if(y==1){
        //startTimer();
        for(int i = 0;i<1000;i++)
            rechercheclassique(l);
        //stopTimer();
        //displayTime();


    }
}

 void rechercheclassique(t_d_list *l){
    int val,i=0;
     printf("Saisir la valeur a rechercher");
     scanf("%d", &val);

     t_d_cell *temp = l->t_heads[0];
     while (temp != NULL) {
         if(temp->value == val){

             printf("La valeur %d se trouve a la %d position ",val,i);
             temp = NULL;
         }
         i++;
         temp = temp->t_level[0];

     }

}

void recherchedichotomie(t_d_list *l){
    int taille_logique = l->max_level-1;
    int g = 0, m, d, pos=-1, arret = 0, val;
    printf("Saisir la valeur à rechercher");
    scanf("%d", &val);
    m = l->t_heads[taille_logique--]->value;
    pos = m+1;
    while (taille_logique>0){

        if (m==val){
            taille_logique = 0;
        }
        else{
            if (val < m){
                m = l->t_heads[taille_logique]->value;
                pos=pos-2;
            }
            else{
                t_d_cell *temp = l->t_heads[taille_logique];
                while (temp->t_level[taille_logique]!=NULL){
                    temp = temp ->t_level[taille_logique];
                }
                m = temp->value;
                pos=pos+2;
            }
            taille_logique--;
        }
    }
    if(pos>=0)
        printf("La valeur %d se trouve à la position %d", val,pos+1 );
    else
        printf("Valeur pas trouvé ");
}


