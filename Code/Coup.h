#ifndef _COUP_
#define _COUP_

/**
 * @file Coup.h
 * Projet Minesweeper
 * @author Wania Jean-Pierre et L�a Thai
 * @version 2 - 27/12/2021
 * @brief Type Coup
 */

 /* @brief Type Coup comporte le type du coup et la position
 */
struct Coup {
    char type; // 1 seul �l�ment donc pas de tableau 
    unsigned int position;

};

/*@brief Effectue le traitement d'un coup
* @param[in] coup : le coup a trait�
* @param[in-out] nvC : le nouveau coup
*/
void traiterCoup(Coup& nvC);

#endif