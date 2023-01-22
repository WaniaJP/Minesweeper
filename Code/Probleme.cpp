/**
 * @file Probleme.cpp
 * Projet Minesweeper
 * @author Wania Jean-Pierre et Léa Thai
 * @version 4 - 08/01/2022
 * @brief Composant de Problème
 */

#include <iostream>
#include <cassert>
#include "Probleme.h"
#pragma warning(disable : 4996)
using namespace std;

/*
* @brief Crée un problème et l'affiche
*/
void creerProbleme(){
	Probleme pb;
	cin >> pb.lignes >> pb.colonnes >> pb.nbMines;
	assert(pb.nbMines <= (pb.lignes * pb.colonnes));
	pb.emplacementMines = nvTabMine(pb.nbMines, pb.lignes * pb.colonnes);

	afficherProbleme(pb);
}

/*
* @brief Affiche un problème
* @param[in] pb : le problème à afficher
*/
void afficherProbleme(Probleme& pb){
	cout << pb.lignes << " " << pb.colonnes << " " << pb.nbMines;

	for (unsigned int i = 0; i < pb.nbMines; ++i) {
		cout << " " << pb.emplacementMines[i];
	}
}

/*
* @brief Crée un tableau contenant l'emplacement des mines choisi aléatoirement
* @param[in] nbMines : le nombre de mines
* @param[in] taille : la taille du tableau
* @return un tableau contenant l'emplacement de mines
*/
unsigned int* nvTabMine(unsigned int nbMines, unsigned int nbCases) {
	Statut* tableau = new Statut[nbCases];
	unsigned int* tabMines = new unsigned int[nbMines];

	initialiser(tableau, nbCases, nbMines); //initialisation du tableau de Statut

	for (unsigned int i = 0; i < nbMines; ++i) {
		tabMines[i] = i;
	}

	unsigned int case1, case2; // variable temporaire pour stocker les valeurs des cases
	unsigned int nbEchange = nbCases * nbMines * 2; // détermine le nombre d'échanges de cases à faire
	unsigned int tmp;
	Statut echange;

	for (unsigned int i = 0; i <= nbEchange; ++i) {
		/* Tirage aléatoire des cases */
		case1 = rand() % nbCases;
		case2 = rand() % nbCases;

		if (case1 == case2 || tableau[case1] == mine && tableau[case2] == mine) {
			continue;
		}
		else {
			if (tableau[case1] == mine) {
				tmp = 0;
				while (tabMines[tmp] != case1) { // on cherche l'indice où est la position de la bombe
					++tmp;
				}
				tabMines[tmp] = case2; // on change la position à l'indice de la bombe
			}

			if (tableau[case2] == mine) {
				tmp = 0;
				while (tabMines[tmp] != case2) {
					++tmp;
				}
				tabMines[tmp] = case1;
			}

			/* Echange des cases */
			echange = tableau[case1]; // on stocke la valeur de la première valeur pour ne pas la perdre
			tableau[case1] = tableau[case2];
			tableau[case2] = echange;
		}
	}

	return tabMines;
}

/*
* @brief Initialise un tableau de Statut
* @param[in-out] tableau : tableau contenant des statuts
* @param[in] taille : taille du tableau
* @param[in] nbMines : nombre de mines
*/
void initialiser(Statut* tableau, unsigned int taille, unsigned nbMines) {
	for (unsigned int i = 0; i < taille; ++i) { // initialisation de toutes les cases du tableau à masque
		tableau[i] = masque;

		if (i < nbMines) { // place les mines sur les premières cases pour faciliter la phase d'aléatoirisation
			tableau[i] = mine;
		}
	}
}