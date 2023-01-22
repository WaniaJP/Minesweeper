/**
 * @file Demineur.cpp
 * Projet Minesweeper
 * @author Wania Jean-Pierre et Léa Thai
 * @version 2 - 24/12/2021
 */

#include <iostream>
#include "Grille.h"
#include "ConteneurTDE.h"
#pragma warning(disable : 4996)
using namespace std;

int main() {
	srand((unsigned int)time(NULL));
	unsigned int code;
	cin >> code;
	if (code == 1) {
		creerProbleme();
		exit(0);
	}

	if (code == 2) {
		creerGrille();
		exit(0);
	}

	if (code == 3) {
		partieGagne();
		exit(0);
	}

	if (code == 4) {
		partiePerdu();
		exit(0);
	}

	if (code == 5) {
		nvCoup();
		exit(0);
	}

	return 0;
}