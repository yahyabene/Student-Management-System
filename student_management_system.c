#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXNOTES 4

// Creation de la structure date

typedef struct date {
	int jour, mois, annee;

}	date;

// Creation de la structure etudiant

typedef struct etudiant {
	int matricule;
	char nom[65], prenom[65];
	date dateN; // dateN(Naissance)
	float notes[MAXNOTES]; // tableau de 4 notes

}	etudiant;


// Definition de la structure liste chainee

typedef struct registre {

	int nb_etud;
	etudiant *etudiants;

}	registre;



/*	PROTOYPE	*/

date lire_date();
void affiche_date(date);
etudiant ajout_etud();
void affiche_etud(etudiant);
void ajout_etud_liste(registre *, etudiant *);
void print_registre(registre *);
void affiche_etd_admis(registre);
void rech_etd_matricule(registre, int);
void rech_etd_nom(registre, char *);
float moyG(float *);
void affiche_maj(registre);


/*>>>>>>>>>>>>>>>>>>>	LE MAIN    <<<<<<<<<<<<<<<<<<<*/

main() {

	int choix;
	int mat;
	char nom[65];
	etudiant e;
	registre r;

	r.nb_etud = 0;

	do {
		printf("\n\n\t\t Selectionner une operation\n\n");
		printf("\t1.Ajouter un nouvel etudiant\n");
		printf("\t2.Afficher tous les etudiants\n");
		printf("\t3.Afficher les etudiants admis\n");
		printf("\t4.Rechercher un etudiant par matricule\n");
		printf("\t5.Rechercher un etudiant par nom\n");
		printf("\t6.Afficher les majorants\n");
		printf("\t0.Quitter\n");
		scanf("\t%d", &choix);

		switch(choix) {
			case 1:
				e = ajout_etud();
				ajout_etud_liste(&r, &e);
				break;
			case 2:
				print_registre(&r);
				break;
			case 3: 
				affiche_etd_admis(r);
				break;
			case 4:
				printf("Saisir le matricule: ");
				scanf("%d", &mat);
				
				rech_etd_matricule(r, mat);	
				break;
			case 5:
				printf("Saisir un nom: ");
				scanf("%s", &nom);
				
				rech_etd_nom(r, nom);		
				break;
			case 6:
				affiche_maj(r);
				break;
		}

	} while(choix != 0);
}


/*>>>>>>>>>>>>>>>>>>>	DEFINITION DES FONCTIONS    <<<<<<<<<<<<<<<<<<<*/

// Definir:  Lire une date

date lire_date() {
	
	date d;
	
	do
	{
		printf("jj/mm/aaaa: ");
		scanf("%d/%d/%d", &d.jour, &d.mois, &d.annee);
		
	} while(d.jour >= 1 && d.jour <= 31 && d.mois >= 1 && d.mois <= 12 && d.annee >= 1900);
	
	return d;
}

// Definir: Afficher une date

void affiche_date(date d) {
	printf("%d/%d/%d", d.jour, d.mois, d.annee);
}

// Definire: Lire les informations d'un etudiant

etudiant ajout_etud() {
	etudiant e;
	int i;

	printf("Matricule: ");
	scanf("%d", &e.matricule);
	printf("Nom: ");
	scanf("%s", &e.nom);
	printf("Prenom: ");
	scanf("%s", &e.prenom);
	printf("Date de naissance: ");
	e.dateN = lire_date();
	printf("Notes: \n");
	for (i = 0; i < MAXNOTES; i++) {
		printf("Note %d: ", i+1);
		scanf("%f", &e.notes[i]);
	}

	return e;
}

// Definir: Afficher les informations d'un etudiant

void affiche_etud(etudiant e) {
	int i;

	printf("Matricule: %d\n", e.matricule);
	printf("Nom: %s\n", e.nom);
	printf("Prenom: %s\n", e.prenom);
	printf("Date de naissance: \n");
	affiche_date(e.dateN);
	printf("\n");
	printf("Notes: \n");
	for(i = 0; i < MAXNOTES; i++) {
		printf("Note %d: %.2f\n", i+1, e.notes[i]);
	}
}

// Ajouter un etudiant a la liste des etudiants

void ajout_etud_liste(registre *r, etudiant *e) {

	// Si la liste est vide

	if (r->nb_etud == 0) {
		r->etudiants = (etudiant *)malloc(sizeof(etudiant));

		r->etudiants[r->nb_etud] = *e;
		r->nb_etud++;

		return;
	}

	// Si la liste n'est pas vide

	r->etudiants = (etudiant *)realloc(r->etudiants, ((r->nb_etud)+1)*sizeof(etudiant)); // on peut eliminer nb_etud 
	r->etudiants[r->nb_etud] = *e;
	r->nb_etud++;
}

void print_registre(registre *r) { // On aussi peut faire passer le registre pas comme pointeur
	int i;

	for (i = 0; i < r->nb_etud; i++) {
		affiche_etud(r->etudiants[i]);
	}
}


// Def: Affiche les etudiants admis (moy gen >= 10)

void affiche_etd_admis(registre r) {
	int i, j, moyg = 0;

	for (i = 0; i < r.nb_etud; i++) {
		for (j = 0; j < MAXNOTES; j++) {
			moyg += r.etudiants[i].notes[j];
		}

		if(moyg / MAXNOTES >= 10)
			affiche_etud(r.etudiants[i]);
	}
}

// Def: Recherche par matricule et affiche etd

void rech_etd_matricule(registre r, int matricule) { // void --> etudiant
	
	/*
	for (i = 0; i < longeur du registre; i++)
	{
		if (matricule == e.matricule)
			affiche_etd(etd[e.matricule]);
	}
	*/
	
	int i;

	for (i = 0; i < r.nb_etud; i++)
	{
		if (matricule == r.etudiants[i].matricule)
		{
			affiche_etud(r.etudiants[i]);
			return;
		}
	}
	puts("matricule introubale");
			// return r->etudiants[i];
	// printf("matricule introuvable ");
}

// Def: Recherche par nom et afficher l'etudiant

void rech_etd_nom(registre r, char *nom) {

	int i, cpt = 0;
	
	for (i = 0; i < r.nb_etud; i++) {
		if (strcmp(nom, r.etudiants[i].nom) == 0)
		{
			affiche_etud(r.etudiants[i]);
			cpt++;			
		}
	}
	
	if(cpt == 0)
		puts("Etudiant introuvable!");
}

void affiche_maj(registre r)
{
	
	/*
	int i ;
	float max = -1.0; // afin d'eviter d'appeler moyG pour le premier test
	
	for (i = 0; ...)
	*/

	int j = 0;
	
	float maxN = moyG(r.etudiants[j].notes); 
	
	for (j = 1; j < r.nb_etud; j++)
	{
		if (moyG(r.etudiants[j].notes) > maxN)
			maxN = moyG(r.etudiants[j].notes);
	}
	
	int i, cpt = 0;
	
	for(i = 0; i < r.nb_etud; i++)
	{
		if(moyG(r.etudiants[i].notes) >= maxN)
			affiche_etud(r.etudiants[i]);
	}	
}

//registre* tri_nom(registre *r)
//{
//	int i;
//	etudiant pivot;
//	
//	for (i = 0; i < r->nb_etud; i++)
//	{
//		for (j = 0; j < r->nb_etud; j++)
//		{
//			
//		}
//	}
//}

float moyG(float *notes)
{
	int i, mg = 0;
	for (i = 0; i < MAXNOTES; i++)
	{
		mg += notes[i];
	}
	
	return mg/MAXNOTES;
}
