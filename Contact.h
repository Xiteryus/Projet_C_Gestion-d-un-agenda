#ifndef PROJET_V1_CONTACT_H
#define PROJET_V1_CONTACT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Structures :


//----------------------------------------------------------------------
//CONTACT
typedef struct Contact {
    char *nom;
    char *prenom;
} Contact;
//----------------------------------------------------------------------
//DATE
typedef struct Date {
    int jour;
    int mois;
    int annee;
} Date;
//HEURE
typedef struct Heure {
    int heure;
    int minute;
} Heure;
//RDV
typedef struct RendezVous {
    Date date;
    Heure heure;
    Heure dure_rdv;
    char *objet;
    struct RendezVous *next;  // Champ pour lier les rendez-vous
} Rdv;
//----------------------------------------------------------------------
//AGENDA
typedef struct AgendaEntry {
    Contact *contact;
    Rdv *rendezvous_list;
    struct AgendaEntry *next;
} AgendaEntry;
//LISTE
typedef struct ListeContact {
    int max_level;
    AgendaEntry **next;
} ListeContact;

//----------------------------------------------------------------------
// Fonctions :
//Fonctions pour créer des contact,listcontact,agenda,RDV,Date et une heure
Contact *CreateContact(const char *nom, const char *prenom);
ListeContact CreateListeContact(int n);
AgendaEntry *CreateAgendaEntry();
Rdv CreateRDV(Date, Heure, Heure, char *);
Date CreateDate(int a, int j, int h);
Heure CreateHeure(int h, int m);

//----------------------------------------------------------------------
//fonction pour saisir un RDV
Rdv Saisir_RDV();

//----------------------------------------------------------------------
//Fonction pour rechercher un contact et pour ajouter un contact dans une liste et pour ajouter un rdv
void ContactResearch(ListeContact *liste_contact, const char *n, const char *p);
void AddContactToAgenda(ListeContact *liste_contact, const char *nom, const char *prenom);
void AddRDVToContact(ListeContact *liste_contact, const char *n, const char *p, Rdv RDV);

//----------------------------------------------------------------------
//Fonction pour supprimer un contact et un rdv
void RemoveRDVtoContact(ListeContact *liste_contact, const char *n, const char *p);
void RemoveContactFromContactList(ListeContact *liste_contact, const char *n, const char *p);

//----------------------------------------------------------------------
//fonction pour saisir un chaine de caractere
char *scanString(void);

//----------------------------------------------------------------------
//fonction pour afficher
void DisplayListeContact(ListeContact *liste_contact);
void Display_RDV(ListeContact *l, const char *n, const char *p);

//----------------------------------------------------------------------
//fonction bonus
void Create_Contacts_From_Files(ListeContact *liste_contact);
void Save_RDV_In_File(ListeContact *liste_contact,const char *n, const char *p);
void Print_RDV();
#endif //PROJET_V1_CONTACT_H