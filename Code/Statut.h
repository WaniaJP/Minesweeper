#ifndef _STATUT_
#define _STATUT_

/**
 * @file Statut.h
 * Projet Minesweeper
 * @author Wania Jean-Pierre et Léa Thai
 * @version 1 - 12/12/2021
 * @brief Spécialisation du Type Statut
 */

 /* @brief Structure Statut d'une case, qui peut prendre 4 valeurs : mine, marque, masque, desmasque
 */
enum Statut { mine = -1, marque = -2, masque = -3, marqueSp = -4, demasque = 0 };

#endif