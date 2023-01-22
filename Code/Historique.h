#ifndef _HISTORIQUE_
#define _HISTORIQUE_

/**
 * @file Historique.h
 * Projet Minesweeper
 * @author Wania Jean-Pierre et Léa Thai
 * @version 3 - 09/01/2021
 * @brief Composant de Historique
 */

#include "Coup.h"

 /* L'historique qui a le nombre de coups et la liste des coups
 */
struct Historique {
    unsigned int nbCoups;
    Coup* listeCoups; // Tableau dynamique contenant les coups 
};

/*@brief Initialise une structure Historique
* @param[in-out] histo : historique du jeu
*/
void initiaHisto(Historique& histo);


#endif