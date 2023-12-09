//
// Created by samue on 03/12/2023.
//
#include "Contact.h"

Contact *CreateContact(const char *nom, const char *prenom) {
    Contact *c = (Contact *)malloc(sizeof(Contact));// Alloue de la mémoire pour la structure Contact

    if (c != NULL) {
        c->nom = strdup(nom); //'strdup' pour copier la chaine de caractere
        c->prenom = strdup(prenom);
    }

    return c;//retourne un contact
}

ListeContact CreateListeContact(int n) {
    ListeContact l;
    l.max_level = n;
    l.next = (AgendaEntry **)malloc(sizeof(AgendaEntry *) * n);
    return l;
}

AgendaEntry *CreateAgendaEntry() {
    AgendaEntry *a = (AgendaEntry *)malloc(sizeof(AgendaEntry));// Alloue de la mémoire pour la structure Agenda

    a->contact = NULL;
    a->rendezvous_list = NULL;
    a->next = NULL;

    return a;
}

Rdv CreateRDV(Date d, Heure h_rdv, Heure dure, char *obj) {
    Rdv *r = (Rdv *)malloc(sizeof(Rdv));// Alloue de la mémoire pour la structure RDV

    r->date = d;
    r->heure = h_rdv;
    r->dure_rdv = dure;
    r->objet = strdup(obj);

    return *r;//retourne l'adresse du rdv
}

Date CreateDate(int a, int m, int j) {
    Date *d = (Date *)malloc(sizeof(Date));// Alloue de la mémoire pour la structure Date

    d->annee = a;
    d->jour = j;
    d->mois = m;

    return *d;//retourne l'adresse d'une date
}

Heure CreateHeure(int h, int m) {
    Heure *her = (Heure *)malloc(sizeof(Heure));// Alloue de la mémoire pour la structure Heure

    her->heure = h;
    her->minute = m;

    return *her;//retourne l'adresse d'une heure
}

//----------------------------------------------------------------------
//fonction pour ajouter un contact dans un liste à contact
void AddContactToAgenda(ListeContact *liste_contact, const char *nom, const char *prenom) {
    Contact *c = CreateContact(nom, prenom);

    //transformation du nom en Minuscule pour trier
    char Nom_Min[strlen(nom) + 1];

    for (int i = 0; nom[i] != '\0'; i++) {
        if (nom[i] >= 'A' && nom[i] <= 'Z')
            Nom_Min[i] = nom[i] + 32;//utilisation du code ASCII
        else
            Nom_Min[i] = nom[i];
    }
    Nom_Min[strlen(nom)] = '\0';
    // trouver la bonne liste de contacts
    if (liste_contact->next == NULL) {
        // Si la liste de contacts n'existe pas, la créer et l'initialiser
        liste_contact->next = (AgendaEntry **) malloc(sizeof(AgendaEntry *));
        if (liste_contact->next == NULL) {
            free(Nom_Min);

            return;
        }

        liste_contact->max_level = 1;

        AgendaEntry *new_agenda = CreateAgendaEntry();
        new_agenda->contact = c;
        new_agenda->next = NULL;
        liste_contact->next[0] = new_agenda;
    } else {
        // Sinon, insérer le contact dans la liste triée
        if (strcmp(liste_contact->next[0]->contact->nom, Nom_Min) > 0) {
            AgendaEntry *new_agenda = CreateAgendaEntry();
            new_agenda->contact = c;
            new_agenda->next = liste_contact->next[0];
            liste_contact->next[0] = new_agenda;
        } else {
            AgendaEntry *temp = liste_contact->next[0];
            while (temp->next != NULL && strcmp(temp->next->contact->nom, Nom_Min) < 0) {
                temp = temp->next;
            }

            AgendaEntry *new_agenda = CreateAgendaEntry();
            new_agenda->contact = c;
            new_agenda->next = temp->next;
            temp->next = new_agenda;
        }

    }

}

void AddRDVToContact(ListeContact *liste_contact, const char *n, const char *p, Rdv RDV) {
    AgendaEntry *temp_agenda = liste_contact->next[0];

    while (temp_agenda != NULL) {//on parcourt la liste pour trouver le contact
        if (strcmp(temp_agenda->contact->nom, n) == 0 && strcmp(temp_agenda->contact->prenom, p) == 0) {
            Rdv *new_rdv = (Rdv *)malloc(sizeof(Rdv));
            *new_rdv = RDV;
            new_rdv->next = NULL;

            if (temp_agenda->rendezvous_list == NULL) {//si le contact n'a pas de rdv alors on l'inssert en tete
                temp_agenda->rendezvous_list = new_rdv;
            } else {
                Rdv *last_rdv = temp_agenda->rendezvous_list;
                while (last_rdv->next != NULL) {//si le contact à déja des rdv alors on parcourt pour insserer le rdv à la fin
                    last_rdv = last_rdv->next;
                }
                last_rdv->next = new_rdv;
            }
            return;
        }
        temp_agenda = temp_agenda->next;
    }
    //rappel des fonction si le contact n'est pas dans la liste
    AddContactToAgenda(liste_contact, n, p);
    AddRDVToContact(liste_contact, n, p, RDV);
}
//----------------------------------------------------------------------

void RemoveContactFromContactList(ListeContact *liste_contact, const char *n, const char *p) {

    AgendaEntry *current = liste_contact->next[0];
    AgendaEntry *prev = NULL;

    while (current != NULL) {//on parcourt la liste pour trouver le contact
        if (strcmp(current->contact->nom, n) == 0 && strcmp(current->contact->prenom, p) == 0) {
            // Contact trouvé, supprimer et réorganiser la liste
            if (prev == NULL) {
                liste_contact->next[0] = current->next;
            } else {
                prev->next = current->next;
            }

            free(current->contact->nom);//on free pour supprimer le nom, prenom et le contact
            free(current->contact->prenom);
            free(current->contact);
            free(current);
            return;
        }

        prev = current;
        current = current->next;
    }
    printf("Contact Introuvable\n");
}

void RemoveRDVtoContact(ListeContact *liste_contact, const char *n, const char *p) {

    // Recherche du contact dans la liste
    AgendaEntry *current = liste_contact->next[0];

    while (current != NULL) {//on parcourt la liste pour trouver le contact
        if (strcmp(current->contact->nom, n) == 0 && strcmp(current->contact->prenom, p) == 0) {
            // Contact trouvé, recherche du rendez-vous à supprimer
            Rdv *current_rdv = current->rendezvous_list;
            Rdv *prev_rdv = NULL;

            while (current_rdv != NULL) {
                // ici supprime le premier rdv d'un contact
                if (prev_rdv == NULL) {
                    current->rendezvous_list = current_rdv->next;
                } else {
                    prev_rdv->next = current_rdv->next;
                }

                free(current_rdv); // Libérer la mémoire du rendez-vous supprimé
                return;
            }
            prev_rdv = current_rdv;
            current_rdv = current_rdv->next;
        }
        current = current->next;
    }
    printf("Contact Introuvable\n");
}

//----------------------------------------------------------------------
//Fonction qui rechercher un contact
void ContactResearch(ListeContact *liste_contact, const char *n, const char *p) {
    AgendaEntry *temp_agenda = liste_contact->next[0];

    while (temp_agenda != NULL) {//on parcourt la liste pour trouver le contact
        if (strcmp(temp_agenda->contact->nom, n) == 0 && strcmp(temp_agenda->contact->prenom, p) == 0) {
            printf("Contact trouve dans la liste");//Si le contact est trouve
            return;
        }
        temp_agenda = temp_agenda->next;
    }

    printf("Contact Introuvable\n");//s'il est n'est pas trouve
}

//----------------------------------------------------------------------


//Fonction qui affiche les contacts
void DisplayListeContact(ListeContact *liste_contact) {
    printf("Liste des contacts :\n");

    for (int i = 0; i < liste_contact->max_level; i++) {
        AgendaEntry *temp_agenda = liste_contact->next[i];

        while (temp_agenda != NULL) {//On parcours la liste et on affiche tous les contacts
            printf("Nom : %s | Prenom : %s\n", temp_agenda->contact->nom, temp_agenda->contact->prenom);//On affiche le nom et le prenom du contact
            temp_agenda = temp_agenda->next;
        }
    }
}
//Fonction qui affiche les RDV pour les contacts
void Display_RDV(ListeContact *l, const char *n, const char *p) {
    AgendaEntry *temp_agenda = l->next[0];

    while (temp_agenda != NULL) {//on parcours la liste jusqu'a trouver le bon nom et le bon prenom
        if (strcmp(temp_agenda->contact->nom, n) == 0 && strcmp(temp_agenda->contact->prenom, p) == 0) {
            Rdv *temp_rdv = temp_agenda->rendezvous_list;
            //Puis on affiche le rdv
            while (temp_rdv != NULL) {//on affiche tous les rdv du contact
                printf("Date : %02d/%02d/%d\n", temp_rdv->date.jour, temp_rdv->date.mois, temp_rdv->date.annee);
                printf("Heure : %02d:%02d\n", temp_rdv->heure.heure, temp_rdv->heure.minute);
                printf("Duree du rendez-vous : %02d:%02d\n", temp_rdv->dure_rdv.heure, temp_rdv->dure_rdv.minute);
                printf("Objet : %s\n\n", temp_rdv->objet);
                temp_rdv = temp_rdv->next;
            }
            return;
        }
        temp_agenda = temp_agenda->next;
    }
    printf("Contact introuvable.\n");
}
//----------------------------------------------------------------------

//Fonction pour saisir une chaine de caractere
char *scanString(){
    int taille = 50,i=0;// on définit une taille maximale pour la chaîne
    char *c = (char*) (malloc(sizeof(char)*taille));// Alloue de la mémoire pour stocker la chaîne

    while (i<taille-1){
        scanf("%c",&c[i]);
        if (c[i]=='\n'){
            c[i] = '\0';
            break;
        }
        i++;
    }
    printf("\n");
    return c;
}


//----------------------------------------------------------------------
//Fonction pour saisir un RDV, on demande à l'utilisateur de saisir une date, une heure et un rdv
Rdv Saisir_RDV(){
    int a,m,j,he,min,h_rdv,min_rdv;
    printf("Inserer Annee du Rdv : ");
    scanf("%d",&a);
    printf("Inserer Mois du Rdv : ");
    scanf("%d",&m);
    printf("Inserer Jour du Rdv : ");
    scanf("%d",&j);
    Date d= CreateDate(a,m,j);
    printf("Inserer Heure du Rdv : ");
    scanf("%d",&he);
    printf("Inserer Minute du Rdv : ");
    scanf("%d",&min);
    Heure h= CreateHeure(he,min);
    printf("Inserer dure du Rdv en Heure : ");
    scanf("%d",&h_rdv);
    printf("Inserer dure du Rdv en minute : ");
    scanf("%d",&min_rdv);
    printf("Entrez objet du RDV en  : ");
    scanf("%d",&min_rdv);
    Heure dure= CreateHeure(h_rdv,min_rdv);
    char *objet = scanString();
    Rdv rdv = CreateRDV(d,h,dure,objet);
    return rdv;
}

//----------------------------------------------------------------------
//Fonction qui doit importer des contact depuis un fichier et les mettre dans une liste de contact
void Create_Contacts_From_Files(ListeContact *liste_contact) {

    FILE *fichier_nom = fopen("C:\\Users\\samue\\CLionProjects\\Projet_v1\\nom.txt", "r");//on ouvre les ficher avec uniquement le mode lecture
    FILE *fichier_prenom = fopen("C:\\Users\\samue\\CLionProjects\\Projet_v1\\Prenom.txt", "r");


    char nom[100];
    char prenom[100];
    int compteur = 0;

    while (compteur < 1000 && fscanf(fichier_nom, "%s", nom) == 1 && fscanf(fichier_prenom, "%s", prenom) == 1) {
        //on arrive à extraire les nom et prenom du fichier
        printf("Nom : %s, Prenom : %s\n", nom, prenom);
        //mais l'appel de la fonction qui ne marche pas
        AddContactToAgenda(liste_contact, nom, prenom);


        compteur++;
    }

    fclose(fichier_nom);//on ferme les fichiers
    fclose(fichier_prenom);
}
//Fonction qui enregistre un RDV de contact
void Save_RDV_In_File(ListeContact *liste_contact, const char *n, const char *p) {
    FILE *file = fopen("C:\\Users\\samue\\CLionProjects\\Projet_v1\\Sauvegarde_RDV.txt", "a");//on ouvre les fichier en mode append, c'est a dire qu'on peut ecrire sur le ficher et cela ne supprimera pas ce qu'il y a deja la

    if (file == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }
    AgendaEntry *temp_agenda = liste_contact->next[0];

    while (temp_agenda != NULL) {//on parcours la liste jusqu'a trouver le bon nom et le bon prenom
        if (strcmp(temp_agenda->contact->nom, n) == 0 && strcmp(temp_agenda->contact->prenom, p) == 0) {
            Rdv *temp_rdv = temp_agenda->rendezvous_list;

            while (temp_rdv != NULL) {
                // Écriture des détails du rendez-vous dans le fichier
                fprintf(file,"Nom %s | Prenom %s \n",n,p);
                fprintf(file, "Date : %02d/%02d/%d\n", temp_rdv->date.jour, temp_rdv->date.mois, temp_rdv->date.annee);
                fprintf(file, "Heure : %02d:%02d\n", temp_rdv->heure.heure, temp_rdv->heure.minute);
                fprintf(file, "Duree du rendez-vous : %02d:%02d\n", temp_rdv->dure_rdv.heure, temp_rdv->dure_rdv.minute);
                fprintf(file, "Objet : %s\n\n", temp_rdv->objet);
                temp_rdv = temp_rdv->next;
            }
            break; // Quitter la boucle si le contact est trouvé
        }
        temp_agenda = temp_agenda->next;
    }

    fclose(file);//on ferme le fichier
}
//Fonction qui affiche tous les RDV sauvegarde
void Print_RDV(){
    FILE *file = fopen("C:\\Users\\samue\\CLionProjects\\Projet_v1\\Sauvegarde_RDV.txt", "r");
    int lettre = 0;
    if(file==NULL){//on regarde si le fichier est nul
        printf("Fichier NULL");
        return;
    }
    while(1){//boucle infinie

        lettre = fgetc(file); //lire caractere

        if(feof(file))//Condition d'arreter pour la boucle
            break;

        printf("%c",lettre);//affiche lettre par lettre le fichier

    }

}

