#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int genererID() {
    srand(time(NULL));
    return rand() % 10000000000;
}
void afficherlist(){

}
void rechercherPatientParID(int id) {
    char nomPatient[50];
    char nomMaladie[50];
    char datePresence[20];

    FILE *fAllPatients = fopen("AllPatients.txt", "r");
    if (fAllPatients == NULL) {
        printf("Erreur lors de l'ouverture du fichier AllPatients.txt.\n");
        return;
    }

    int patientTrouve = 0;

    while (fscanf(fAllPatients, "Nom : %49s", nomPatient) == 1) {
        int idPatient;
        fscanf(fAllPatients, "ID du patient : %d", &idPatient);

        if (idPatient == id) {
            fscanf(fAllPatients, "%*[^\n]"); // Ignorer le reste de la ligne pour passer à la suivante
            fscanf(fAllPatients, "Nom de la maladie : %[^\n]", nomMaladie);
            fscanf(fAllPatients, "Date de présence : %19s", datePresence);

            printf("ID du patient : %d\n", idPatient);
            printf("Nom : %s\n", nomPatient);
            printf("Nom de la maladie : %s\n", nomMaladie);
            printf("Date de présence : %s\n", datePresence);
            printf("\n");

            patientTrouve = 1;
            break;
        }
    }

    if (!patientTrouve) {
        printf("Aucun patient avec l'ID %d n'a été trouvé.\n", id);
    }

    fclose(fAllPatients);
}

void rechercherPatientParNom(char *nom) {
    char nomPatient[50];
    char nomMaladie[50];
    char datePresence[20];

    FILE *fAllPatients = fopen("AllPatients.txt", "r");
    if (fAllPatients == NULL) {
        printf("Erreur lors de l'ouverture du fichier AllPatients.txt.\n");
        return;
    }

    int patientTrouve = 0;

    while (fscanf(fAllPatients, "Nom : %49s", nomPatient) == 1) {
        if (strcmp(nomPatient, nom) == 0) {
            fscanf(fAllPatients, "%*[^\n]"); // Ignorer le reste de la ligne pour passer à la suivante
            fscanf(fAllPatients, "Nom de la maladie : %[^\n]", nomMaladie);
            fscanf(fAllPatients, "Date de présence : %19s", datePresence);

            printf("Nom : %s\n", nomPatient);
            printf("Nom de la maladie : %s\n", nomMaladie);
            printf("Date de présence : %s\n", datePresence);
            printf("\n");

            patientTrouve = 1;
        }
    }

    if (!patientTrouve) {
        printf("Aucun patient avec le nom %s n'a été trouvé.\n", nom);
    }

    fclose(fAllPatients);
}

void rechercherPatientParMaladie(char *maladie) {
    char nomPatient[50];
    char nomMaladie[50];
    char datePresence[20];

    FILE *fAllPatients = fopen("AllPatients.txt", "r");
    if (fAllPatients == NULL) {
        printf("Erreur lors de l'ouverture du fichier AllPatients.txt.\n");
        return;
    }

    int patientTrouve = 0;

    while (fscanf(fAllPatients, "Nom : %49s", nomPatient) == 1) {
        fscanf(fAllPatients, "%*[^\n]"); // Ignorer le reste de la ligne pour passer à la suivante
        fscanf(fAllPatients, "Nom de la maladie : %[^\n]", nomMaladie);
        fscanf(fAllPatients, "Date de présence : %19s", datePresence);

        if (strcmp(nomMaladie, maladie) == 0) {
            printf("Nom : %s\n", nomPatient);
            printf("Nom de la maladie : %s\n", nomMaladie);
            printf("Date de présence : %s\n", datePresence);
            printf("\n");

            patientTrouve = 1;
        }
    }

    if (!patientTrouve) {
        printf("Aucun patient avec la maladie %s n'a été trouvé.\n", maladie);
    }

    fclose(fAllPatients);
}

void supprimerDossierPatient(char *nom) {
    char cheminDossier[100] = "./";
    strcat(cheminDossier, nom);

    char commandeSuppression[100];
    sprintf(commandeSuppression, "rm -rf %s", cheminDossier);

    int statut = system(commandeSuppression);

    if (statut != 0) {
        printf("Erreur lors de la suppression du dossier du patient %s.\n", nom);
    } else {
        printf("Dossier du patient %s supprimé avec succès.\n", nom);
    }
}
int AjouterP() {
    char nomPatient[50];
    char medecinTraitant[50];
    char sexe[10];
    int age;
    char adresse[100];
    char nomMaladie[50];
    int niveauUrgence;
    int idPatient;


    printf("Entrez le nom du patient : ");
    scanf("%49s",&nomPatient);




    printf("Entrez le sexe du patient : ");
    scanf("%9s",&sexe);


 printf("Entrez l'adresse du patient : ");
 scanf("%99s",adresse);


printf("Entrez le nom de la maladie : ");
scanf("%49s",&nomMaladie);

    printf("Entrez l'âge du patient : ");
    scanf("%d", &age);
    getchar();

    printf("Niveau d'urgence (1 niveau très urgent, 2 niveau urgen,  3 niveau modéré, 4 niveau faible, 5 niveau très faible) : ");
    scanf("%d", &niveauUrgence);
    getchar();

    idPatient = genererID();
    FILE *fichier;
    fichier = fopen("listes.txt", "w");

    if (fichier == NULL) {
        printf("Erreur lors de la création du fichier.\n");
        return 1;
    }
    fprintf(fichier, "ID du patient : %d\n", idPatient);
    fprintf(fichier, "NOM du patient : %s\n", nomPatient);
    fprintf(fichier, "Sexe : %s\n", sexe);
    fprintf(fichier, "Âge : %d\n", age);
    fprintf(fichier, "Adresse : %s\n", adresse);
    fprintf(fichier, "Nom de la maladie : %s\n", nomMaladie);
    fclose(fichier);

    char cheminDossier[100] = "./";
    strcat(cheminDossier, nomPatient);

    int statut = mkdir(cheminDossier, 0700);
    if (statut == -1) {
        printf("Erreur lors de la création du dossier.\n");
        return 1;
    }

    char fichierID[100];
    sprintf(fichierID, "%s/ID_%d.txt", cheminDossier, idPatient);
    FILE *fID = fopen(fichierID, "w");
    if (fID == NULL) {
        printf("Erreur lors de la création du fichier ID_%d.txt.\n", idPatient);
        return 1;
    }
    fprintf(fID, "ID du patient : %d\n", idPatient);
    fprintf(fID, "NOM du patient : %s\n", nomPatient);
    fclose(fID);

    char fichierPatient[100];
    sprintf(fichierPatient, "%s/Inf_%s.txt", cheminDossier, nomPatient);
    FILE *fPatient = fopen(fichierPatient, "w");
    if (fPatient == NULL) {
        printf("Erreur lors de la création du fichier Informations_%s.txt.\n", nomPatient);
        return 1;
    }
    fprintf(fPatient, "Nom : %s\n", nomPatient);
    fprintf(fPatient, "Sexe : %s\n", sexe);
    fprintf(fPatient, "Âge : %d\n", age);
    fprintf(fPatient, "Adresse : %s\n", adresse);
    fprintf(fPatient, "Nom de la maladie : %s\n", nomMaladie);

    switch (niveauUrgence) {
        case 1:
            fprintf(fPatient, "Type d'urgence : niveau très urgent\n");
            break;
        case 2:
            fprintf(fPatient, "Type d'urgence : niveau urgen\n");
            break;
        case 3:
            fprintf(fPatient, "Type d'urgence : niveau modéré\n");
            break;
        case 4:
            fprintf(fPatient, "Type d'urgence : niveau faible\n");
            break;
        case 5:
            fprintf(fPatient, "Type d'urgence : niveau très faible\n");
            break;
        default:
            fprintf(fPatient, "Type d'urgence : Inconnu\n");
            break;
    }

    fclose(fPatient);
 char fichierMladie[100];
    sprintf(fichierMladie, "%s/malad_%s.txt", cheminDossier, nomMaladie);
    FILE *fMALAD = fopen(fichierMladie, "w");
    if (fMALAD == NULL) {
        printf("Erreur lors de la création du fichier ID_%d.txt.\n", idPatient);
        return 1;
    }
    fprintf(fMALAD, "ID du patient : %d\n", idPatient);
    fprintf(fMALAD, "NOM du patient : %s\n", nomPatient);
    fprintf(fMALAD, "NOM du patient : %s\n", nomMaladie);
    fclose(fMALAD);
    // Create or open the file for storing the information of all patients
    FILE *fAllPatients = fopen("AllPatients.txt", "a");
    if (fAllPatients == NULL) {
        printf("Erreur lors de l'ouverture du fichier AllPatients.txt.\n");
        return 1;
    }
    fprintf(fAllPatients, "Nom : %s\n", nomPatient);
    fprintf(fAllPatients, "Nom de la maladie : %s\n", nomMaladie);
    time_t tempsActuel;
    struct tm *tempsInfo;
    char datePresence[20];
    time(&tempsActuel);
    tempsInfo = localtime(&tempsActuel);
    strftime(datePresence, sizeof(datePresence), "%Y-%m-%d", tempsInfo);
    fprintf(fAllPatients, "Date de présence : %s\n\n", datePresence);

    fclose(fAllPatients);

    printf("Dossier créé avec succès.\n");

    return 0;
}


void afficherMenu() {
    system("CLS");
    printf("===== MENU =====\n");
    printf("1. Ajouter un patient\n");
    printf("2. Rechercher un patient \n");
    printf("3. Supprimer le dossier d'un patient\n");
    printf("4.liste des patients\n");
    printf("0. Quitter\n");
    printf("================\n");
    printf("Votre choix : ");
}
void afficherrecherche (){
    system("CLS");
    printf("======rechercher======\n");
    printf("11.Rechercher un patient par id\n");
    printf("21.Rechercher un patient par nom\n");
    printf("31.Rechercher un patient par le nom de maladie\n");
    printf("0.retouner\n");
    printf("=======================\n");
    printf("votre choix :");}
int main() {
system("color F4");
    int choix;

    do {
        afficherMenu();
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                AjouterP();
                break;

           case 2: {
                 afficherrecherche();
                 scanf("%d", &choix);
                case 11:{  int id;
                printf("Entrez l'ID du patient : ");
                scanf("%d", &id);
                rechercherPatientParID(id);
                break;}
                case 21:{char nom[50];
                printf("Entrez le nom du patient : ");
                scanf("%49s", nom);
                rechercherPatientParNom(nom);
                break;
            }
            case 31:{char maladie[50];
                printf("Entrez le nom de la maladie : ");
                scanf("%49s", maladie);
                rechercherPatientParMaladie(maladie);
                break;
            }

            break;
            }
            case 3: {
                char nom[50];
                printf("Entrez le nom du patient dont vous voulez supprimer le dossier : ");
                scanf("%s",&nom);
                supprimerDossierPatient(nom);}
                break;
              case 4: {
                 char ligne[10000];//rani create wahde  fichier jdide kayne f fonction ajoute de pation compiler ba3da 3adafheme

}
            case 0:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
                break;
        }

        printf("\n");

    } while (choix != 0);

    return 0;
}
