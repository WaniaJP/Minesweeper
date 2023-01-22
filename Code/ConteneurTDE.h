/**
 * @file ConteneurTDE.h
 * Projet Minesweeper
 * @author l'�quipe p�dagogique et Wania Jean-Pierre
 * @version 4 08/01/22
 * @brief Composant de ConteneurTDE
 */

#include <iostream>
#include <cassert>
using namespace std;



/** @brief Conteneur d'unsigned ints allou�s en m�moire dynamique
 *  de capacit� extensible suivant un pas d'extension
 */
struct ConteneurTDE {
	unsigned int capacite; 	   // capacit� du conteneur (>0)
	unsigned int pasExtension; // pas d'extension du conteneur (>0)
	unsigned int nbElemDansTab = 0;
	unsigned int* tab;		   // conteneur allou� en m�moire dynamique
};

/*
 * @brief Initialise un conteneur d'unsigned int 
 * Allocation en m�moire dynamique du conteneur d'items
 * de capacit� (capa) extensible par pas d'extension (p)
 * @see detruire, pour sa d�sallocation en fin d'utilisation
 * @param[out] c : le conteneur d'items
 * @param [in] capa : capacit� du conteneur
 * @param [in] p : pas d'extension de capacit�
 * @pre capa>0 et p>0
 */
void initialiser(ConteneurTDE& c, unsigned int capa, unsigned int p);

/**
 * @brief D�salloue un conteneur d'items en m�moire dynamique
 * @see initialiser, le conteneur d'unsigned int a d�j� �t� allou�
 * @param[out] c : le conteneur d'unsigned int
 */
void detruire(ConteneurTDE& c);

/**
 * @brief Lecture d'un unsigned int d'un conteneur d'unsigned int
 * @param[in] c : le conteneur d'unsigned int
 * @param[in] i : la position de l'unsigned int dans le conteneur
 * @return l'unsigned int � la position i
 * @pre i < c.capacite
 */
unsigned int lire(const ConteneurTDE& c, int i);

/**
 * @brief Ecrire un unsigned int dans un conteneur d'unsigned int
 * @param[in,out] c : le conteneur d'unsigned int
 * @param[in] i : la position o� ajouter/modifier l'item
 * @param[in] it : l'unsigned int � �crire
 */
void ecrire(ConteneurTDE& c, unsigned int i, unsigned int it);


/* @brief G�n�re un nouveau coup 
*/
void nvCoup();

/* 
* @brief Remplie grille   
*  @param[in] nombreCharLigne : au nombre max de caractere dans une ligne    
*  @param[in] *tab : le tableau  
*  @param[in] nbrL : nombre de ligne dans la grille  
*  @param[in-out] posNbMineCase : nombre de ligne dans la grille  

*/
void remplissageGrille(unsigned int nombreCharLigne, int* tab, unsigned int nbrL, ConteneurTDE& posNbMineCase);

/**
* @brief Echange les valeurs des indices i et j dans un tableau
* @param[in-out] c : le conteneur
* @param[in] i : le premier indice
* @param[in] j : le deuxieme indice
*/

void echanger(ConteneurTDE& c, unsigned int i, unsigned int j);


/**
* @brief S�lectionne le pivot et tri une partie du tableau
* @param[in-out] c : le conteneur
* @param[in] tableauGrille : la grille remplie 
* @param[in] debut : le premier indice
* @param[in] fin : le deuxieme indice
* return un indice
*/
int repartition(ConteneurTDE& c, int* tableauGrille, int debut, int fin);


/**
* @brief Fait des appels r�cursifs pout trier la partie gauche et droite du pivot
* @param[in-out] c : le conteneur
* @param[in] tableauGrille : la grille remplie 
* @param[in] debut : le premier indice
* @param[in] fin : le deuxieme indice
*/
void TriRapideRec(ConteneurTDE& c, int* tableauGrille, int debut, int fin);


/* Tri rapide dans l'ordre d�croissant d'un tableau
* @param[in-out] c : le conteneur
* @param[in] tableauGrille : la grille remplie 
*/
void TriRapide(ConteneurTDE& c, int* tableauGrille);


/*
* @brief Indique s'il y a des cases d�couvertes sans mines proches, � proximit� de la case masqu�e
* @param[in] tabGrille : un tableau de statut
* @param[in] nbrC : nombre de colonnes
* @param[in] nbrL : nombre de lignes
* @param[in] caseMasque : la case � v�rifier
* @return true ou false
*/
bool checkZero(int* tabGrille, unsigned int nbrC, unsigned int nbrL, unsigned int caseMasque);

/*
* @brief Remplie le conteneur caseMasqueProxi qui contient les positions des cases masqu�s autour d'une autre donn�e et indique si on peut marquer une case
* @param[in] tableauGrille : tableau de statut
* @param[in] caseMineProx : la case trait�
* @param[in-out] caseMasqueProxi : le conteneur remplie
* @param[in] nbrC : le nombre de colonnes
* @param[in] nbrL : le nombre de lignes
* @return true ou false
*/
bool checkCarre(int* tableauGrille, unsigned int CaseMineProx, ConteneurTDE& caseMasqueProxi, unsigned int nbrC, unsigned int nbrL);



/**
* @brief Remplie le conteneur caseMasqueProxi qui contient les positions des cases masqu�s autour d'une autre donn�e et indique si on peut marquer une case
* @param[in] tableauGrille: tableau de statut  
* @param[in] CaseMineProx : case actuelle
* @param[in-out] caseMasqueProxi : le conteneur rempli
* @param[in] nbrC : nombre de colonnes  
* @param[in] nbrL : nombre de lignes
* return true ou false
*/
bool checkCarrePourMarque(int* tableauGrille, unsigned int CaseMineProx, ConteneurTDE& caseMasqueProxi, unsigned int nbrC, unsigned int nbrL);