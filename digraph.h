/* 
 * Squelette minimal pour la classe générique Digraph<T> du TP3.
 * TP3 -- Graphes orientés
 * UQAM / Département d'informatique
 * INF3105 - Structures de données et algorithmes (Hiver 2023)
 */
 

#ifndef __DIGRAPH_H__
#define __DIGRAPH_H__

#include <set>
#include <map>
#include <tuple>
#include <assert.h>
//#include <array>
//#include <vector>
//#include <deque>
//#include <forward_list>
//#include <list>
//#include <multiset>
//#include <multimap>
//#include <unordered_set>
//#include <unordered_map>
//#include <unordered_multiset>
//#include <unordered_multimap>
//#include <stack>
//#include <queue>
//#include <priority_queue>
//#include <limits>

/*
 * 	Remarque.
 *	Tout parcours des structures de données "map" et "set" doit se faire dans	
 *	l'ordre croissant (pour les valeurs numériques) ou l'ordre lexicographique
 *	(pour les caractères ou chaines de caractères). C'est le parcours implémenté
 *	dans le standard C++11 avec le compilateur g++.
 *	Par conséquent, lors de la recherche de circuits, c'est le premier circuit 
 *	induit par parcours en ordre croissant qui sera considéré dans les différents
 *	tests.
 */

template <class T>
class Digraph {
	// Vous n'avez pas le droit de modifier cette interface. Aucun ajout de fonction
	// publique n'est autorisé. Aucune modification des signatures ou des types de
	// retour des déclarations fonctions publiques n'est autorisé.
	public:
		Digraph();
		Digraph(const Digraph & autre);
		~Digraph();
		Digraph<T> & operator = (const Digraph<T> & autre);
		
		/*********** Fonctions pour les caractéristiques de graphe ***********/
		// Retourne le nombre de sommets dans graphe.
		int sommets() const;
		// Retourne le nombre d'arcs dans le graphe.
		int arcs() const;
		// Retourne "true" si "u" est un sommet du graphe courant. "false" si 
		// non.
		bool sommet(T u) const;
		// Retourne "true" si "(u,v)" est un arc du graphe courant. "false" si
		// non.
		bool arc(T u, T v) const;

		/*************************** Modificateurs ***************************/
		// Insère le sommet "u" si le graphe ne le contient pas. Ne fait 
		// rien si le graphe contient déjà le sommet "u".
		void inserer(T u);
		// Créé un arc entre les sommets "u" et "v" avec le poids "emprunt", 
		// si le graphe ne contient pas l'arc "(u, v)". Ne fait rien si le
		// graphe contient déjà un arc "(u,v)".
		// Si l'arc doit être créé faut s'assurer que,
		// 	- "u" doit être différent de "v",
		// 	- "emprunt" doit être strictement positif,
		// 		- faut arrêter l'exécution avec la fonction "assert" si les 
		// 		deux conditions plus faut ne sont pas satisfaites,
		// 	- si l'arc "(u,v)" existe déjà, peu importe la valeur de "emprunt",
		//	rien ne	sera fait par la fonction inserer.
		// 	- si l'un ou les deux sommets "u" et "v" n'existent pas dans
		// 	le graphe, ils seront crées.
		void inserer(T u, T v, double emprunt);
		// Supprime le sommet "u" et tous les arcs qui lui sont incidents.
		void supprimer(T u);
		// Supprime l'arc "(u, v)"
		void supprimer(T u, T v);

		/**************************** Sous-graphe ***************************/	
		// Créé un sous-graphe du graphe courant induit par les sommets du 
		// set "S".
		// Un "sous-graphe induit" par les sommets de "S" est un sous-graphe 
		// formé par les sommets de "S" et TOUS les arcs "e=(u,v)" du graphe 
		// courant tel que "u" et "v" sont TOUS deux des sommets de "S".
		//	- Il faut que tous les sommets listés dans "S" soient des
		//	sommets du graphe courant. Faut arrêter l'exécution avec la 
		//	fonction "assert" dans le cas	contraire.
		Digraph<T> cooperative(std::set<T> & S) const;
		
		/********************** Fonctions financières **********************/
		// Retourne le montant total que doit rembourser le sommet "u".
		double dette(T u) const;
		// De même, retourne le montant total que doivent rembourser tous 
		// les sommets du sous-graphe "SG" envers les autres sommets dans 
		// le reste du graphe courant. Attention, on ne comptabilise pas 
		// les dettes internes à "SG", on comptabilise que les dettes d'un 
		// sommet externe à "SG" vers un sommet interne de "SG".
		double dette(const Digraph<T> & SG) const;
		// Retourne le montant total des remboursements que doit recevoir 
		// le sommet "u".
		double pret(T u) const;
		// De même, retourne le montant total des remboursements que doivent
		// recevoir tous les sommets du sous-graphe "SG" de la part des 
		// autres sommets dans le reste du graphe courant. Attention, on ne 
		// comptabilise pas les remboursements internes à "SG", on 
		// comptabilise que les remboursements d'un sommet interne de "SG" 
		// vers un sommet externe à "SG".
		double pret(const Digraph<T> & SG) const;
		// Réduit les dettes circulaires du sommet "s". Voir des explications
		// et un exemple de l'énoncé.
		void reduire(T s);
		// De même, réduit les dettes circulaires d'un sous-graphe "SG". Voir
		// des explications et un exemple dans l'énoncé.
		void reduire(const Digraph<T> & SG);
	
	// Vous n'avez pas le droit de modifier l'attribut "graphe".
	// Vous n'avez pas le droit d'ajouter d'autres attributs privés.		
	private:
		
		// Par défaut, le "map" et le "set" sont parcourus en ordre croissant, 
		// ils sont ordonnés (standard C++11).
		std::map<T,std::set<std::tuple<T,double>>> graphe;
		
		// Vous pouvez ajouter toutes les fonctions privées que vous estimez
		// nécessaire.
};

// À compléter

#endif
