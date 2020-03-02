#ifndef SPHERE_H
#define SPHERE_H

/*!
 * \file sphere.h
 * \brief Implémentation des sphères
 */

#include "shape.h"

/*!
 * \class Sphere
 * \brief Classe représentant une sphère
 *
 * Sphere représentée dans l'espace par son centre et son rayon
 */

class Sphere : public Shape
{
	private:
		Vector3f origin_;           /*!< Centre de la sphere */
		float radius_;              /*!< Rayon de la sphere */

	public:
	/*!
	 * \brief Constructeur
	 *
	 * Constructeur de la classe Sphere
	 * \param <matter> le matériau dont la sphère est composée
	 * \param <origin> le centre de la sphère
	 * \param <radius> le rayon de la sphère
	 */
		Sphere(Material matter, Vector3f origin, float radius);

		bool is_hit(const Ray3f ray);
		Ray3f reflect(const Ray3f ray) const;

	/*!
	 * \brief Getter pour le centre de la Sphere
	 */	
		Vector3f origin() const;
	/*!
	 * \brief Getter pour le rayon de la Sphere
	 */	
		float radius() const;
};


	/*!
	* \brief Opérateur d'affichage des paramètres de la Sphere
	*/
std::ostream & operator<<(std::ostream & st, const Sphere & s);


#endif
