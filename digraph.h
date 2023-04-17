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
// #include <array>
// #include <vector>
// #include <deque>
// #include <forward_list>
// #include <list>
// #include <multiset>
// #include <multimap>
// #include <unordered_set>
// #include <unordered_map>
// #include <unordered_multiset>
// #include <unordered_multimap>
#include <stack>
// #include <queue>
// #include <priority_queue>
// #include <limits>

#include <iostream>

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
class Digraph
{
	// Vous n'avez pas le droit de modifier cette interface. Aucun ajout de fonction
	// publique n'est autorisé. Aucune modification des signatures ou des types de
	// retour des déclarations fonctions publiques n'est autorisé.
public:
	Digraph();
	Digraph(const Digraph &autre);
	~Digraph();
	Digraph<T> &operator=(const Digraph<T> &autre);

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
	Digraph<T> cooperative(std::set<T> &S) const;

	/********************** Fonctions financières **********************/
	// Retourne le montant total que doit rembourser le sommet "u".
	double dette(T u) const;
	// De même, retourne le montant total que doivent rembourser tous
	// les sommets du sous-graphe "SG" envers les autres sommets dans
	// le reste du graphe courant. Attention, on ne comptabilise pas
	// les dettes internes à "SG", on comptabilise que les dettes d'un
	// sommet externe à "SG" vers un sommet interne de "SG".
	double dette(const Digraph<T> &SG) const;
	// Retourne le montant total des remboursements que doit recevoir
	// le sommet "u".
	double pret(T u) const;
	// De même, retourne le montant total des remboursements que doivent
	// recevoir tous les sommets du sous-graphe "SG" de la part des
	// autres sommets dans le reste du graphe courant. Attention, on ne
	// comptabilise pas les remboursements internes à "SG", on
	// comptabilise que les remboursements d'un sommet interne de "SG"
	// vers un sommet externe à "SG".
	double pret(const Digraph<T> &SG) const;
	// Réduit les dettes circulaires du sommet "s". Voir des explications
	// et un exemple de l'énoncé.
	void reduire(T s);
	// De même, réduit les dettes circulaires d'un sous-graphe "SG". Voir
	// des explications et un exemple dans l'énoncé.
	void reduire(const Digraph<T> &SG);

	// Vous n'avez pas le droit de modifier l'attribut "graphe".
	// Vous n'avez pas le droit d'ajouter d'autres attributs privés.
private:
	// Par défaut, le "map" et le "set" sont parcourus en ordre croissant,
	// ils sont ordonnés (standard C++11).
	std::map<T, std::set<std::tuple<T, double>>> graphe;

	// Vous pouvez ajouter toutes les fonctions privées que vous estimez
	// nécessaire.
	bool trouverChemin(T s, std::stack<T> &path, std::set<T> &visited, T &depart);
	bool trouverChemin(T s, std::stack<T> &path, std::set<T> &visited, std::set<T> &depart, const Digraph<T> &SG);
	void modifierDette(T u, T v, double montant);

	std::set<T> trouver_frontiere(const Digraph<T> &SG);
};

// À compléter
template <class T>
Digraph<T>::Digraph()
{
	// À compléter
}

template <class T>
Digraph<T>::Digraph(const Digraph &autre)
{
	graphe.clear();
	graphe = autre.graphe;
}

template <class T>
Digraph<T>::~Digraph()
{
	// À compléter
}

// O(n)
template <class T>
Digraph<T> &Digraph<T>::operator=(const Digraph<T> &autre)
{

	graphe.clear();		   // complexité linéaire
	graphe = autre.graphe; // pareil
	return *this;
}

// O(1)
template <class T>
int Digraph<T>::sommets() const
{
	return graphe.size();
}

// O(n)
template <class T>
int Digraph<T>::arcs() const
{
	int totalArcs = 0;
	// le type de l'itérateur ici est std::map<T, std::set<std::tuple<T, double>>>::iterator
	// par soucis de lisibilité on utilisera auto pour toutes les itérations sur std::map
	for (auto it = graphe.begin(); it != graphe.end(); ++it)
	{
		totalArcs += it->second.size();
	}
	return totalArcs;
}

// O(log n)
template <class T>
bool Digraph<T>::sommet(T u) const
{
	auto it = graphe.find(u);
	return it != graphe.end();
}
// O(n)
template <class T>
bool Digraph<T>::arc(T u, T v) const
{
	auto it = graphe.find(u); // O(log n)

	if (it != graphe.end())
	{										 // vérifie si it existe dans le graphe
		for (const auto &tuple : it->second) // O(n)
		{
			if (std::get<0>(tuple) == v)
			{ // vérifie si l'arc u -> v existe
				return true;
			}
		}
	}

	// Si aucun des deux arcs n'existe, retourne false
	return false;
}
// O(log n)
template <class T>
void Digraph<T>::inserer(T u)
{
	// vérifier que u n'est pas déjà dans le graphe
	auto it = graphe.find(u); // O(log n)
	if (it == graphe.end())
	{
		std::set<std::tuple<T, double>> emptySet;
		graphe.insert(std::make_pair(u, emptySet)); // O(log n)
	}
}

// O(n)
template <class T>
void Digraph<T>::inserer(T u, T v, double emprunt)
{
	// on commence par vérifier que u et v sont bien différents
	assert(u != v);

	// on vérifie que emprunt est positif
	assert(emprunt > 0);

	// on ajoute u v comme sommet (la fonction inserer vérifie que u n'est pas déjà dans le graphe)
	inserer(u); // O(log n)
	inserer(v); // O(log n)

	auto it = graphe.find(u); // O(log n)
	// on ajoute le tuple (v, emprunt) s'il n'existe pas déjà un tuple avec la même valeur de v
	auto &s = it->second;
	bool tuple_existe = false;
	for (const auto &tuple : s) // O(n)
	{
		if (std::get<0>(tuple) == v)
		{
			tuple_existe = true;
			break;
		}
	}
	if (!tuple_existe)
	{
		s.insert(std::make_tuple(v, emprunt)); // O(log n)
	}
}

// O(n²log n)
template <class T>
void Digraph<T>::supprimer(T u)
{

	// O(nlog(n))
	// TODO CETTE PARTIE N'EST PAS DU TOUT OPTIMISÉ À MON AVIS
	// MAIS C'EST PAS TRÈS IMPORTANT CAR LA SUPPRESSION DES ARCS EST DE PLUS GRANDE COMPLEXITE
	// Supprimer le sommet u
	auto it = graphe.find(u); // O(log n)
	if (it != graphe.end())
	{
		for (auto adjacent : it->second) // O(n)
		{
			T sommet_adjacent = std::get<0>(adjacent);

			// O(log n)
			graphe[sommet_adjacent].erase(std::make_tuple(u, std::get<1>(adjacent)));
		}
		graphe.erase(it);
	}

	// Supprimer les arcs associés à u
	for (auto &pair : graphe) // O(n)
	{
		for (auto adjacent : pair.second) // O(n)
		{
			if (std::get<0>(adjacent) == u)
			{
				// O(log n)
				pair.second.erase(std::make_tuple(u, std::get<1>(adjacent)));
				break;
			}
		}
	}
}

// O(n log n)
// pas trop sur de la complexité de erase
template <class T>
void Digraph<T>::supprimer(T u, T v)
{
	// std::cout << "Suppression de " << u  << " " << v<< std::endl;

	auto it = graphe.find(u); // O(log n)
	if (it != graphe.end())
	{
		// Supprimer l'arc (u, v)
		for (auto iter = it->second.begin(); iter != it->second.end(); ++iter) // O(n)
		{
			if (std::get<0>(*iter) == v)
			{
				// O(log n)
				it->second.erase(iter);
				break;
			}
		}
	}
}
// O(log(n) * n**3)
template <class T>
Digraph<T> Digraph<T>::cooperative(std::set<T> &S) const
{
	Digraph<T> result;
	// std::cout << std::endl << "NOUVELLE COOPERATIVE = ";
	for (auto &sommet : S) // O(n)
	{
		result.inserer(sommet); // O(log n)
								// std::cout << sommet << " ";
	}

	// std::cout << std::endl;
	for (auto it = graphe.begin(); it != graphe.end(); ++it) // O(n)
	{
		if (S.find(it->first) != S.end()) // O(log n)
		{
			// std::cout << "inserer " << it->first << std::endl;
			result.inserer(it->first);											// O(log n)
			for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) // O(n)
			{
				if (S.find(std::get<0>(*it2)) != S.end()) // log(n)
				{
					// std::cout << "inserer " << std::get<0>(*it2) << std::endl;
					result.inserer(it->first, std::get<0>(*it2), std::get<1>(*it2)); // O(n)
				}
			}
		}
	}
	return result;
}

// O(n**2)
template <class T>
double Digraph<T>::dette(T u) const
{

	double result = 0;
	for (auto it = graphe.begin(); it != graphe.end(); ++it) // O(n)
	{
		for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) // O(n)
		{
			if (std::get<0>(*it2) == u)
				result += std::get<1>(*it2);
		}
	}
	return result;
}
// O(n**2 * log(n**2))
template <class T>
double Digraph<T>::dette(const Digraph<T> &SG) const
{
	double result = 0;
	for (auto const &sommet : graphe)
	{
		if (!SG.sommet(sommet.first))
		{
			for (auto const &adjacent : sommet.second)
			{
				if (SG.sommet(std::get<0>(adjacent)))
				{
					result += std::get<1>(adjacent);
				}
			}
		}
	}
	return result;
}

// O(n log n)
template <class T>
double Digraph<T>::pret(T u) const
{
	double result = 0;
	auto it = graphe.find(u);
	if (it != graphe.end())
	{
		for (auto adjacent : it->second)
		{
			result += std::get<1>(adjacent);
		}
	}
	return result;
}

// O(n**2 log n)
template <class T>
double Digraph<T>::pret(const Digraph<T> &SG) const
{
	double result = 0;

	for (auto const &sommet : graphe)
	{
		if (SG.sommet(sommet.first))
		{
			for (auto const &adjacent : sommet.second)
			{
				if (!SG.sommet(std::get<0>(adjacent)))
				{
					result += std::get<1>(adjacent);
				}
			}
		}
	}

	return result;
}

template <class T>
void Digraph<T>::reduire(T depart)
{

	std::stack<T> path;
	std::set<T> visited;
	path.push(depart);

	while (trouverChemin(depart, path, visited, depart))
	{

		// on trouve le minimum
		std::stack<T> copyPath = path;
		double min = 0;
		while (!copyPath.empty())
		{
			T debiteur = copyPath.top();
			copyPath.pop();
			if (copyPath.empty())
				break;
			T creancier = copyPath.top();

			// On trouve l'arc (debiteur, creancier)
			auto it = graphe.find(creancier);

			for (const auto &tuple : it->second)
			{
				if (std::get<0>(tuple) == debiteur)
				{ // vérifie si l'arc u -> v existe
					if (min == 0 || std::get<1>(tuple) < min)
					{
						min = std::get<1>(tuple);
					}
				}
			}
		}

		// Une fois qu'on a trouvé le minimum, on le soustrait à toutes les dettes
		while (!path.empty())
		{
			T debiteur = path.top();
			path.pop();
			if (path.empty())
				break;
			T creancier = path.top();

			// On trouve l'arc (creancier, debiteur)
			modifierDette(creancier, debiteur, min);
		}

		path = std::stack<T>();
		visited = std::set<T>();
		path.push(depart);
	};
}
template <class T>
bool Digraph<T>::trouverChemin(T s, std::stack<T> &path, std::set<T> &visited, T &depart)
{
	if (s == depart && visited.size() > 0)
	{
		return true;
	}

	auto it = graphe.find(s);

	if (it != graphe.end())
	{
		// on vérifie que le sommet n'est pas un noeud de sortie
		if (it->second.size() == 0)
		{
			return false;
		}

		// on boucle récursivement sur les sommets adjacents qui ne sont pas dans visited
		for (auto adjacent : it->second)
		{
			if (visited.find(std::get<0>(adjacent)) == visited.end())
			{
				visited.insert(std::get<0>(adjacent));
				path.push(std::get<0>(adjacent));
				if (trouverChemin(std::get<0>(adjacent), path, visited, depart))
				{
					return true;
				}
				else
				{
					path.pop();
				}
			}
		}
	}
	return false;
}

template <class T>
bool Digraph<T>::trouverChemin(T s, std::stack<T> &path, std::set<T> &visited, std::set<T> &depart, const Digraph<T> &SG)
{
	// std::cout << "reduireNoeud" << std::endl;
	// std::cout << "s = " << s << std::endl;
	// std::cout << s << " ";
	if (depart.find(s) != depart.end() && visited.size() > 0)
	{
		// std::cout << std::endl;
		return true;
	}

	auto it = graphe.find(s);

	if (it != graphe.end())
	{
		// on vérifie que le sommet n'est pas un noeud de sortie
		if (it->second.size() == 0)
		{
			return false;
		}

		// on boucle récursivement sur les sommets adjacents qui ne sont pas dans visited
		for (auto adjacent : it->second)
		{
			// le sommet ne doit pas être dans les sommets visités
			// il faut faire aussi attention à ne pas prendre les sommets qui sont dans la frontière au départ
			if (visited.find(std::get<0>(adjacent)) == visited.end() && !(SG.sommet(std::get<0>(adjacent)) && SG.sommet(s)))
			{
				visited.insert(std::get<0>(adjacent));
				path.push(std::get<0>(adjacent));
				if (trouverChemin(std::get<0>(adjacent), path, visited, depart, SG))
				{
					return true;
				}
				else
				{
					path.pop();
				}
			}
		}
	}
	return false;
}

template <class T>
void Digraph<T>::modifierDette(T u, T v, double montant)
{
	auto it = graphe.find(u);

	for (auto iter = it->second.begin(); iter != it->second.end(); iter++)
	{
		if (std::get<0>(*iter) == v)
		{
			// *iter = std::make_tuple(std::get<0>(*iter), std::get<1>(*iter) - montant);

			if (std::get<1>(*iter) - montant > 0)
			{
				it->second.insert(std::make_tuple(std::get<0>(*iter), std::get<1>(*iter) - montant));
			}
			else
			{
				// std::cout << "On supprime l'arc " << u << " -> " << v << " de " << montant << std::endl;
			}
			it->second.erase(iter);
			break;
		}
	}
}

template <class T>
void Digraph<T>::reduire(const Digraph<T> &SG)
{
	std::set<T> frontiere = trouver_frontiere(SG);
	// std::cout << "frontiere : ";
	for (const auto &depart : frontiere)
	{
		// std::cout << "sommet frontiere en cours : ";
		// std::cout << depart << std::endl;
		std::stack<T> path;
		std::set<T> visited;
		path.push(depart);

		while (trouverChemin(depart, path, visited, frontiere, SG))
		{
			// std::cout << "############ WHILE START ############" << std::endl;
			// on trouve le minimum
			std::stack<T> copyPath = path;
			double min = 0;
			// std::cout << "on cherche le minimum " << std::endl;
			while (!copyPath.empty())
			{

				T debiteur = copyPath.top();
				copyPath.pop();
				if (copyPath.empty())
					break;
				T creancier = copyPath.top();

				// std::cout << creancier << " -> " << debiteur << std::endl;

				// On trouve l'arc (debiteur, creancier)
				auto it = graphe.find(creancier);

				for (const auto &tuple : it->second)
				{
					if (std::get<0>(tuple) == debiteur)
					{ // vérifie si l'arc u -> v existe
						if (min == 0 || std::get<1>(tuple) < min)
						{
							min = std::get<1>(tuple);
						}
					}
				}
			}
			// std::cout << "min = " << min << std::endl;

			T arrive = path.top();

			// Une fois qu'on a trouvé le minimum, on le soustrait à toutes les dettes
			while (!path.empty())
			{
				T debiteur = path.top();
				path.pop();
				if (path.empty())
					break;
				T creancier = path.top();

				// On trouve l'arc (creancier, debiteur)
				modifierDette(creancier, debiteur, min);
			}
			// std::cout << "on a soustrait le minimum" << std::endl;
			// std::cout << "depart = " << depart << std::endl;
			// std::cout << "arrive = " << arrive << std::endl;
			// il faut maintenant modifier les dettes entre arrive et depart
			if (depart == arrive)
			{
				// std::cout << "depart = arrive" << std::endl;
			}
			else if (arc(arrive, depart))
			{
				modifierDette(arrive, depart, min);
			}
			else if (arc(depart, arrive))
			{
				modifierDette(depart, arrive, -min);
			}
			else
			{
				inserer(depart, arrive, min);
			}
			path = std::stack<T>();
			visited = std::set<T>();
			path.push(depart);

			// std::cout << "############ WHILE END ############" << std::endl;
		}
	}
}

template <class T>
std::set<T> Digraph<T>::trouver_frontiere(const Digraph<T> &SG)
{
	std::set<T> frontiere;
	// std::cout << "frontiere : ";
	for (const auto &pair : graphe)
	{

		for (const auto &tuple : pair.second)
		{
			if (SG.sommet(pair.first) && !SG.sommet(std::get<0>(tuple)) && frontiere.find(pair.first) == frontiere.end())
			{
				// std::cout << pair.first << " ";
				frontiere.insert(pair.first);
			}
			if (!SG.sommet(pair.first) && SG.sommet(std::get<0>(tuple)) && frontiere.find(std::get<0>(tuple)) == frontiere.end())
			{
				frontiere.insert(std::get<0>(tuple));
				// std::cout << std::get<0>(tuple) << " ";
			}
		}
	}
	// std::cout << std::endl;

	return frontiere;
}

#endif
