#ifndef RAY3F_H
#define RAY3F_H
/*!
 * \file ray3f.h
 * \brief Implémentation d'un rayon dans l'espace
 */
#include "vector3f.h"


/*!
 * \class Ray3f
 * \brief Classe représentant un rayon dans l'espace
 *
 * Représente un rayon par son origine et sa direction
 */

class Ray3f
{
	private:
		Vector3f origin_;               /*!< Origine du rayon */
		Vector3f direction_;            /*!< Direction du rayon */

	public:
	/*!
	 * \brief Constructeur
	 *
	 * Constructeur de la classe Ray3f
	 * \param <ori> Origine du rayon
	 * \param <dir> Direction du rayon
	 */
		Ray3f(const Vector3f & ori, const Vector3f & dir);
	/*!
	 * \brief Constructeur de Copie
	 *
	 * Constructeur de copie de la classe Ray3f
	 * \param <r> Référence vers un autre rayon
	 */
		Ray3f(const Ray3f & r);

		Ray3f & operator=(const Ray3f & r);

	/*!
	* \brief Getter pour l'origine du rayon
    */
		Vector3f origin() const;
	/*!
	* \brief Getter pour la direction du rayon
    */
		Vector3f direction() const;
};

	/*!
	* \brief Opérateur d'affichage des coordonnées du vecteur origine et direction
	*/

std::ostream & operator<<(std::ostream & st, const Ray3f & v);



#endif
