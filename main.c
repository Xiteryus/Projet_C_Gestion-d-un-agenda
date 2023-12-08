#include <stdio.h>
#include "Menu.h"
int main() {
    Menu();
    //Create_List();

    // Créer une liste de contacts
    /*ListeContact liste_contact = CreateListeContact(1);
    Create_Contacts_From_Files(&liste_contact);


    // Menu
    int choix;
    do {
        printf("\nMenu:\n");
        printf("1. Rechercher un contact\n");
        printf("2. Afficher les rendez-vous d'un contact\n");
        printf("3. Creer un contact\n");
        printf("4. Creer un rendez-vous pour un contact\n");
        printf("5. Pour afficher la liste des contacts\n");
        printf("6. Sauvegarder RDV\n");
        printf("0. Quitter\n");

        printf("Votre choix : ");
        scanf("%d", &choix);
        getchar();

        switch (choix) {
            case 1:
                printf("Entrez le nom du contact : ");
                char *nomRecherche = scanString();
                printf("Entrez le prenom du contact : ");
                char *PrenomRecherche = scanString();
                ContactResearch(&liste_contact, nomRecherche, PrenomRecherche);
                break;

            case 2:
                printf("Entrez le nom du contact : ");
                char *nomAffichage = scanString();
                printf("Entrez le prenom du contact : ");
                char *prenomAffiche = scanString();
                Display_RDV(&liste_contact, nomAffichage,prenomAffiche);

                break;

            case 3:
                printf("Entrez le nom du nouveau contact : ");
                char *nomNouveauContact = scanString();
                printf("Entrez le prénom du nouveau contact : ");
                char *prenomNouveauContact = scanString();
                AddContactToAgenda(&liste_contact, nomNouveauContact, prenomNouveauContact);
                break;

            case 4:
                printf("Entrez le nom du nouveau contact : ");
                char *nomNouveau1Contact = scanString();
                printf("Entrez le prénom du nouveau contact : ");
                char *prenomNouveau1Contact = scanString();
                char *n = scanString();
                //Rdv rdv = CreateRDV(CreateDate(2005,6,8), CreateHeure(2,50),CreateHeure(5,50), n) ;
                AddRDVToContact(&liste_contact,nomNouveau1Contact,prenomNouveau1Contact,Saisir_RDV());
                break;

            case 5:
                // Afficher tous les contacts
                DisplayListeContact(&liste_contact);
                break;

            case 6:
                printf("Entrez le nom du contact : ");
                char *nom = scanString();
                printf("Entrez le prenom du contact : ");
                char *prenom = scanString();
                FILE *f = fopen("C:\\Users\\samue\\CLionProjects\\Projet_v1\\Sauvegarde_RDV.txt", "a");
                Save_RDV_In_File(&liste_contact, nom, prenom);
                fclose(f);
                break;

            case 0:
                // Quitter le programme
                printf("Programme terminé.\n");
                break;

            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }

    } while (choix != 0);*/



    /*agenda A = {NULL};
    Create_Contacts_From_Files(&A,1000);
    Display_Contact(&A);
    int val,lev;
    //Create_List();*/
    /*char *chaine;
    int i=0;
    chaine = scanString();
    PrintString(chaine);*/
    /*agenda A = {NULL} ;
    Add_Contact_To_Agenda(&A, "fff", "prnom1e");
    Add_Contact_To_Agenda(&A, "gdfgre", "prnom2e");
    Add_Contact_To_Agenda(&A, "Mael", "prnom3e");
    Display_Contact(&A);
    Contact_Research(&A,"Mael","prnom3e");*/


    /*printf("Liste 2 \n");

    t_d_list *test = create_list(5);

    t_d_cell *c1 = create_cell(1,0);
    t_d_cell *c2 = create_cell(2,1);
    t_d_cell *c3 = create_cell(3,0);
    t_d_cell *c4 = create_cell(4,2);
    t_d_cell *c5 = create_cell(5,0);
    t_d_cell *c6 = create_cell(6,1);
    t_d_cell *c7 = create_cell(7,3);
    t_d_cell *c8 = create_cell(8,0);
    t_d_cell *c9 = create_cell(9,1);
    t_d_cell *c10 = create_cell(10,0);
    t_d_cell *c11 = create_cell(12,2);
    t_d_cell *c12 = create_cell(13,0);
    t_d_cell *c13= create_cell(14,1);
    t_d_cell *c14 = create_cell(15,0);




    Insert_Cell_To_List(c1,test);
    Insert_Cell_To_List(c2,test);
    Insert_Cell_To_List(c3,test);
    Insert_Cell_To_List(c4,test);
    Insert_Cell_To_List(c5,test);
    Insert_Cell_To_List(c6,test);
    Insert_Cell_To_List(c7,test);
    Insert_Cell_To_List(c8,test);
    Insert_Cell_To_List(c9,test);
    Insert_Cell_To_List(c10,test);
    Insert_Cell_To_List(c11,test);
    Insert_Cell_To_List(c12,test);
    Insert_Cell_To_List(c13,test);
    Insert_Cell_To_List(c14,test);

    Display_List(test);*/

    return 0;
}
