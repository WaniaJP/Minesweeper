/**
 * @file ConteneurTDE.cpp
 * Projet Minesweeper
 * @author l'�quipe p�dagogique et Wania Jean-Pierre
 * @version 4 08/01/22
 * @brief Composant de ConteneurTDE
 */

#include <iostream>
#include <cassert>
#include "Statut.h"
#include "ConteneurTDE.h"
#include <stdlib.h>
#include <cstdlib>
#include <time.h> 
#pragma warning(disable : 4996)
using namespace std;


/**
 * @brief Initialise un conteneur d'unsigned ints
 * Allocation en m�moire dynamique du conteneur d'unsigned ints
 * de capacit� (capa) extensible par pas d'extension (p)
 * @see detruire, pour sa d�sallocation en fin d'utilisation 
 * @param[out] c : le conteneur d'unsigned ints
 * @param [in] capa : capacit� du conteneur
 * @param [in] p : pas d'extension de capacit�
 * @pre capa>0 et p>0
 */
void initialiser(ConteneurTDE& c, unsigned int capa, unsigned int p) {
	assert(capa > 0 && p > 0);
	c.capacite = capa;
	c.pasExtension = p;

	c.tab = new unsigned int[capa];
}

/**
 * @brief D�salloue un conteneur d'unsigned ints en m�moire dynamique
 * @see initialiser, le conteneur d'unsigned ints a d�j� �t� allou� 
 * @param[out] c : le conteneur d'unsigned ints
 */
void detruire(ConteneurTDE& c) {
	if (c.tab != NULL) {
		delete[] c.tab;
	}
}

/**
 * @brief Lecture d'un unsigned int d'un conteneur d'unsigned ints
 * @param[in] c : le conteneur d'unsigned ints
 * @param[in] i : la position de l'unsigned int dans le conteneur
 * @return l'unsigned int � la position i
 * @pre i < c.capacite   
 */
 unsigned int lire(const ConteneurTDE& c, int i) {

	assert(i < c.capacite);
	return c.tab[i];
}

/**
 * @brief Ecrire un unsigned int dans un conteneur d'unsigned ints
 * @param[in,out] c : le conteneur d'unsigned ints
 * @param[in] i : la position o� ajouter/modifier l'unsigned int
 * @param[in] it : l'unsigned int � �crire 
 */
void ecrire(ConteneurTDE& c, unsigned int i, unsigned int it) {
	unsigned int newTaille;
	unsigned int* newT;
	if (i>=c.capacite) {
		/* Strat�gie de r�allocation proportionnelle au pas d'extension :
		 * initialisez la nouvelle taille du conteneur (newTaille) 
		 * � (i+1) * c.pasExtension */
		newTaille = i + 1 * c.pasExtension;
		/* Allouez en m�moire dynamique un nouveau tableau (newT) 
		 * � cette nouvelle taille*/
		/* Recopiez les unsigned ints d�j� stock�s dans le conteneur */
		newT = new unsigned int[newTaille];

		for (int i = 0; i < c.capacite; ++i) {
			newT[i] = c.tab[i];
		}
      	/* D�sallouez l'ancien tableau support du conteneur */
		delete[] c.tab;
    	/* Actualiser la mise � jour du conteneur en m�moire dynamique
    	 * Faites pointer le tableau support du conteneur 
    	 * sur le nouveau tableau en m�moire dynamique */
    	c.tab = newT;
    	/* Actualisez la taille du conteneur */
		c.capacite = newTaille;
	}
	/* Ecriture de l'unsigned int (it) � la position i dans le conteneur */
	c.tab[i] = it;
	c.nbElemDansTab += 1;
}

/******************************************** TRI ****************************************************/

/**
* @brief Echange les valeurs des indices i et j dans un tableau
* @param[in-out] c : le conteneur
* @param[in] i : le premier indice
* @param[in] j : le deuxieme indice
*/

void echanger(ConteneurTDE& c, unsigned int i, unsigned int j) {
	assert(i >= 0 && j < c.nbElemDansTab);
	unsigned int tmp = c.tab[i];
	c.tab[i] = c.tab[j];
	c.tab[j] = tmp;
}


/**
* @brief S�lectionne le pivot et tri une partie du tableau
* @param[in-out] c : le conteneur
* @param[in] debut : le premier indice
* @param[in] fin : le deuxieme indice
*/


int repartition(ConteneurTDE& c,int* tableauGrille, int debut, int fin) {
	int pivot = lire(c, fin); // pivot prend la deni�re val du conteneur, qui en faite la possition case qui a une mine a proximit�e    
	int i = debut - 1;
	for (unsigned int j = debut; j < fin - 1; j++) {
		if ( tableauGrille[lire(c, j)] < tableauGrille[pivot]) { // ordre croissant, utili  
			i += 1;
			echanger(c, i, j);

		}
	}
	echanger(c, ++i, fin); 
	return i; // pas besoin de i+1 du au ++i
}


/**
* @brief Fait des appels r�cursifs pout trier la partie gauche et droite du pivot
* @param[in-out] c : le conteneur
* @param[in] debut : le premier indice
* @param[in] fin : le deuxieme indice
*/

void TriRapideRec(ConteneurTDE& c, int* tableauGrille, int debut, int fin) {
	int p;
	if (fin - debut >= 1) { // s'il reste des �l�ments
		p = repartition(c, tableauGrille, debut, fin); // s�letionne pivot 
		TriRapideRec(c, tableauGrille, debut, p - 1); // trie partie gauche du pivot 
		TriRapideRec(c, tableauGrille, p + 1, fin); // trie partie droite du pivot 
	}
}


/**
* @brief Tri rapide dans l'ordre d�croissant d'un tableau
* @param[in-out] c : le conteneur
*/

void TriRapide(ConteneurTDE& c, int* tableauGrille) {
	TriRapideRec(c, tableauGrille, 0, c.nbElemDansTab - 1);
}

/******************************************** FIN TRI ****************************************************/


/* @brief G�n�re un nouveau coup
*/
void nvCoup() {
	unsigned int nbrL, nbrC;
	cin >> nbrL >> nbrC;
	unsigned int nombreCharLigne = 4 * nbrC + 2; // sch�ma r�p�titif de 4 caract�res ex: "| x " , le +2 = \0 + "|" 
	int* tableauGrille = new int[nbrL * nbrC];
	ConteneurTDE posCaseMineProx;
	initialiser(posCaseMineProx, nbrC, nbrC);
	remplissageGrille(nombreCharLigne, tableauGrille, nbrL, posCaseMineProx);
	TriRapide(posCaseMineProx, tableauGrille);
	bool nvCoupPossible = false;

	//Parcours inverse car tri croissant, et on veut en d�croissant   
	for (int i = posCaseMineProx.nbElemDansTab - 1; i >= 0; --i) {
		ConteneurTDE caseMasqueProxi;
		initialiser(caseMasqueProxi, 2, 2);

		nvCoupPossible = checkCarrePourMarque(tableauGrille, posCaseMineProx.tab[i], caseMasqueProxi, nbrC, nbrL);
		if (nvCoupPossible == true) {
			unsigned int caseMarque = rand() % caseMasqueProxi.nbElemDansTab;
			cout << "M" << lire(caseMasqueProxi, caseMarque);
			break;
		}
		detruire(caseMasqueProxi);
	}

	
	if (nvCoupPossible == false) {
		for (int i = posCaseMineProx.nbElemDansTab - 1; i >= 0; --i) { // Sens inverse
			ConteneurTDE caseMasqueProxi;
			initialiser(caseMasqueProxi, 2, 2);

			nvCoupPossible = checkCarre(tableauGrille, posCaseMineProx.tab[i], caseMasqueProxi, nbrC, nbrL);
			if (nvCoupPossible == true) {
				unsigned int caseDemasque = rand() % caseMasqueProxi.nbElemDansTab;
				cout << "D" << lire(caseMasqueProxi, caseDemasque);
				break;
			}
			detruire(caseMasqueProxi);
		}
	}

	//dernier cas pour d�masquer
	if (nvCoupPossible == false && posCaseMineProx.nbElemDansTab !=0) {
		unsigned int i = 0;
		bool cbon = false;
		do {
			ConteneurTDE caseMasqueProxi;
			unsigned int caseMineProxi = lire(posCaseMineProx, i);
			initialiser(caseMasqueProxi, 2, 2);
			bool verif = checkCarre(tableauGrille, caseMineProxi, caseMasqueProxi, nbrC, nbrL);
			++i;
			if(caseMasqueProxi.nbElemDansTab != 0){
				cbon = true;
				unsigned int caseDemasque = rand() % caseMasqueProxi.nbElemDansTab;
				cout << "D" << lire(caseMasqueProxi, caseDemasque);
				nvCoupPossible = true;
			}
			detruire(caseMasqueProxi);
		} while (cbon == false);

		detruire(posCaseMineProx);
	}

	//Cas o� aucune case n'a encore �t� d�voil� ou, o� tout ceux du dessus sont impossibles
	if (nvCoupPossible == false) {
		unsigned int nvCoup = rand() % (nbrC * nbrL);;
		while (tableauGrille[nvCoup] != masque) {
			++nvCoup;
			if (nvCoup == (nbrC * nbrL)) nvCoup = 0;
		}
		cout << "D" << nvCoup;

	}
}

/*
* @brief Indique s'il y a des cases d�couvertes sans mines proches, � proximit� de la case masqu�e
* @param[in] tabGrille : un tableau de statut 
* @param[in] nbrC : nombre de colonnes
* @param[in] nbrL : nombre de lignes
* @param[in] caseMasque : la case � v�rifier
* @return true ou false
*/
bool checkZero(int* tabGrille, unsigned int nbrC, unsigned int nbrL, unsigned int caseMasque) {
	if (caseMasque > nbrC) { //Nord
		if (tabGrille[caseMasque - nbrC] == demasque) return false; // pas de mines � proximit�es

	}
	if ((caseMasque + nbrC) < (nbrC * nbrL)) { //Sud
		if (tabGrille[caseMasque + nbrC] == demasque) return false;
	}
	if (caseMasque % nbrC != 0) { //Ouest
		if (tabGrille[caseMasque - 1] == demasque) return false;
	}
	if ((caseMasque + 1) % nbrC != 0) { //Est
		if (tabGrille[caseMasque + 1] == demasque) return false;
	}

	if (caseMasque > nbrC && caseMasque % nbrC != 0) { //Nord-Ouest
		if (tabGrille[caseMasque - nbrC - 1] == demasque) return false;
	}
	if (caseMasque > nbrC && (caseMasque + 1) % nbrC != 0) { //Nord-Est
	
		if (tabGrille[caseMasque - nbrC + 1] == demasque) return false;
	}

	if (caseMasque + nbrC < (nbrC * nbrL) && caseMasque % nbrC != 0) { //Sud-Ouest
		if (tabGrille[caseMasque + nbrC - 1] == demasque) return false;
	}

	if ((caseMasque + nbrC) < (nbrC * nbrL) && (caseMasque + 1) % nbrC != 0) { //Sud-Est
		if (tabGrille[caseMasque + nbrC + 1] == demasque) return false;
	}

	return true;
}

/*
* @brief Remplie grille
*  @param[in] nombreCharLigne : au nombre max de caractere dans une ligne
*  @param[in-out] tab : le tableau 
*  @param[in] nbrL : nombre de ligne dans la grille
*/
void remplissageGrille(unsigned int nombreCharLigne, int* tab, unsigned int nbrL, ConteneurTDE& posCaseMineProx) {
	char* ligne = new char[nombreCharLigne];
	unsigned int nCase = 0;
	for (unsigned int i = 0; i < nbrL; ++i) {
		cin >> ws;
		cin.getline(ligne, nombreCharLigne); // On r�cup�re la ligne d'underscore

		cin >> ws;
		cin.getline(ligne, nombreCharLigne); // On �crase l'ancienne ligne sauvegarde pour traiter celle qui nous int�resse

		//On commence la boucle � la valeur 2 car c'est la position de la premi�re valeur d'int�r�t
		for (unsigned int m = 2; m < strlen(ligne); m += 4) { //voir sch�ma r�p�titif (ligne 402), la valeur int�ressante se trouve toujours � 4 indice 
															//de la pr�cedente d� au sch�ma r�p�titif
			if (sscanf(&ligne[m], "%d", &tab[nCase]) == true) { // On v�rifie qu'une conversion est possible, si c'est possible 
				ecrire(posCaseMineProx, posCaseMineProx.nbElemDansTab, nCase); // stock dans posCaseMineProx (contene) la position des cases ayant des mines � proximit�
				++nCase; // stock positions
			}
			else {
				if (ligne[m] == '.') {
					tab[nCase] = masque;
					++nCase;
				}
				else {
					if (ligne[m] == ' ') {
						tab[nCase] = demasque;
						++nCase;
					}
					else {
						if (ligne[m] == 'x') {
							tab[nCase] = marque;
							++nCase;
						}
					}
				}
			}
		}
	}

	cin >> ws;
	cin.getline(ligne, nombreCharLigne); // on r�cup�re la derni�re ligne d'underscore   
}

/**
* @brief Indique si on peut marquer une case et remplie le conteneur  
* @param[in] tableauGrille: tableau de statut  
* @param[in] CaseMineProx : case actuelle
* @param[in-out] caseMasqueProxi : le conteneur rempli
* @param[in] nbrC : nombre de colonnes  
* @param[in] nbrL : nombre de lignes     
*/

bool checkCarrePourMarque(int* tableauGrille, unsigned int CaseMineProx, ConteneurTDE& caseMasqueProxi,  unsigned int nbrC, unsigned int nbrL) {
	unsigned valCaseActuel = tableauGrille[CaseMineProx]; 
	if (CaseMineProx >= nbrC) { //Nord
		if (tableauGrille[CaseMineProx - nbrC] == masque && checkZero(tableauGrille, nbrC, nbrL, CaseMineProx - nbrC) == true) {
			ecrire(caseMasqueProxi, caseMasqueProxi.nbElemDansTab, CaseMineProx - nbrC);
		}
		if (tableauGrille[CaseMineProx - nbrC] == marque) --valCaseActuel; //On veut savoir si il y a d�j� des case marqu� � proximit�
	}
		if ((CaseMineProx + nbrC) < (nbrC * nbrL)) { //Sud
			if (tableauGrille[CaseMineProx + nbrC] == masque && checkZero(tableauGrille, nbrC, nbrL, CaseMineProx + nbrC) == true) {
				ecrire(caseMasqueProxi, caseMasqueProxi.nbElemDansTab, CaseMineProx + nbrC);
			}
			if (tableauGrille[CaseMineProx + nbrC] == marque) --valCaseActuel;
		}
		if (CaseMineProx % nbrC != 0) { //Ouest
			if (tableauGrille[CaseMineProx - 1] == masque && checkZero(tableauGrille, nbrC, nbrL, CaseMineProx - 1) == true) {
				ecrire(caseMasqueProxi, caseMasqueProxi.nbElemDansTab, CaseMineProx - 1);
			}
			if (tableauGrille[CaseMineProx - 1] == marque) --valCaseActuel;
		}
		if ((CaseMineProx + 1) % nbrC != 0) { //Est
			if (tableauGrille[CaseMineProx + 1] == masque && checkZero(tableauGrille, nbrC, nbrL, CaseMineProx + 1) == true) {
				ecrire(caseMasqueProxi, caseMasqueProxi.nbElemDansTab, CaseMineProx + 1);
			}
			if (tableauGrille[CaseMineProx + 1] == marque) --valCaseActuel;
		}

		if (CaseMineProx >= nbrC && CaseMineProx % nbrC != 0) { //Nord-Ouest
			if (tableauGrille[CaseMineProx - nbrC - 1] == masque && checkZero(tableauGrille, nbrC, nbrL, CaseMineProx - nbrC - 1) == true) {
				ecrire(caseMasqueProxi, caseMasqueProxi.nbElemDansTab, CaseMineProx - nbrC - 1);
			}
			if (tableauGrille[CaseMineProx - nbrC - 1] == marque) --valCaseActuel;
		}
		if (CaseMineProx >= nbrC && (CaseMineProx + 1) % nbrC != 0) { //Nord-Est
			if (tableauGrille[CaseMineProx - nbrC + 1] == masque && checkZero(tableauGrille, nbrC, nbrL, CaseMineProx - nbrC + 1) == true) {
				ecrire(caseMasqueProxi, caseMasqueProxi.nbElemDansTab, CaseMineProx - nbrC + 1);
			}
			if (tableauGrille[CaseMineProx - nbrC + 1] == marque) --valCaseActuel;
		}

		if (CaseMineProx + nbrC < (nbrC * nbrL) && CaseMineProx % nbrC != 0) { //Sud-Ouest
			if (tableauGrille[CaseMineProx + nbrC - 1] == masque && checkZero(tableauGrille, nbrC, nbrL, CaseMineProx + nbrC - 1) == true) {
				ecrire(caseMasqueProxi, caseMasqueProxi.nbElemDansTab, CaseMineProx + nbrC - 1);
			}
			if (tableauGrille[CaseMineProx + nbrC - 1] == marque) --valCaseActuel;
		}

		if ((CaseMineProx + nbrC) < (nbrC * nbrL) && (CaseMineProx + 1) % nbrC != 0) { //Sud-Est
			if (tableauGrille[CaseMineProx + nbrC + 1] == masque && checkZero(tableauGrille, nbrC, nbrL, CaseMineProx + nbrC + 1) == true) {
				ecrire(caseMasqueProxi, caseMasqueProxi.nbElemDansTab, CaseMineProx + nbrC + 1);
			}
			if (tableauGrille[CaseMineProx + nbrC + 1] == marque) --valCaseActuel;
		}

		if (valCaseActuel >= caseMasqueProxi.nbElemDansTab && valCaseActuel != 0) return true;
		return false;
	}


/*
* @brief Remplie le conteneur caseMasqueProxi qui contient les positions des cases masqu�s autour d'une autre donn�e et indique si on peut marquer une case
* @param[in] tableauGrille : tableau de statut
* @param[in] caseMineProx : la case trait�
* @param[in-out] caseMasqueProxi : le conteneur remplie
* @param[in] nbrC : le nombre de colonnes
* @param[in] nbrL : le nombre de lignes
* @return 
*/
bool checkCarre(int* tableauGrille, unsigned int CaseMineProx, ConteneurTDE& caseMasqueProxi, unsigned int nbrC, unsigned int nbrL) {
	unsigned int valCaseActuel = tableauGrille[CaseMineProx];
	if (CaseMineProx >= nbrC) { //Nord
		if (tableauGrille[CaseMineProx - nbrC] == masque) {
			ecrire(caseMasqueProxi, caseMasqueProxi.nbElemDansTab, CaseMineProx - nbrC);
		}
		if (tableauGrille[CaseMineProx - nbrC] == marque) --valCaseActuel;
	}
	if ((CaseMineProx + nbrC) < (nbrC * nbrL)) { //Sud
		if (tableauGrille[CaseMineProx + nbrC] == masque) {
			ecrire(caseMasqueProxi, caseMasqueProxi.nbElemDansTab, CaseMineProx + nbrC);
		}
		if (tableauGrille[CaseMineProx + nbrC] == marque) --valCaseActuel;
	}
	if (CaseMineProx % nbrC != 0) { //Ouest
		if (tableauGrille[CaseMineProx - 1] == masque) {
			ecrire(caseMasqueProxi, caseMasqueProxi.nbElemDansTab, CaseMineProx - 1);
		}
		if (tableauGrille[CaseMineProx - 1] == marque) --valCaseActuel;
	}
	if ((CaseMineProx + 1) % nbrC != 0) { //Est
		if (tableauGrille[CaseMineProx + 1] == masque) {
			ecrire(caseMasqueProxi, caseMasqueProxi.nbElemDansTab, CaseMineProx + 1);
		}
		if (tableauGrille[CaseMineProx + 1] == marque) --valCaseActuel;
	}

	if (CaseMineProx >= nbrC && CaseMineProx % nbrC != 0) { //Nord-Ouest
		if (tableauGrille[CaseMineProx - nbrC - 1] == masque) {
			ecrire(caseMasqueProxi, caseMasqueProxi.nbElemDansTab, CaseMineProx - nbrC - 1);
		}
		if (tableauGrille[CaseMineProx - nbrC - 1] == marque) --valCaseActuel;
	}
	if (CaseMineProx >= nbrC && (CaseMineProx + 1) % nbrC != 0) { //Nord-Est
		if (tableauGrille[CaseMineProx - nbrC + 1] == masque) {
			ecrire(caseMasqueProxi, caseMasqueProxi.nbElemDansTab, CaseMineProx - nbrC + 1);
		}
		if (tableauGrille[CaseMineProx - nbrC + 1] == marque) --valCaseActuel;
	}

	if (CaseMineProx + nbrC < (nbrC * nbrL) && CaseMineProx % nbrC != 0) { //Sud-Ouest
		if (tableauGrille[CaseMineProx + nbrC - 1] == masque) {
			ecrire(caseMasqueProxi, caseMasqueProxi.nbElemDansTab, CaseMineProx + nbrC - 1);
		}
		if (tableauGrille[CaseMineProx + nbrC - 1] == marque) --valCaseActuel;
	}

	if ((CaseMineProx + nbrC) < (nbrC * nbrL) && (CaseMineProx + 1) % nbrC != 0) { //Sud-Est
		if (tableauGrille[CaseMineProx + nbrC + 1] == masque) {
			ecrire(caseMasqueProxi, caseMasqueProxi.nbElemDansTab, CaseMineProx + nbrC + 1);
		}
		if (tableauGrille[CaseMineProx + nbrC + 1] == marque) --valCaseActuel;
	}

	if (valCaseActuel == 0 && caseMasqueProxi.nbElemDansTab != 0) return true;

	return false;
}