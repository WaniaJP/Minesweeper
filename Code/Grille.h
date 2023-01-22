#ifndef _GRILLE_
#define _GRILLE_

/**
 * @file Grille.h
 * Projet Minesweeper
 * @author Wania Jean-Pierre et L�a Thai
 * @version 6 - 08/01/2022
 * @brief Composant de Grille
 */

#include "Probleme.h"
#include "Historique.h"
#include "Pile.h"

/* @brief Type Grille,
* Contient toutes les informations d'une grille : sa taille, le tableau contenant les Statuts de cases, le probleme, l'historique de jeu
*/
struct Grille {
    unsigned int taille;
    int* tab; // Tableau dynamique de Statut 
    Probleme jeuPb;
    Historique jeuHistorique;
};


/*
* @brief Affiche une Grille
* @param[in] grille : la grille � afficher
* @param[in] PoG : indique si la partie est perdue ou non (change l'affichage)
*/
void afficherGrille(Grille& grille, unsigned int PoG);

/*
* @brief Permet de d'initialiser correctement le tableau de Grille
* @param[in-out] grille : la grille � remplir
* @return un nombre indiquant si la partie est perdu ou non
*/
unsigned int abracadabra(Grille& grille); // Nom � modifier

/* @brief Cr�er une Grille
*/
void creerGrille();

/*
* @brief Cr�e un probl�me pour un type Grille
* @param[in-out] pb : le probl�me � cr�er
*/
void creerNvProbleme(Probleme& pb);

/*
* @brief initialiser le Tableau d'un type Grille
* @param[in-out] grille : la grille dont le tableau doit �tre initialis�
*/
void initialiserTabGrille(Grille& grille);

/*
* @brief D�termine le nombre de mines � proximit�
* @param[in-out] tab: tableau de statut
* @param[in] position : la case 
* @param[in] taille : la taille du tableau 
* @param[in] nbColonnes : nombre de colonnes
* return le nombre de mines � proximit�
*/
unsigned int nbMineProche(int* tab, unsigned int position, unsigned int taille, unsigned int nbColonnes);

/*
* @brief Empile les bonnes cases � proximit�
* @param[in-out] tab: tableau de statut
* @param[in] position : la case
* @param[in] taille : la taille du tableau
* @param[in] nbColonnes : nombre de colonnes
* @param[in-out] abracadabra : la pile
*/
void queDoisJeEmpiler(int* tab, unsigned int position, unsigned int taille, unsigned int nbColonnes, Pile& abracadabra);

/* @brief Affiche si la partie est gagn�e ou non
*/
void partieGagne();

/* @brief Affiche si la partie est perdue ou non
*/
void partiePerdu();



#endif