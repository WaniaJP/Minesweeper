#ifndef _PROBLEME_
#define _PROBLEME_

/**
 * @file Probleme.h
 * Projet Minesweeper
 * @author Wania Jean-Pierre et Léa Thai
 * @version 4 - 08/01/2022
 * @brief Composant de Problème
 */

#include "Statut.h"

/*
* @brief Type Probleme
* Contient toutes les informations d'un problème : nombre de lignes, de colonnes et de mines, et un tableau avec l'emplacement des mines
*/
struct Probleme {
	unsigned int lignes;
	unsigned int colonnes;
	unsigned int nbMines; 
	unsigned int* emplacementMines; //Tableau dynamique contenant l'emplacement des bombes 
	// Possède la taille du nombre de Mines
};

/*
* @brief Crée un problème et l'affiche
*/
void creerProbleme();

/*
* @brief Affiche un problème
* @param[in] pb : le problème à afficher
*/
void afficherProbleme(Probleme& pb);

/*
* @brief Crée un tableau avec l'emplacement des mines choisi aléatoirement
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