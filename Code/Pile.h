#ifndef _PILE_
#define _PILE_

/**
 * @file Pile.h
 * Projet sem04-cours-Cpp2
 * @author l'équipe pédagogique 
 * @version 1 - 29/11/2014
 * @brief Composant de pile à capacité paramétrée
 */

struct Pile {
	unsigned int capacite;  // capacité de la pile (c>0) 
	unsigned int pasExtension;
	unsigned int* tab;				// tableau des éléments de pile en mémoire dynamique
	int sommet;				// indice de sommet de pile dans tab
};

 /**
 * @brief Initialiser une pile vide
 * la pile est allouée en mémoire dynamique
 * @see detruire, pour une désallocation en fin d’utilisation
 * @param[out] p : la pile à initialiser
 * @param[in] c : capacité de la pile (nb maximum d‘items stockés)
 * @param[in] extension : le pas d'extension de la pile
 * @pre c>0
 */
void initialiser(Pile& p, unsigned int c, unsigned extension);


/**
 * @brief Désallouer une pile
 * @see initialiser, la pile a déjà été initialisée
 * @param[in,out] p : la pile à désallouer
 */
void detruire(Pile& p);

/**
 * @brief Test de pile pleine
 * @param[in] p : la pile testée
 * @return true si p est pleine, false sinon
 */
bool estPleine(const Pile& p);

/**
 * @brief Test de pile vide
 * @param[in] p : la pile testée
 * @return true si p est vide, false sinon
 */
bool estVide(const Pile& p);

/**
 * @brief Lire l'item au sommet de pile
 * @param[in] p : la pile
 * @return la valeur de l'item au sommet de pile
 * @pre la pile n’est pas vide
 */
unsigned int sommet(const Pile& p);

/**
 * @brief Empiler un item sur une pile si pile pleine ajoute de l'espace
 * @param[in,out] p : la pile
 * @param[in] it : l'item à empiler
 */
void empiler(Pile& p, const unsigned int& it);

/**
 * @brief Dépiler l’item au sommet de pile
 * @param[in,out] p : la pile
 * @pre la pile n’est pas vide
 */
void depiler(Pile& p);

#endif


