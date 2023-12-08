#ifndef PROJET_V1_CONTACT_H
#define PROJET_V1_CONTACT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Structures :


//----------------------------------------------------------------------

typedef struct Contact {
    char *nom;
    char *prenom;
} Contact;
//----------------------------------------------------------------------

typedef struct Date {
    int jour;
    int mois;
    int annee;
} Date;

typedef struct Heure {
    int heure;
    int minute;
} Heure;

typedef struct RendezVous {
    Date date;
    Heure heure;
    Heure dure_rdv;
    char *objet;
    struct RendezVous *next;  // Champ pour lier les rendez-vous
} Rdv;
//----------------------------------------------------------------------

typedef struct AgendaEntry {
    Contact *contact;
    Rdv *rendezvous_list;
    struct AgendaEntry *next;
} AgendaEntry;

typedef struct ListeContact {
    int max_level;
    AgendaEntry **next;
} ListeContact;

//----------------------------------------------------------------------
// Fonctions :

Contact *CreateContact(const char *nom, const char *prenom);
ListeContact CreateListeContact(int n);
AgendaEntry *CreateAgendaEntry();
Rdv CreateRDV(Date, Heure, Heure, char *);
Date CreateDate(int a, int j, int h);
Heure CreateHeure(int h, int m);

//----------------------------------------------------------------------

Rdv Saisir_RDV();

//----------------------------------------------------------------------

void ContactResearch(ListeContact *liste_contact, const char *n, const char *p);
void AddContactToAgenda(ListeContact *liste_contact, const char *nom, const char *prenom);
void AddRDVToContact(ListeContact *liste_contact, const char *n, const char *p, Rdv RDV);
//----------------------------------------------------------------------

char *scanString(void);
void *PrintString(char *c);

//----------------------------------------------------------------------

void DisplayContact(ListeContact *liste_contact);
void DisplayAgenda(AgendaEntry *);
void DisplayListeContact(ListeContact *liste_contact);
void Display_RDV(ListeContact *l, const char *n, const char *p);

//----------------------------------------------------------------------

void Create_Contacts_From_Files(ListeContact *liste_contact);
void Save_RDV_In_File(ListeContact *liste_contact,const char *n, const char *p);
#endif //PROJET_V1_CONTACT_H