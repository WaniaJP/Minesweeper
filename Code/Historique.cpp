/*
 * @file Historique.cpp
 * Projet Minesweeper
 * @author Wania Jean-Pierre et Léa Thai
 * @version 3 - 27/12/2021
 * @brief Composant de Historique
 */

#include <iostream>
#include "Historique.h"
using namespace std;
#pragma warning(disable : 4996)


/*@brief Initialise une structure Historique
* @param[out] histo : historique du jeu
* @pram
*/
void initiaHisto(Historique& histo) {
	cin >> histo.nbCoups; // On récupère le nombre de coups
	histo.listeCoups = new Coup[histo.nbCoups];

	for (unsigned int i = 0; i < histo.nbCoups; ++i) { // On remplit la liste des coups
		traiterCoup(histo.listeCoups[i]);
	}
}