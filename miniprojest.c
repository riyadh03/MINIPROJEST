#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int genererID() {
    srand(time(NULL));
    return rand() % 10000000000;
}
void afficherlist() {
    triedesPatients();

    FILE* fAllPatients = fopen("AllPatients.txt", "r");
    if (fAllPatients == NULL) {
        printf("Erreur lors de l'ouverture du fichier AllPatients.txt.\n");
        return;
    }

    char ligne[1000];

    while (fgets(ligne, sizeof(ligne), fAllPatients) != NULL) {
        printf("%s", ligne);
    }

    fclose(fAllPatients);
}

void triedesPatients() {

    FILE* fAllPatients = fopen("AllPatients.txt", "r+");
    if (fAllPatients == NULL) {
        printf("Erreur lors de l'ouverture du fichier AllPatients.txt.\n");
        return;
    }

    char ligne[1000];
    char records[1000][1000];
    int recordCount = 0;

    while (fgets(ligne, sizeof(ligne), fAllPatients) != NULL) {
        strcpy(records[recordCount], ligne);
        recordCount++;
    }


    int i, j;
    char temp[1000];

    for (i = 0; i < recordCount - 1; i++) {
        for (j = 0; j < recordCount - i - 1; j++) {
            char name1[50], name2[50];
            sscanf(records[j], "Nom : %s", name1);
            sscanf(records[j + 1], "Nom : %s", name2);

            if (strcmp(name1, name2) > 0) {
                strcpy(temp, records[j]);
                strcpy(records[j], records[j + 1]);
                strcpy(records[j + 1], temp);
            }
        }
    }


    fseek(fAllPatients, 0, SEEK_SET);

    for (i = 0; i < recordCount; i++) {
        fputs(records[i], fAllPatients);
    }

    fclose(fAllPatients);
}
void recherche1(char* nomE){





    FILE* fAllPatients = fopen("AllPatients.txt", "r");
    if (fAllPatients == NULL) {
        printf("Erreur lors de l'ouverture du fichier AllPatients.txt.\n");
        return;
    }

    char ligne[100];
    int patientTrouve = 0;

    while (fgets(ligne, sizeof(ligne), fAllPatients) != NULL) {
        if (strstr(ligne, nomE) != NULL) {
            printf("\n%s", ligne);
            patientTrouve = 1;
        }
    }

    if (!patientTrouve) {
        printf("Le patient n'a pas été trouvé.\n");
    }

    fclose(fAllPatients);




    }





void recherche0(char * nomE0){






     FILE* fAllPatients = fopen("AllPatients.txt", "r");
    if (fAllPatients == NULL) {
        printf("Erreur lors de l'ouverture du fichier AllPatients.txt.\n");
        return;
    }

    char ligne[100];
    int patientTrouve = 0;

    while (fgets(ligne, sizeof(ligne), fAllPatients) != NULL) {
        if (strstr(ligne, nomE0) != NULL) {
            printf("\n%s", ligne);
            patientTrouve = 1;
        }
    }

    if (!patientTrouve) {
        printf("Le patient n'a pas été trouvé.\n");
    }

    fclose(fAllPatients);

}


void afficherpatient(){
printf("======editer======\n");
    printf("21.ajouter un patient\n");
    printf("22.modifier un patient\n");
    printf("23.retouner\n");
    printf("=======================\n");
    printf("votre choix :");}
void supprimerDossierPatient(char* nom) {
    char cheminDossier[100] = "/home/shark/Music/";
    strcat(cheminDossier, nom);

    char commandeSuppression[100];
    sprintf(commandeSuppression, "rm -rf %s", cheminDossier);

    int statut = system(commandeSuppression);

    if (statut != 0) {
        printf("Erreur lors de la suppression du dossier du patient %s.\n", nom);
    } else {
        printf("Dossier du patient %s supprimé avec succès.\n", nom);

        // Remove patient's information from AllPatients.txt
        FILE* fAllPatients = fopen("AllPatients.txt", "r");
        FILE* fTemp = fopen("temp.txt", "w");

        if (fAllPatients == NULL || fTemp == NULL) {
            printf("Erreur lors de l'ouverture des fichiers.\n");
            return;
        }

        char ligne[1000];

        while (fgets(ligne, sizeof(ligne), fAllPatients) != NULL) {
            if (strstr(ligne, nom) == NULL) {
                fputs(ligne, fTemp);
            }
        }

        fclose(fAllPatients);
        fclose(fTemp);

        remove("AllPatients.txt");
        rename("temp.txt", "AllPatients.txt");
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

    int c=0;//compteur pour generer 1 id seulement pour un 1 dossier
    printf("Entrez le nom du patient : ");
    scanf("%49s",&nomPatient);




    printf("Entrez le sexe du patient : ");
    scanf("%9s",&sexe);


 printf("Entrez l'adresse du patient : ");
 scanf("%99s",&adresse);


printf("Entrez le nom de la maladie : ");
scanf("%49s",&nomMaladie);

    printf("Entrez l'âge du patient : ");
    scanf("%d", &age);
    getchar();

    printf("Niveau d'urgence (1 urgent,  2 niveau moyen , 3 niveau faible) : ");
    scanf("%d", &niveauUrgence);
    getchar();

    idPatient = genererID();

    FILE *fichier;
    fichier = fopen("listes.txt", "w");

    if (fichier == NULL) {
        printf("Erreur lors de la création du fichier.\n");
        return 1;
    }
    fprintf(fichier, "ID du patient : \n%d", idPatient);
    fprintf(fichier, "NOM du patient : \n%s", nomPatient);
    fprintf(fichier, "Sexe : \n%s", sexe);
    fprintf(fichier, "Âge : \n%d", age);
    fprintf(fichier, "Adresse : \n%s", adresse);
    fprintf(fichier, "Nom de la maladie : \n%s", nomMaladie);
    fclose(fichier);

    char cheminDossier[100] = "./";
    strcat(cheminDossier, nomPatient);

    int statut = mkdir(cheminDossier, 0700);
    if (statut == -1) {

        printf("le patient et deja existe ajouter la nouvelle maladie\n");
        char fichierMladie[100];
    sprintf(fichierMladie, "%s/malad_%s.txt", cheminDossier, nomMaladie);
    c++;
    FILE *fMALAD = fopen(fichierMladie, "w");
    if (fMALAD == NULL) {
        printf("Erreur lors de la création du fichier ID_%d.txt.\n", idPatient);
        return 1;

    }
    fprintf(fMALAD, "NOM du patient : %s\n", nomPatient);
    fprintf(fMALAD, "NOM du patient : %s\n", nomMaladie);
    fclose(fMALAD);
    }
if(c==0){
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
}
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
    fprintf(fPatient, "maladie : %s\n",nomMaladie);


    switch (niveauUrgence) {
        case 1:
            fprintf(fPatient, "Type d'urgence : niveau très urgent\n");
            break;
        case 2:
            fprintf(fPatient, "Type d'urgence : niveau urgent\n");
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

    fprintf(fMALAD, "NOM du patient : %s\n", nomPatient);
    fprintf(fMALAD, "NOM du patient : %s\n", nomMaladie);
    fclose(fMALAD);
    FILE* fAllPatients = fopen("AllPatients.txt", "a");
    if (fAllPatients == NULL) {
        printf("Erreur lors de l'ouverture du fichier AllPatients.txt.\n");
        return 1;
    }
    fprintf(fAllPatients, "\nNom : %s\t", nomPatient);
    fprintf(fAllPatients, "Nom de la maladie : %s\t", nomMaladie);
    time_t tempsActuel;
    struct tm* tempsInfo;
    char datePresence[20];
    time(&tempsActuel);
    tempsInfo = localtime(&tempsActuel);
    strftime(datePresence, sizeof(datePresence), "%Y-%m-%d", tempsInfo);
    fprintf(fAllPatients, "Date de présence : %s\t", datePresence);

    fclose(fAllPatients);

    printf("Créé avec succès.\n");

    return 0;

}
void afficherMenu() {

    printf("===== MENU =====\n");
    printf("1. Editer un patient\n");
    printf("2. Rechercher un patient \n");
    printf("3. Supprimer le dossier d'un patient\n");
    printf("4.liste des patients\n");
    printf("5.statistique\n");

    printf("0. Quitter\n");
    printf("================\n");
    printf("Votre choix : ");
}
void afficherrecherche (){

    printf("======rechercher======\n");
    printf("11.Rechercher un patient par nom\n");
    printf("21.Rechercher un patient par le nom de maladie\n");
    printf("31.retouner\n");
    printf("=======================\n");
    printf("votre choix :");}
int main () {
int comPA=0,comPMA=0;
    int choix;

    do {
        afficherMenu();
        scanf("%d", &choix);

        switch (choix) {
            case 1: {
                afficherpatient();
                 scanf("%d", &choix);

                 if (choix==21){AjouterP();comPA++;comPMA++;break;}
                 if (choix==22){
                 printf("pour modifier un patient taper le meme nom du patient\n");

                 AjouterP();
                 break;}
                 break;
                 }
           case 2: {
                 afficherrecherche();
                 scanf("%d", &choix);


               if(choix==11){char nomE[50];
                printf("Entrez le nom du patient : ");
                scanf("%49s",nomE);
                recherche1(nomE);

            }
            if(choix==21){char nomE0[50];
                printf("Entrez le nom de la maladie : ");
                scanf("%49s", nomE0);
                recherche0(nomE0);

            }
             if(choix==31){break;}
            break;
            }
            case 3: {
                char nomE[50];
                printf("Entrez le nom du patient dont vous voulez supprimer le dossier : ");
                scanf("%s",&nomE);
                supprimerDossierPatient(nomE);}
                break;
              case 4: {afficherlist();break;}
               case 5:{printf("===== Hospital Statistics =====\n");
               printf("\nle nombre du patient:%d",comPA);
               printf("\nle nombre des maladies:%d",comPMA);
               break;}



            case 0:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
                break;
        }

        printf("\n");
}while (choix != 0);
  return 0;}
