/**
 * @file Coup.cpp
 * Projet Minesweeper
 * @author Wania Jean-Pierre et Léa Thai
 * @version 1 - 27/12/2021
 * @brief Type Coup
 */

#include <iostream>
#include "Coup.h"
using namespace std;
#pragma warning(disable : 4996)

/*@brief Effectue le traitement d'un coup
* @param[in] coup : le coup a traité
* @param[in-out] nvC : le nouveau coup
*/
void traiterCoup(Coup& nvC) {
    cin >> nvC.type >> nvC.position;
}

