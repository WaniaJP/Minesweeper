/**
 * @file Pile.cpp
 * Projet sem04-cours-Cpp2
 * @author l'�quipe p�dagogique 
 * @version 1 - 29/11/2014
 * @brief Composant de pile � capacit� param�tr�e
 */

#include <iostream>
#include <cassert>
using namespace std;

#include "Pile.h"

 /**
* @brief Initialiser une pile vide
* la pile est allou�e en m�moire dynamique
* @see detruire, pour une d�sallocation en fin d�utilisation
* @param[out] p : la pile � initialiser
* @param[in] c : capacit� de la pile (nb maximum d�unsigned ints stock�s)
* @param[in] extension : le pas d'extension de la pile
* @pre c>0
*/
void initialiser(Pile& p, unsigned int c, unsigned extension) {
	assert(c>0);
	p.capacite = c;
	p.pasExtension = extension;
	p.tab = new unsigned int[c];
	p.sommet = -1; 
}

/**
 * @brief D�sallouer une pile
 * @see initialiser, la pile a d�j� �t� initialis�e
 * @param[in,out] p : la pile � d�sallouer
 */
void detruire(Pile& p) {
	delete [] p.tab;
	p.tab = NULL;
}

/**
 * @brief Test de pile pleine
 * @param[in] p : la pile test�e
 * @return true si p est pleine, false sinon
 */
bool estPleine(const Pile& p) {
	return (p.sommet == (p.capacite-1));
}

/**
 * @brief Test de pile vide
 * @param[in] p : la pile test�e
 * @return true si p est vide, false sinon
 */
bool estVide(const Pile& p) {
	return (p.sommet == -1);
}

/**
 * @brief Lire l'unsigned int au sommet de pile
 * @param[in] p : la pile
 * @return la valeur de l'unsigned int au sommet de pile
 * @pre la pile n�est pas vide
 */
unsigned int sommet(const Pile& p) {
	assert(!estVide(p));
	return p.tab[p.sommet];
}

/**
 * @brief Empiler un unsigned int sur une pile si pile pleine ajoute de l'espace
 * @param[in,out] p : la pile
 * @param[in] it : l'unsigned int � empiler
 */
void empiler(Pile& p, const unsigned int& it) {
	if (estPleine(p) == true) {
		unsigned int* nPile;
		unsigned int newCapa = (p.capacite + 1) * p.pasExtension;
		nPile = new unsigned int[newCapa];
		
		for (int i = 0; i < p.capacite; ++i) {
			nPile[i] = p.tab[i];
		}

		p.capacite = newCapa;
		delete[] p.tab;
		p.tab = nPile;

		cout << "Extension - Allocaton/R�allocation de " << newCapa * sizeof(unsigned int)
			<< " octets (" << newCapa << " unsigned ints)." << endl;

	}
	p.sommet++;
	p.tab[p.sommet] = it;
}

/**
 * @brief D�piler l�unsigned int au sommet de pile
 * @param[in,out] p : la pile
 * @pre la pile n�est pas vide
 */
void depiler(Pile& p) {
	assert(!estVide(p));
	p.sommet--;
}
