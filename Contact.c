//
// Created by samue on 03/12/2023.
//

#include "Contact.h"

void Create_Contact(agenda *a){

    char *x;
    char *y;
    contact *c = (contact*)(sizeof(contact));
    //printf("Inserer le nom : ");
    //x = scanString();
    //PrintString(x);

    c->nom = "gfdg";
    //PrintString(c->nom);
    printf("Inserer le prenom : ");
    y = scanString();
    c->prenom = (char*) (malloc(sizeof(char)*50));
    c->prenom = y;
    a->contact =*c;

}

list_contact Create_List_Contact(int n){
    list_contact *l = (list_contact*) malloc(sizeof(list_contact));

    l->max_level = n;
    l->t_heads = (contact **) malloc(sizeof(contact *)*n);

    return *l;
}

agenda *Create_Agenda(){
    agenda *a = (agenda*) malloc(sizeof(agenda));

    a->contact.prenom = " ";
    a->contact.nom = "moi";
    a->rendezvous_list = NULL;
    a->next = NULL;

    return a;
}

char *scanString(void){
    int taille = 50,i=0;
    char *c = (char*) (malloc(sizeof(char)*taille));

    while (i<taille-1){
        scanf("%c",&c[i]);
        if (c[i]=='\n')
            break;
        i++;
    }
    return c;
}

void *PrintString(char *c){
    int i = 0;
    while(c[i]!='\n'){
        printf("%c",c[i]);
        i++;
    }
}

void Insert_Contact_To_List(list_contact *l,contact *c){


}

void insert_contact_to_Agenda(contact *cellule, list_contact *liste){


}

void display(contact *c){


}
