//
// Created by samue on 03/12/2023.
//

#ifndef PROJET_V1_CONTACT_H
#define PROJET_V1_CONTACT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
//Structures :

typedef struct Contact
{
    char *nom;
    char *prenom;
}contact;

//Rendez-Vous
typedef struct Date
{
    int jour;
    int heure;
    int annee;
}date;

typedef struct Heure
{
    int heure;
    int minute;
}heure;

typedef struct rendez_vous
{
    struct Date date;
    struct Heure heure;
    struct Heure dure_rdv;
    char *objet;
}rdv;
//Agenda
typedef struct Agenda
{
    contact contact;
    rdv *rendezvous_list;
    struct s_agenda_entry *next;
} agenda;

//List à contact
typedef struct Liste_Contact
{
    int max_level;
    contact **t_heads;

} list_contact;

//Fonction :

void Create_Contact(agenda*);
list_contact Create_List_Contact(int n);
agenda *Create_Agenda();
void Insert_Contact_To_Agenda(list_contact*,contact*);
char *scanString(void);
void *PrintString(char *c);






#endif //PROJET_V1_CONTACT_H