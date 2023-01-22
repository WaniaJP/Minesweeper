#ifndef _PROBLEME_
#define _PROBLEME_

/**
 * @file Probleme.h
 * Projet Minesweeper
 * @author Wania Jean-Pierre et L�a Thai
 * @version 4 - 08/01/2022
 * @brief Composant de Probl�me
 */

#include "Statut.h"

/*
* @brief Type Probleme
* Contient toutes les informations d'un probl�me : nombre de lignes, de colonnes et de mines, et un tableau avec l'emplacement des mines
*/
struct Probleme {
	unsigned int lignes;
	unsigned int colonnes;
	unsigned int nbMines; 
	unsigned int* emplacementMines; //Tableau dynamique contenant l'emplacement des bombes 
	// Poss�de la taille du nombre de Mines
};

/*
* @brief Cr�e un probl�me et l'affiche
*/
void creerProbleme();

/*
* @brief Affiche un probl�me
* @param[in] pb : le probl�me � afficher
*/
void afficherProbleme(Probleme& pb);

/*
* @brief Cr�e un tableau avec l'emplacement des mines choisi al�atoirement
* @param[in] nbMines : le nombre de mines
* @return un tableau contenant l'emplacement de mines
*/
unsigned int* nvTabMine(unsigned int nbMines, unsigned int nbCases);

/*
* @brief Initialise un tableau de Statut
* @param[in-out] tableau : tableau contenant des statuts
* @param[in] taille : taille du tableau
* @param[in] nbMines : nombre de mines
*/
void initialiser(Statut* tableau, unsigned int taille, unsigned nbMines);


#endif