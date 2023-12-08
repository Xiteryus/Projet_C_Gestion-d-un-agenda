//
// Created by samue on 03/12/2023.
//
#include "Contact.h"

Contact *CreateContact(const char *nom, const char *prenom) {
    Contact *c = (Contact *)malloc(sizeof(Contact));

    if (c != NULL) {
        c->nom = strdup(nom);
        c->prenom = strdup(prenom);
    }

    return c;
}

ListeContact CreateListeContact(int n) {
    ListeContact l;
    l.max_level = n;
    l.next = (AgendaEntry **)malloc(sizeof(AgendaEntry *) * n);
    return l;
}

AgendaEntry *CreateAgendaEntry() {
    AgendaEntry *a = (AgendaEntry *)malloc(sizeof(AgendaEntry));

    a->contact = NULL;
    a->rendezvous_list = NULL;
    a->next = NULL;

    return a;
}

Rdv CreateRDV(Date d, Heure h_rdv, Heure dure, char *obj) {
    Rdv *r = (Rdv *)malloc(sizeof(Rdv));

    r->date = d;
    r->heure = h_rdv;
    r->dure_rdv = dure;
    r->objet = strdup(obj);

    return *r;
}

Date CreateDate(int a, int m, int j) {
    Date *d = (Date *)malloc(sizeof(Date));

    d->annee = a;
    d->jour = j;
    d->mois = m;

    return *d;
}

Heure CreateHeure(int h, int m) {
    Heure *her = (Heure *)malloc(sizeof(Heure));

    her->heure = h;
    her->minute = m;

    return *her;
}

//----------------------------------------------------------------------

void AddContactToAgenda(ListeContact *liste_contact, const char *nom, const char *prenom) {
    Contact *c = CreateContact(nom, prenom);


    char Nom_Min[strlen(nom) + 1];

    for (int i = 0; nom[i] != '\0'; i++) {
        if (nom[i] >= 'A' && nom[i] <= 'Z')
            Nom_Min[i] = nom[i] + 32;
        else
            Nom_Min[i] = nom[i];
    }
    // Trouver la bonne liste de contacts
    if (liste_contact->next == NULL) {
        // Si la liste de contacts n'existe pas, la créer et l'initialiser
        liste_contact->next = (AgendaEntry **) malloc(sizeof(AgendaEntry *));
        if (liste_contact->next == NULL) {
            // Gérer l'échec de l'allocation mémoire si nécessaire
            free(Nom_Min);

            return;
        }

        liste_contact->max_level = 1;

        AgendaEntry *new_agenda = CreateAgendaEntry();
        new_agenda->contact = c;
        new_agenda->next = NULL; // Initialisation du champ next
        liste_contact->next[0] = new_agenda;
    } else {
        // Sinon, insérer le contact dans la liste triée
        if (strcasecmp(liste_contact->next[0]->contact->nom, Nom_Min) > 0) {
            AgendaEntry *new_agenda = CreateAgendaEntry();
            new_agenda->contact = c;
            new_agenda->next = liste_contact->next[0];
            liste_contact->next[0] = new_agenda;
        } else {
            AgendaEntry *temp = liste_contact->next[0];
            while (temp->next != NULL && strcasecmp(temp->next->contact->nom, Nom_Min) < 0) {
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

    while (temp_agenda != NULL) {
        if (strcmp(temp_agenda->contact->nom, n) == 0 && strcmp(temp_agenda->contact->prenom, p) == 0) {
            Rdv *new_rdv = (Rdv *)malloc(sizeof(Rdv));
            *new_rdv = RDV;
            new_rdv->next = NULL;

            if (temp_agenda->rendezvous_list == NULL) {
                temp_agenda->rendezvous_list = new_rdv;
            } else {
                Rdv *last_rdv = temp_agenda->rendezvous_list;
                while (last_rdv->next != NULL) {
                    last_rdv = last_rdv->next;
                }
                last_rdv->next = new_rdv;
            }
            return;
        }
        temp_agenda = temp_agenda->next;
    }

    AddContactToAgenda(liste_contact, n, p);
    AddRDVToContact(liste_contact, n, p, RDV);
}

//----------------------------------------------------------------------

void ContactResearch(ListeContact *liste_contact, const char *n, const char *p) {
    AgendaEntry *temp_agenda = liste_contact->next[0];

    while (temp_agenda != NULL) {
        if (strcmp(temp_agenda->contact->nom, n) == 0 && strcmp(temp_agenda->contact->prenom, p) == 0) {
            printf("Contact trouve dans la liste");
            return;
        }
        temp_agenda = temp_agenda->next;
    }

    printf("Contact pas trouve");
}

//----------------------------------------------------------------------

void DisplayContact(ListeContact *liste_contact) {
    AgendaEntry *temp_agenda = liste_contact->next[0];

    printf("Liste des contacts dans la liste :\n");
    while (temp_agenda != NULL) {
        printf("Nom : %s | Prenom : %s\n", temp_agenda->contact->nom, temp_agenda->contact->prenom);
        temp_agenda = temp_agenda->next;
    }
}
void DisplayListeContact(ListeContact *liste_contact) {
    printf("Liste des contacts :\n");

    for (int i = 0; i < liste_contact->max_level; i++) {
        AgendaEntry *temp_agenda = liste_contact->next[i];

        while (temp_agenda != NULL) {
            printf("Nom : %s | Prenom : %s\n", temp_agenda->contact->nom, temp_agenda->contact->prenom);
            temp_agenda = temp_agenda->next;
        }
    }
}

void Display_RDV(ListeContact *l, const char *n, const char *p) {
    AgendaEntry *temp_agenda = l->next[0];

    while (temp_agenda != NULL) {
        if (strcmp(temp_agenda->contact->nom, n) == 0 && strcmp(temp_agenda->contact->prenom, p) == 0) {
            Rdv *temp_rdv = temp_agenda->rendezvous_list;

            while (temp_rdv != NULL) {
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


char *scanString(){
    int taille = 50,i=0;
    char *c = (char*) (malloc(sizeof(char)*taille));

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


void *PrintString(char *c){
    int i = 0;
    while(c[i]!='\n'){
        printf("%c",c[i]);
        i++;
    }
}

//----------------------------------------------------------------------

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
    printf("Entrez l'objet du RDV en Min : ");
    scanf("%d",&min_rdv);
    Heure dure= CreateHeure(h_rdv,min_rdv);
    char *objet = scanString();
    Rdv rdv = CreateRDV(d,h,dure,objet);
    return rdv;
}

//----------------------------------------------------------------------

void Create_Contacts_From_Files(ListeContact *liste_contact) {

    FILE *fichier_nom = fopen("C:\\Users\\samue\\CLionProjects\\Projet_v1\\nom.txt", "r");
    FILE *fichier_prenom = fopen("C:\\Users\\samue\\CLionProjects\\Projet_v1\\Prenom.txt", "r");


    char nom[100]; // Taille arbitraire pour le nom
    char prenom[100]; // Taille arbitraire pour le prénom
    int compteur = 0;

    while (compteur < 1000 && fscanf(fichier_nom, "%s", nom) == 1 && fscanf(fichier_prenom, "%s", prenom) == 1) {
        printf("Nom : %s, Prenom : %s\n", nom, prenom);
        AddContactToAgenda(liste_contact, nom, prenom);


        compteur++;
    }

    fclose(fichier_nom);
    fclose(fichier_prenom);
}

void Save_RDV_In_File(ListeContact *liste_contact, const char *n, const char *p) {
    FILE *file = fopen("C:\\Users\\samue\\CLionProjects\\Projet_v1\\Sauvegarde_RDV.txt", "a");

    if (file == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }
    AgendaEntry *temp_agenda = liste_contact->next[0];

    while (temp_agenda != NULL) {
        if (strcmp(temp_agenda->contact->nom, n) == 0 && strcmp(temp_agenda->contact->prenom, p) == 0) {
            Rdv *temp_rdv = temp_agenda->rendezvous_list;

            while (temp_rdv != NULL) {
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

    fclose(file);
}