//
// Created by samue on 07/12/2023.
//

#include "Menu.h"

void Menu() {
    int x;
    do {
        printf("\n MENU \n");
        printf("1. Partie II\n");
        printf("2. Partie III\n");
        printf("0. Quitter\n");

        scanf("%d", &x);

        switch (x) {
            case 1:
                //afficher le menu II
                MenuII();
                break;


            case 2 :
                //afficher le menu III
                MenuIII();
                break;

            case 0:
                // Quitter le programme
                printf("Programme termine.\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }

    } while (x != 0);

}


void MenuII(){
    int y,x,rer,time;
    t_d_list *l = NULL;

    do {
        printf("\n MENU de la partie II \n");
        printf("1. Creer une liste\n");
        printf("2. Afficher la liste\n");
        printf("3. Recherche classique de valeur\n");
        printf("4. Recherche dichotomique de valeur\n");
        printf("5. Recherche classique de valeur aleatoire en calculant le temps\n");
        printf("6. Recherche dichotomique de valeur aleatoire en calculant le temps\n");
        printf("0. Retour MENU\n");

        printf("Votre choix : ");
        scanf("%d", &y);

        switch(y){
            case 1:
                //crée une liste à n niveaux
            printf("Entrez la valeur n : \n");
            scanf(" %d", &x);
            l =Create_List(x);
                break;
            case 2:
                //affiche la liste
                if (l==NULL)
                    break;
                printf("LISTE : \n");
                Display_List(l);
                break;
            case 3 :
                //Recherche classique de valeur
                if (l==NULL)
                    break;
                printf("Entrez la valeur a rechercher : \n");
                scanf(" %d", &rer);
                if ((Classic_Research(l,rer))==-1)
                    printf("Valeur Introuvable");
                else
                    printf("Position %d ", Classic_Research(l,rer));
                break;
            case 4:
                //Recherche Dichotomique de valeur
                if (l==NULL)
                    break;
                printf("Entrez la valeur a rechercher : \n");
                scanf(" %d", &rer);
                if(Dichotomy_Research(l,rer)==1)
                    printf("Valeur Trouvee");
                else
                    printf("Valeur Introuvable ");
                break;

            case 5:
                //Recherche classique pour un grand nombre de valeur
                if (l==NULL)
                    break;
                int t = pow(2,x)-1;
                printf("Nombre Iteration : \n");
                scanf(" %d", &time);
                startTimer();

                for(int i=0;i<time;i++) {
                    Classic_Research(l, rand() % t);
                }
                stopTimer();
                displayTime();
                break;

            case 6:
                //Recherche Dichotomique pour un grand nombre de valeur
                if (l==NULL)
                    break;
                t = pow(2,x)-1;
                printf("Nombre Iteration : \n");
                scanf(" %d", &time);
                startTimer();

                for(int i=0;i<time;i++) {
                    Dichotomy_Research(l, rand() % t);
                }
                stopTimer();
                displayTime();
                break;

            case 0:
            // Quitter le programme
                Menu();
                break;

        default:
            printf("Choix invalide. Veuillez réessayer.\n");
    }

} while (y != 0);

}

void MenuIII(){

    ListeContact liste_contact = CreateListeContact(1);
    //Fonction qui ne marche pas :
    //Create_Contacts_From_Files(&liste_contact);

    // Menu
    int choix;
    do {
        printf("\nMenu de la partie III:\n");
        printf("1. Rechercher un contact\n");
        printf("2. Afficher les rendez-vous d'un contact\n");
        printf("3. Creer un contact\n");
        printf("4. Creer un rendez-vous pour un contact\n");
        printf("5. Afficher la liste des contacts\n");
        printf("6. Sauvegarder RDV\n");
        printf("7. Lire sauvegarde RDV\n");
        printf("8. Supprimer un contact\n");
        printf("9. Supprimer un RDV d'un contact\n");

        printf("0. Retour MENU\n");

        printf("Votre choix : ");
        scanf("%d", &choix);
        getchar();

        switch (choix) {
            case 1:
                //Rechercher un contact, nous n'avons pas fait l'option bonus avec la completion automatique
                printf("Entrez le nom du contact : ");
                char *nomRecherche = scanString();
                printf("Entrez le prenom du contact : ");
                char *PrenomRecherche = scanString();
                ContactResearch(&liste_contact, nomRecherche, PrenomRecherche);
                break;

            case 2:
                //Afficher rdv d'un contact
                printf("Entrez le nom du contact : ");
                char *nomAffichage = scanString();
                printf("Entrez le prenom du contact : ");
                char *prenomAffiche = scanString();
                Display_RDV(&liste_contact, nomAffichage,prenomAffiche);

                break;

            case 3:
                //Crée un nouveau contact
                printf("Entrez le nom du nouveau contact : ");
                char *nomNouveauContact = scanString();
                printf("Entrez le prénom du nouveau contact : ");
                char *prenomNouveauContact = scanString();
                AddContactToAgenda(&liste_contact, nomNouveauContact, prenomNouveauContact);
                break;

            case 4:
                //Saisir un rdv pour un contact
                printf("Entrez le nom du nouveau contact : ");
                char *nomNouveau1Contact = scanString();
                printf("Entrez le prénom du nouveau contact : ");
                char *prenomNouveau1Contact = scanString();
                AddRDVToContact(&liste_contact,nomNouveau1Contact,prenomNouveau1Contact,Saisir_RDV());
                break;

            case 5:
                // Afficher tous les contacts
                DisplayListeContact(&liste_contact);
                break;

            case 6:
                //Sauvegarder les rdv d'un contact dans un fichier
                printf("Entrez le nom du contact : ");
                char *nom = scanString();
                printf("Entrez le prenom du contact : ");
                char *prenom = scanString();
                FILE *f = fopen("C:\\Users\\samue\\CLionProjects\\Projet_v1\\Sauvegarde_RDV.txt", "a");
                Save_RDV_In_File(&liste_contact, nom, prenom);
                fclose(f);
                break;

            case 7:
                Print_RDV();
                break;

            case 8:
                //Supprimer Contact
                printf("Entrez le nom du contact a supprimer : ");
                char *n = scanString();
                printf("Entrez le prenom du contact a supprimer : ");
                char *p = scanString();
                RemoveContactFromContactList(&liste_contact,n,p);
                break;
            case 9:
                //supprime 1er rdv d'un contact
                printf("Entrez le nom du contact a supprimer : ");
                char *n1 = scanString();
                printf("Entrez le prenom du contact a supprimer : ");
                char *p1 = scanString();
                RemoveRDVtoContact(&liste_contact,n1,p1);
                break;

            case 0:
                // Quitter le programme
                Menu();
                break;

            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }

    } while (choix != 0);

}
