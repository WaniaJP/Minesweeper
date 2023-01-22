/**
 * @file Grille.cpp
 * Projet Minesweeper
 * @author Wania Jean-Pierre et L�a Thai
 * @version 6 - 08/01/2022
 * @brief Composant de Grille
 */

#include "Grille.h"
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <iomanip>
#include <stdlib.h>
using namespace std;

/*
* @brief Affiche une Grille
* @param[in] grille : la grille � afficher
* @param[in] PoG : indique si la partie est perdue ou gagn�e (change l'affichage)
*/
void afficherGrille(Grille& grille, unsigned int PoG) {
	unsigned int numeroCase = 0;
	cout << grille.jeuPb.lignes << " " << grille.jeuPb.colonnes << endl;
	for (unsigned int i = 0; i < grille.jeuPb.lignes; ++i) { // la boucle s'initialise sur les lignes car on print lignes par lignes
		for (unsigned int m = 0; m < grille.jeuPb.colonnes; m++) {
			cout << " " << "___";
		}
		cout << endl;

		for (unsigned int m = 0; m < grille.jeuPb.colonnes; m++) {
            cout << "| ";
			switch (grille.tab[numeroCase]) {
				case masque: cout << ". ";
					break;

				case marque: 
					if (PoG != 0) cout << "m ";
					else cout << "x ";
					break;
				
				case marqueSp: // pour afficher l'erreur
					cout << "x ";
					break;

				case mine:
					if (PoG != 0) cout << "m ";
					else cout << ". ";
					break;

				default: //le cas par d�faut est celui des cas masque
					if (grille.tab[numeroCase] != 0) { //une case non-min� et non-masqu� � comme valeur 0 (donc demasque)
						cout << grille.tab[numeroCase] << " "; // ou le nombre de bombe proche dans ce cas on le print
					}
					else cout << "  ";
					
			}
			++numeroCase;
		}
        cout << "|" << endl;
	}

	for (unsigned int m = 0; m < grille.jeuPb.colonnes; m++) {
		cout << " " << "___";
	}
}

/*
* @brief Permet de d'initialiser correctement le tableau de Grille
* @param[in-out] grille : la grille � remplir
* @return un nombre indiquant si la partie est perdu ou non
*/
unsigned int abracadabra(Grille& grille) { //Nom � changer 
    Coup coup;
    Pile flood;
    unsigned int caseAct = 0;
    int tmp = 0;
    initialiser(flood, grille.taille, 1); // initialisation de la pile 

    for (unsigned int i = 0; i < grille.jeuHistorique.nbCoups; ++i) { // On regarde l'historique de coups
        coup = grille.jeuHistorique.listeCoups[i];
        if (coup.type == 'D') { // C'est de la merde pens� � mettre ' ' et pas " " car erreur vu que le C c'est de la merde
			if (grille.tab[coup.position] == mine) {
				return 1;
			}

			/* REMPLISSAGE PAR DIFFUSION */
            empiler(flood, coup.position);

            while (!(estVide(flood))) {
                caseAct = sommet(flood); // On r�cup�re la valeur que l'on va traiter
                depiler(flood); // On d�pile pour enlever la case que l'on traite
				//On donne le nombre de mine � proximit� comme valeur de la case pour les traiter plus facilement � l'affichage
				grille.tab[caseAct] = nbMineProche(grille.tab, caseAct, grille.taille, grille.jeuPb.colonnes); 

                if (grille.tab[caseAct]==0) { // On v�rifie qu'il n'y a pas de mines � proximit�
					queDoisJeEmpiler(grille.tab, caseAct, grille.taille, grille.jeuPb.colonnes, flood);
                }
            }
        }
        else { // Si le type du coup est 'M' donc marqu�
			if (grille.tab[coup.position] != mine) { // Si la case qu'on veut marqu� n'est pas une mine, on perd
				grille.tab[coup.position] = marqueSp; //la mauvaise case marqu� doit appara�tre dans l'affichage on utilise donc un statut sp�cial
				return 1;
			}
            grille.tab[coup.position] = marque;
        }
    }
	detruire(flood);
	return 0;
}

/* @brief Cr�er une Grille
*/
void creerGrille() {
    Grille grille;
    creerNvProbleme(grille.jeuPb);  // On r�cup�re le probl�me
    grille.taille = grille.jeuPb.colonnes * grille.jeuPb.lignes;

    grille.tab = new int[grille.taille];
	initialiserTabGrille(grille); // On initialise le tableau de statut 
    initiaHisto(grille.jeuHistorique);

    unsigned int WoL = abracadabra(grille);
    afficherGrille(grille, WoL);
}

/*
* @brief Cr�e un probl�me pour un type Grille
* @param[in-out] pb : le probl�me � cr�er
*/
void creerNvProbleme(Probleme& pb) {
    cin >> pb.lignes >> pb.colonnes >> pb.nbMines;
    assert(pb.nbMines <= (pb.lignes * pb.colonnes));
    pb.emplacementMines = new unsigned int[pb.nbMines];
    for (unsigned int i = 0; i < pb.nbMines; ++i) {
        cin >> pb.emplacementMines[i];
    }
}

/*
* @brief D�termine le nombre de mines � proximit�
* @param[in-out] tab: tableau de statut
* @param[in] position : la case
* @param[in] taille : la taille du tableau
* @param[in] nbColonnes : nombre de colonnes
* return le nombre de mines � proximit�
*/
unsigned int nbMineProche(int* tab, unsigned int position, unsigned int taille, unsigned int nbColonnes) {
	unsigned int nbMine = 0;

	/* Cas des coins */
	// Case 1er ligne tout � gauche 
	if (position == 0) {
		if (tab[position + 1] == mine || tab[position + 1] == marque) ++nbMine;
		if (tab[position + nbColonnes] == mine || tab[position + nbColonnes] == marque) ++nbMine;
		if (tab[position + nbColonnes + 1] == mine || tab[position + nbColonnes + 1] == marque) ++nbMine;
		return nbMine;
	}
	//case 1er ligne tout � droite 
	if (position + 1 == nbColonnes) {
		if (tab[position + nbColonnes] == mine || tab[position + nbColonnes] == marque) ++nbMine;
		if (tab[position + nbColonnes - 1] == mine || tab[position + nbColonnes - 1] == marque) ++nbMine;
		if (tab[position - 1 ] == mine || tab[position - 1] == marque) ++nbMine;
		return nbMine;
	}
	//case tout en bas � gauche
	if (position + nbColonnes == taille) {
		if (tab[position + 1] == mine || tab[position + 1] == marque) ++nbMine;
		if (tab[position - nbColonnes] == mine || tab[position - nbColonnes] == marque) ++nbMine;
		if (tab[position - nbColonnes + 1] == mine || tab[position - nbColonnes + 1] == marque) ++nbMine;
		return nbMine;
	}

	if (position + 1 == taille) {
		if (tab[position - 1] == mine || tab[position - 1] == marque) ++nbMine;
		if (tab[position - nbColonnes] == mine || tab[position - nbColonnes] == marque) ++nbMine;
		if (tab[position - nbColonnes - 1] == mine || tab[position - nbColonnes - 1] == marque) ++nbMine;
		return nbMine;
	}


	/****** Cas particulier des lignes et colonnes en bordure ******/

	// toutes les cases de la derni�re ligne sauf les coins  
	if (position + nbColonnes > taille) {
		if (tab[position + 1] == mine || tab[position + 1] == marque) ++nbMine;
		if (tab[position - 1] == mine || tab[position - 1] == marque) ++nbMine;
		if (tab[position - nbColonnes] == mine || tab[position - nbColonnes] == marque) ++nbMine;
		if (tab[position - nbColonnes + 1] == mine || tab[position - nbColonnes + 1] == marque) ++nbMine;
		if (tab[position - nbColonnes - 1] == mine || tab[position - nbColonnes - 1] == marque) ++nbMine;
		return nbMine;
	}

	// toutes les cases de la 1ere ligne sauf les coins 
	if (position - nbColonnes < 0) {
		if (tab[position + nbColonnes] == mine || tab[position + nbColonnes] == marque) ++nbMine;
		if (tab[position + nbColonnes + 1] == mine || tab[position + nbColonnes + 1] == marque) ++nbMine;
		if (tab[position + nbColonnes - 1] == mine || tab[position + nbColonnes - 1] == marque) ++nbMine;
		if (tab[position + 1] == mine || tab[position + 1] == marque) ++nbMine;
		if (tab[position - 1] == mine || tab[position - 1] == marque) ++nbMine;
		return nbMine;
	}

	// COLONNES Particuli�re

	// toutes les cases de la colonne de droite sauf les coins 
	if ((position +1) % nbColonnes == 0) {
		if (tab[position + nbColonnes] == mine || tab[position + nbColonnes] == marque) ++nbMine;
		if (tab[position + nbColonnes] == mine || tab[position + nbColonnes] == marque) ++nbMine;
		if (tab[position - 1] == mine || tab[position - 1] == marque) ++nbMine;
		if (tab[position - nbColonnes] == mine || tab[position - nbColonnes] == marque) ++nbMine;
		if (tab[position - nbColonnes - 1] == mine || tab[position - nbColonnes - 1] == marque) ++nbMine;
		return nbMine;
	}

	// toutes les cases de la colonne de gauche sauf les coins 
	if (position % nbColonnes == 0) {
		if (tab[position + nbColonnes] == mine || tab[position + nbColonnes] == marque) ++nbMine;
		if (tab[position + nbColonnes] == mine || tab[position + nbColonnes] == marque) ++nbMine;
		if (tab[position + 1] == mine || tab[position + 1] == marque) ++nbMine;
		if (tab[position - nbColonnes] == mine || tab[position - nbColonnes] == marque) ++nbMine;
		if (tab[position - nbColonnes + 1] == mine || tab[position - nbColonnes + 1] == marque) ++nbMine;
		return nbMine;
	}

	//Cas par d�faut 

	//toute le cases sauf ceux pr�cis�es plus haut, cases du centre
	if (tab[position + nbColonnes] == mine || tab[position + nbColonnes] == marque) ++nbMine;
	if (tab[position + nbColonnes + 1] == mine || tab[position + nbColonnes + 1] == marque) ++nbMine;
	if (tab[position + nbColonnes - 1] == mine || tab[position + nbColonnes - 1] == marque) ++nbMine;
	if (tab[position + 1] == mine || tab[position + 1] == marque) ++nbMine;
	if (tab[position - 1] == mine || tab[position - 1] == marque) ++nbMine;
	if (tab[position - nbColonnes] == mine || tab[position - nbColonnes] == marque) ++nbMine;
	if (tab[position - nbColonnes - 1] == mine || tab[position - nbColonnes - 1] == marque) ++nbMine;
	if (tab[position - nbColonnes + 1] == mine || tab[position - nbColonnes + 1] == marque) ++nbMine;
	return nbMine;
}

/*
* @brief Empile les bonnes cases � proximit�
* @param[in-out] tab: tableau de statut
* @param[in] position : la case
* @param[in] taille : la taille du tableau
* @param[in] nbColonnes : nombre de colonnes
* @param[in-out] abracadabra : la pile
*/
void queDoisJeEmpiler(int* tab, unsigned int position, unsigned int taille, unsigned int nbColonnes, Pile& abracadabra) {

	/* Cas des coins */
	// Case 1er ligne tout � gauche 
	if (position == 0) {
		if (tab[position + 1] == masque) empiler(abracadabra, position + 1);
		if (tab[position + nbColonnes] == masque) empiler(abracadabra, position + nbColonnes);
		return;
	}
	//case 1er ligne tout � droite
	if (position + 1 == nbColonnes) {
		if (tab[position - 1] == masque) empiler(abracadabra, position - 1);
		if (tab[position + nbColonnes] == masque) empiler(abracadabra, position + nbColonnes);
		return;
	}
	//case tout en bas � gauche
	if (position + nbColonnes == taille) {
		if (tab[position + 1] == masque) empiler(abracadabra, position + 1);
		if (tab[position - nbColonnes] == masque) empiler(abracadabra, position - nbColonnes);
		return;
	}
	//case tout en bas � droite
	if (position + 1 == taille) {
		if (tab[position - 1] == masque) empiler(abracadabra, position - 1);
		if (tab[position - nbColonnes] == masque) empiler(abracadabra, position - nbColonnes);
		return;
	}


	/****** Cas particulier des lignes et colonnes en bordure ******/

	// LIGNES
	// toutes les cases de la derni�re ligne sauf les coins  
	if (position + nbColonnes > taille) {
		if (tab[position + 1] == masque) empiler(abracadabra, position + 1);
		if (tab[position - 1] == masque) empiler(abracadabra, position - 1);
		if (tab[position - nbColonnes] == masque) empiler(abracadabra, position - nbColonnes);
		return;
	}

	// toutes les cases de la 1ere ligne sauf les coins 
	if (position - nbColonnes < 0) {
		if (tab[position + 1] == masque) empiler(abracadabra, position + 1);
		if (tab[position - 1] == masque) empiler(abracadabra, position - 1);
		if (tab[position + nbColonnes] == masque) empiler(abracadabra, position + nbColonnes);
		return;
	}

	// COLONNES Particuli�re

	// toutes les cases de la colonne de droite sauf les coins
	if ((position + 1) % nbColonnes == 0) {
		if (tab[position - 1] == masque) empiler(abracadabra, position - 1);
		if (tab[position - nbColonnes] == masque) empiler(abracadabra, position - nbColonnes);
		if (tab[position + nbColonnes] == masque) empiler(abracadabra, position + nbColonnes);
		return;
	}

	// toutes les cases de la colonne de gauche sauf les coins
	if (position % nbColonnes == 0) {
		if (tab[position + 1] == masque) empiler(abracadabra, position + 1);
		if (tab[position - nbColonnes] == masque) empiler(abracadabra, position - nbColonnes);
		if (tab[position + nbColonnes] == masque) empiler(abracadabra, position + nbColonnes);
		return;
	}

	//Cas par d�faut 

	//toute le cases sauf ceux pr�cis�es plus haut, cases du centre
	if (tab[position + nbColonnes] == masque) empiler(abracadabra, position + nbColonnes);
	if (tab[position - nbColonnes] == masque) empiler(abracadabra, position - nbColonnes);
	if (tab[position - 1] == masque) empiler(abracadabra, position - 1);
	if (tab[position + 1] == masque) empiler(abracadabra, position + 1);
	return;
}

/*
* @brief initialiser le Tableau d'un type Grille
* @param[in-out] grille : la grille dont le tableau doit �tre initialis�
*/
void initialiserTabGrille(Grille& grille) {
	for (unsigned int i = 0; i < grille.taille; ++i) { // on initialise tout le tableau au statut masque
		grille.tab[i] = masque;
	}

	for (unsigned int i = 0; i < grille.jeuPb.nbMines; ++i) { // puis on met le statut mine aux bonnes cases
		grille.tab[grille.jeuPb.emplacementMines[i]] = mine;
	}
}

/* @brief Affiche si la partie est gagn�e ou non
*/
void partieGagne() {
	Grille grille;
	creerNvProbleme(grille.jeuPb);
	grille.taille = grille.jeuPb.colonnes * grille.jeuPb.lignes;
	grille.tab = new int[grille.taille];

	initialiserTabGrille(grille);
	
	initiaHisto(grille.jeuHistorique);

	unsigned int WoL = abracadabra(grille);

	if (WoL != 0) { //valeur retourn� par abracadabra indique si la partie est perdu ou pas
		cout << "game not won";
	}
	else {
		/*Pour savoir si une partie est gagn� on doit v�rifier que tous les cases qui ne sont pas des mines soient d�couvertes*/
		unsigned int nbCaseDecou = 0; 
		for (unsigned int i = 0; i < grille.taille; ++i) {
			if (grille.tab[i] == masque) { //si un case masque est toujours pr�sente la partie n'est pas gagn�
				cout << "game not won";
				break;
			}
			if(grille.tab[i] >= demasque) ++nbCaseDecou; // demasque = 0 
		}
		if (nbCaseDecou == (grille.taille - grille.jeuPb.nbMines)) cout << "game won"; 
	}
}

/* @brief Affiche si la partie est perdue ou non
*/
void partiePerdu() {
	Probleme pb;
	Historique histo;
	creerNvProbleme(pb);
	initiaHisto(histo);

	unsigned int i;
	if (histo.listeCoups[histo.nbCoups-1].type == 'D') { //On v�rifie qu'on a pas demasque une mine
		for (i = 0; i < pb.nbMines; ++i) {
			if (histo.listeCoups[histo.nbCoups-1].position == pb.emplacementMines[i]) { // Si la position du Coup est celle d'une mine
				cout << "game lost";
				break;
			}
		}
		if( i == pb.nbMines) cout << "game not lost"; // i a parcouru le tableau sans erreur (if jamais valide)
	}

	else { // Cas o� le type du Coup est 'M'
		for (i = 0; i < pb.nbMines; ++i) { //On v�rifie qu'on a pas masqu� une non-mine
			if (histo.listeCoups[histo.nbCoups-1].position == pb.emplacementMines[i]) { // Si la position du Coup est celle d'une mine
				cout << "game not lost"; // La Case marqu�e est correcte
				break;
			}
		}
		if( i == pb.nbMines) cout << "game lost"; // marqu� une case sans mine  
	}
}
