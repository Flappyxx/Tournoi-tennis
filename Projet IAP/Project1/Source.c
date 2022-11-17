/*
source.c
LIN Oscar et CREUSEVEAU Lucas
Groupe 103
Cree le 02/10/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable :4996)

#define lgMot 30
#define nbMatchTournoi 127
#define maxTournoi 10
#define nbJoueuse 128
enum { SOIXANTEQUATRE = 0, TRENTEDEUX = 64, SEIZIEME = 96, HUITIEME = 112, QUART = 120, DEMI = 124, FINALE = 126 };


typedef struct {
	char nom[lgMot + 1];  //Nom de la joueuse
	unsigned int points;
}Joueuse;

typedef struct {
	unsigned int idxGagnante;  //Index
	unsigned int idxPerdante;
}Match;

typedef struct {
	char nom[lgMot + 1];  // Nom de tournoi
	int date; // Date du tournoi en annee
	Match dataMatch[nbMatchTournoi];
}Tournoi;

typedef struct {
	Tournoi dataTournois[maxTournoi];
	Joueuse dataJoueuse[maxTournoi * nbJoueuse];
	unsigned int idxTournoi, idxJoueuse;
}TournoiWTA;

/* Initialise une structure de tournoiWTA
* ptournoiWTA [in-out] le tournoiWTA
*/
void initialisation_structureWTA(TournoiWTA* ptournoiWTA);

/*Définit le nombre de tournoi maximum (entre 1 et 10)
* ptournoiWTA [in-out] le tournoiWTA
*/
void definir_nombre_tournois(TournoiWTA* ptournoiWTA);

/* Enregistre un tournoi une place disponible
* ptournoiWTA [in-out] le tournoiWTA
*/
void enregistrement_tournoi(TournoiWTA* ptournoiWTA);

/* Affiche les matchs d'un tournoi en particulier
* ptournoiWTA [in] le tournoiWTA
*/
void affichage_matchs_tournoi(const TournoiWTA* ptournoiWTA);

/* Affiche les matchs d'une joueuse dans un tournoi en particulier
* ptournoiWTA [in] le tournoiWTA
*/
void afficher_matchs_joueuse(const TournoiWTA* ptournoiWTA);

/* Affiche les informations des joueuse dans un tournoi (rangé par ordre alphabétique)
* ptournoiWTA [in] le tournoiWTA
*/
void affichage_joueuses_tournoi(const TournoiWTA* ptournoiWTA);

/* Affiche le classement des 4 derniers tournois réunis
* ptournoiWTA [in] le tournoiWTA
*/
void afficher_classement(const TournoiWTA* ptournoiWTA);

/* Ajoute des points seulement le positionnement de la joueuse
* match [in] numéro du match
* joueuseGagnante [in] index de la joueuse gagnante
* joueusePerdante [in] index de la joueuse perdante
* ptournoiWTA [in-out] le tournoiWTA
*/
void ajout_points(unsigned int match, unsigned int joueuseGagnante, unsigned int joueusePerdante,TournoiWTA* ptournoiWTA);

/* Retire des points seulement le positionnement de la joueuse
* match [in] numéro du match
* joueuseGagnante [in] index de la joueuse gagnante
* joueusePerdante [in] index de la joueuse perdante
* ptournoiWTA [in-out] le tournoiWTA
*/
void enlever_points(unsigned int match, unsigned int joueuseGagnante, unsigned int joueusePerdante,TournoiWTA* ptournoiWTA);

void initialisation_structureWTA(TournoiWTA* ptournoiWTA) {
	int i;
	ptournoiWTA->idxJoueuse = 0;
	ptournoiWTA->idxTournoi = 0;
	for (i = 0; i < maxTournoi; i++) {
		ptournoiWTA->dataJoueuse[i].points = 0;
	}
	for (; i < nbJoueuse * maxTournoi; i++) {
		ptournoiWTA->dataJoueuse[i].points = 0;
	}
}

void definir_nombre_tournois(TournoiWTA* ptournoiWTA) {
	int t;
	scanf("%d", &t); // Recuperation du chiffre dans le buffer
	if (t <= 0 || t > 10) {  //Verification de la donnee
		printf("Valeur invalide\n");
	}
	else {
		int i;
		for (i = 0; i < t; i++) {
			strcpy(ptournoiWTA->dataTournois[i].nom,"Dispo");
			ptournoiWTA->idxTournoi += 1;
		}
	}
}

void ajout_points(unsigned int match, unsigned int joueuseGagnante, unsigned int joueusePerdante, TournoiWTA* ptournoiWTA) {
	if (match < TRENTEDEUX) {
		ptournoiWTA->dataJoueuse[joueusePerdante].points += 10;
	}
	else if (match < SEIZIEME) {
		ptournoiWTA->dataJoueuse[joueusePerdante].points += 45;
	}
	else if (match < HUITIEME) {
		ptournoiWTA->dataJoueuse[joueusePerdante].points += 90;
	}
	else if (match < QUART) {
		ptournoiWTA->dataJoueuse[joueusePerdante].points += 180;
	}
	else if (match < DEMI) {
		ptournoiWTA->dataJoueuse[joueusePerdante].points += 360;
	}
	else if (match < FINALE) {
		ptournoiWTA->dataJoueuse[joueusePerdante].points += 720;
	}
	else {
		ptournoiWTA->dataJoueuse[joueusePerdante].points += 1200;
		ptournoiWTA->dataJoueuse[joueuseGagnante].points += 2000;
	}
}

void enlever_points(unsigned int match, unsigned int joueuseGagnante, unsigned int joueusePerdante, TournoiWTA* ptournoiWTA) {
	if (match < TRENTEDEUX) {
		ptournoiWTA->dataJoueuse[joueusePerdante].points -= 10;
	}
	else if (match < SEIZIEME) {
		ptournoiWTA->dataJoueuse[joueusePerdante].points -= 45;
	}
	else if (match < HUITIEME) {
		ptournoiWTA->dataJoueuse[joueusePerdante].points -= 90;
	}
	else if (match < QUART) {
		ptournoiWTA->dataJoueuse[joueusePerdante].points -= 180;
	}
	else if (match < DEMI) {
		ptournoiWTA->dataJoueuse[joueusePerdante].points -= 360;
	}
	else if (match < FINALE) {
		ptournoiWTA->dataJoueuse[joueusePerdante].points -= 720;
	}
	else {
		ptournoiWTA->dataJoueuse[joueusePerdante].points -= 1200;
		ptournoiWTA->dataJoueuse[joueuseGagnante].points -= 2000;
	}
}


void enregistrement_tournoi(TournoiWTA* ptournoiWTA) {
	char nom1[lgMot];
	char nom2[lgMot];
	int date;
	int trouve1, trouve2;
	int idxTournoi;
	int idxG, idxP;
	scanf("%s %d", &nom1, &date); //recuperation du nom et de la date du tournoi dans le buffer
	for (idxTournoi = 0; idxTournoi < ptournoiWTA->idxTournoi; idxTournoi++) {
		if (strcmp(ptournoiWTA->dataTournois[idxTournoi].nom, "Dispo") == 0) {
			break;
		}
		else if (strcmp(ptournoiWTA->dataTournois[idxTournoi].nom, nom1) == 0 && ptournoiWTA->dataTournois[idxTournoi].date == date) {
			idxTournoi = ptournoiWTA->idxTournoi + 1;
		}
	}
	if (idxTournoi == ptournoiWTA->idxTournoi) {
		printf("Pas de tournoi disponible\n");
	}
	else if (idxTournoi == ptournoiWTA->idxTournoi + 1) {
		printf("Tournoi deja existant\n");
	}
	else {
		strcpy(ptournoiWTA->dataTournois[idxTournoi].nom, nom1);
		ptournoiWTA->dataTournois[idxTournoi].date = date;
		for (int i = 0; i < nbMatchTournoi; i++) {
			trouve1 = 0;
			trouve2 = 0;
			scanf("%s %s", &nom1, &nom2);
			for (unsigned int j = 0; j <= ptournoiWTA->idxJoueuse && (trouve1 != 1 || trouve2 != 1); j++) {
				if (strcmp(nom1, ptournoiWTA->dataJoueuse[j].nom) == 0) {
					ptournoiWTA->dataTournois[idxTournoi].dataMatch[i].idxGagnante = j;
					idxG = j;
					trouve1 = 1;  // le nom du joueur 1 a ete trouve
				}
				else if (strcmp(nom2, ptournoiWTA->dataJoueuse[j].nom) == 0) {
					ptournoiWTA->dataTournois[idxTournoi].dataMatch[i].idxPerdante = j;
					idxP = j;
					trouve2 = 1;  // le nom du joueur 2 a ete trouve
				}
				else if (j == ptournoiWTA->idxJoueuse) {  //Le nom n'a pas ete enregistre, il faut donc l'enregistrer
					if (trouve1 != 1) {
						strcpy(ptournoiWTA->dataJoueuse[j].nom, nom1);
						ptournoiWTA->dataTournois[idxTournoi].dataMatch[i].idxGagnante = j;
						trouve1 = 1;
						idxG = j;
					}
					else {
						strcpy(ptournoiWTA->dataJoueuse[j].nom, nom2);
						ptournoiWTA->dataTournois[idxTournoi].dataMatch[i].idxPerdante = j;
						idxP = j;
						trouve2 = 1;
					}
					ptournoiWTA->idxJoueuse += 1;
				}
				if (trouve1 == 1 && trouve2 == 1) {
					ajout_points(i, idxG, idxP, ptournoiWTA);
				}
			}
		}
	}
	if (idxTournoi > 3) {
		for (int i = 0; i < nbMatchTournoi; i++) {
			idxG = ptournoiWTA->dataTournois[idxTournoi - 4].dataMatch[i].idxGagnante;
			idxP = ptournoiWTA->dataTournois[idxTournoi - 4].dataMatch[i].idxPerdante;
			enlever_points(i, idxG, idxP, ptournoiWTA);
		}
	}
}

void affichage_matchs_tournoi(const TournoiWTA* ptournoiWTA) {
	unsigned int idxgagnante, idxperdante;
	int date;
	int idxTournoi;
	char nom[lgMot];
	scanf("%s %d", nom, &date);
	for (idxTournoi = 0; idxTournoi < ptournoiWTA->idxTournoi && (strcmp(ptournoiWTA->dataTournois[idxTournoi].nom, nom) != 0 || ptournoiWTA->dataTournois[idxTournoi].date != date); idxTournoi++) {
		continue;
	}
	if (idxTournoi == ptournoiWTA->idxTournoi) {
		printf("Nom Invalide");
	}
	else {
		printf("%s %d\n", ptournoiWTA->dataTournois[idxTournoi].nom, ptournoiWTA->dataTournois[idxTournoi].date);
		for (int j = 0; j < nbMatchTournoi; j++) {
			if (j == SOIXANTEQUATRE) {
				printf("64emes de finale\n");
			}
			else if (j == TRENTEDEUX) {
				printf("32emes de finale\n");
			}
			else if (j == SEIZIEME) {
				printf("16emes de finale\n");
			}
			else if (j == HUITIEME) {
				printf("8emes de finale\n");
			}
			else if (j == QUART) {
				printf("quarts de finale\n");
			}
			else if (j == DEMI) {
				printf("demi-finales\n");
			}
			else if (j == FINALE) {
				printf("finale\n");
			}
			idxgagnante = ptournoiWTA->dataTournois[idxTournoi].dataMatch[j].idxGagnante;
			idxperdante = ptournoiWTA->dataTournois[idxTournoi].dataMatch[j].idxPerdante;
			printf("%s %s\n", ptournoiWTA->dataJoueuse[idxgagnante].nom, ptournoiWTA->dataJoueuse[idxperdante].nom);
		}
	}
}

void afficher_matchs_joueuse(TournoiWTA* ptournoiWTA) {
	char nom[lgMot];
	char nomTournoi[lgMot];
	int date;
	unsigned int idxJoueuse;
	int trouve = 0;
	unsigned int idxTournoi, idxAdversaire;
	scanf("%s %d %s", nomTournoi, &date, nom);
	for (int i = 0; i < ptournoiWTA->idxJoueuse; ++i) {
		if (strcmp(nom, ptournoiWTA->dataJoueuse[i].nom) == 0) {
			trouve = 1;
			idxJoueuse = i;
			break;
		}
	}
	if (trouve == 0) {
		printf("Nom invalide");
	}
	else {
		for (idxTournoi = 0; idxTournoi < maxTournoi && (strcmp(ptournoiWTA->dataTournois[idxTournoi].nom, nomTournoi) != 0 || ptournoiWTA->dataTournois[idxTournoi].date != date); idxTournoi++) {
			continue;
		}
		for (int i = 0; i < nbMatchTournoi; ++i) {
			if (ptournoiWTA->dataTournois[idxTournoi].dataMatch[i].idxGagnante == idxJoueuse) {
				idxAdversaire = ptournoiWTA->dataTournois[idxTournoi].dataMatch[i].idxPerdante;
				printf("%s %s\n", nom, ptournoiWTA->dataJoueuse[idxAdversaire].nom);
			}
			else if (ptournoiWTA->dataTournois[idxTournoi].dataMatch[i].idxPerdante == idxJoueuse) {
				idxAdversaire = ptournoiWTA->dataTournois[idxTournoi].dataMatch[i].idxGagnante;
				printf("%s %s\n", ptournoiWTA->dataJoueuse[idxAdversaire].nom, nom);
				break;
			}
		}
	}
}

void affichage_joueuses_tournoi(TournoiWTA* ptournoiWTA) {
	int date;
	int idxTournoi;
	char nom[lgMot];
	unsigned int tabIndexJoueuse[nbJoueuse];
	unsigned int tabPointsTournoi[nbJoueuse];
	int idxTabJoueuse = 0;
	int j;
	scanf("%s %d", nom, &date);
	for (idxTournoi = 0; idxTournoi < ptournoiWTA->idxTournoi && (strcmp(ptournoiWTA->dataTournois[idxTournoi].nom, nom) != 0 || ptournoiWTA->dataTournois[idxTournoi].date != date); idxTournoi++) {
		continue;
	}
	if (idxTournoi == ptournoiWTA->idxTournoi) {
		printf("Nom Invalide");
	}
	else {
		printf("%s %d\n", ptournoiWTA->dataTournois[idxTournoi].nom, ptournoiWTA->dataTournois[idxTournoi].date);
		int i;
		for (i = 0; i < TRENTEDEUX; i++) { // attribution des points pour le tournoi (peut être mis à par dans une autre fonction)
			tabIndexJoueuse[idxTabJoueuse] = ptournoiWTA->dataTournois[idxTournoi].dataMatch[i].idxPerdante;
			tabPointsTournoi[idxTabJoueuse] = 10;
			idxTabJoueuse++;
		}
		for (; i < SEIZIEME; i++) {
			tabIndexJoueuse[idxTabJoueuse] = ptournoiWTA->dataTournois[idxTournoi].dataMatch[i].idxPerdante;
			tabPointsTournoi[idxTabJoueuse] = 45;
			idxTabJoueuse++;
		}
		for (; i < HUITIEME; i++) {
			tabIndexJoueuse[idxTabJoueuse] = ptournoiWTA->dataTournois[idxTournoi].dataMatch[i].idxPerdante;
			tabPointsTournoi[idxTabJoueuse] = 90;
			idxTabJoueuse++;
		}
		for (; i < QUART; i++) {
			tabIndexJoueuse[idxTabJoueuse] = ptournoiWTA->dataTournois[idxTournoi].dataMatch[i].idxPerdante;
			tabPointsTournoi[idxTabJoueuse] = 180;
			idxTabJoueuse++;
		}
		for (; i < DEMI; i++) {
			tabIndexJoueuse[idxTabJoueuse] = ptournoiWTA->dataTournois[idxTournoi].dataMatch[i].idxPerdante;
			tabPointsTournoi[idxTabJoueuse] = 360;
			idxTabJoueuse++;
		}
		for (; i < FINALE; i++) {
			tabIndexJoueuse[idxTabJoueuse] = ptournoiWTA->dataTournois[idxTournoi].dataMatch[i].idxPerdante;
			tabPointsTournoi[idxTabJoueuse] = 720;
			idxTabJoueuse++;
		}
		tabIndexJoueuse[idxTabJoueuse] = ptournoiWTA->dataTournois[idxTournoi].dataMatch[i].idxPerdante;
		tabPointsTournoi[idxTabJoueuse] = 1200;
		idxTabJoueuse++;
		tabIndexJoueuse[idxTabJoueuse] = ptournoiWTA->dataTournois[idxTournoi].dataMatch[i].idxGagnante;
		tabPointsTournoi[idxTabJoueuse] = 2000;
		unsigned int temp, tempPoint;
		for (int i = 1; i < nbJoueuse; i++) {
			temp = tabIndexJoueuse[i];
			tempPoint = tabPointsTournoi[i];
			for (j = i; j > 0 && strcmp(ptournoiWTA->dataJoueuse[tabIndexJoueuse[j - 1]].nom, ptournoiWTA->dataJoueuse[temp].nom) > 0; j--) {
				tabIndexJoueuse[j] = tabIndexJoueuse[j - 1];
				tabPointsTournoi[j] = tabPointsTournoi[j - 1];
			}
			tabIndexJoueuse[j] = temp;
			tabPointsTournoi[j] = tempPoint;
		}
		for (int i = 0; i < nbJoueuse; i++) {
			printf("%s %d\n", ptournoiWTA->dataJoueuse[tabIndexJoueuse[i]].nom, tabPointsTournoi[i]);
		}
	}
}

void afficher_classement(TournoiWTA* ptournoiWTA) {
	int tabIdxJoueuse[nbJoueuse * nbMatchTournoi];
	for (int i = 0; i < ptournoiWTA->idxJoueuse; i++) {
		tabIdxJoueuse[i] = i;
	}
	int j, temp;
	for (int i = 1; i < ptournoiWTA->idxJoueuse; i++) {
		temp = tabIdxJoueuse[i];
		for (j = i; j > 0 && strcmp(ptournoiWTA->dataJoueuse[tabIdxJoueuse[j - 1]].nom, ptournoiWTA->dataJoueuse[temp].nom) > 0; j--) {
			tabIdxJoueuse[j] = tabIdxJoueuse[j - 1];
		}
		tabIdxJoueuse[j] = temp;
	}
	for (int i = 1; i < ptournoiWTA->idxJoueuse; i++) {
		temp = tabIdxJoueuse[i];
		for (j = i; j > 0 && (ptournoiWTA->dataJoueuse[tabIdxJoueuse[j - 1]].points < ptournoiWTA->dataJoueuse[temp].points); j--) {
			tabIdxJoueuse[j] = tabIdxJoueuse[j - 1];
		}
		tabIdxJoueuse[j] = temp;
	}
	for (int i = 0; i < ptournoiWTA->idxJoueuse; i++) {
		if (ptournoiWTA->dataJoueuse[tabIdxJoueuse[i]].points == 0) {
			break;
		}
		printf("%s %d\n", ptournoiWTA->dataJoueuse[tabIdxJoueuse[i]].nom, ptournoiWTA->dataJoueuse[tabIdxJoueuse[i]].points);
	}
}

int main() {
	char mot[lgMot];
	TournoiWTA infoTournoiWTA;
	initialisation_structureWTA(&infoTournoiWTA);
	while (1) {
		scanf("%s", mot);//lecture de la commande de l'utilisateur
		if (strcmp(mot, "definir_nombre_tournois") == 0) { //definir nombre de tournois
			definir_nombre_tournois(&infoTournoiWTA);
		}
		else if (strcmp(mot, "enregistrement_tournoi") == 0) {  //enregistrer un tournoi
			enregistrement_tournoi(&infoTournoiWTA);
		}
		else if (strcmp(mot, "affichage_matchs_tournoi") == 0) { //afficher les matchs d'un tournoi
			affichage_matchs_tournoi(&infoTournoiWTA);
		}
		else if (strcmp(mot, "afficher_matchs_joueuse") == 0) { //sortie de la fonction principale
			afficher_matchs_joueuse(&infoTournoiWTA);
		}
		else if (strcmp(mot, "affichage_joueuses_tournoi") == 0) { // affichage des joueuses du tournoi par ordre alphabétique
			affichage_joueuses_tournoi(&infoTournoiWTA);
		}
		else if (strcmp(mot, "afficher_classement") == 0) { //affichage du classement
			afficher_classement(&infoTournoiWTA);
		}
		else if (strcmp(mot, "exit") == 0) { //sortie de la fonction principale
			exit(0);
		}
	}
}