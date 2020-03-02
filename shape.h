#ifndef SHAPE_H
#define SHAPE_H

/*!
 * \file shapes.h
 * \brief Implémentation abstraite des formes en 3D
 */

#include "ray3f.h"
#include "material.h"

/*!
 * \class Shape
 * \brief Classe abstraite des formes en 3D
 *
 * Classe abstraite pure dont héritent les autres formes géométriques
 */

class Shape
{
	protected:
		Material matter_;          /*!< Le matériau en quoi est fait la forme */

	public:
	/*!
	 * \brief Constructeur de Shape
	 *
	 * Constructeur de la classe abstraite Shape, appelé par les classes filles
	 */
		Shape(Material matter) : matter_(matter) {}


	/*!
	 * \brief Test d'intersection 
	 *
	 * Methode permettant de savoir si le rayon touche l'objet ou non
	 * \param ray Le rayon de lumière que l'on doit vérifier s'il touche l'objet ou non
	 * \return bool 
	 */
		virtual bool is_hit(const Ray3f ray) = 0;

	/*!
	 * \brief  Récupération du rayon réfléchi 
	 *
	 * Méthode permettant de savoir le point d'origine du rayon réfléchi et sa direction
	 * \param ray Le rayon de lumière qui doit traverser l'objet
	 * \return Ray3f 
	 */
		virtual Ray3f reflect(const Ray3f ray) const = 0;

	/*!
	 * \brief Getter pour le materiau du Shape
	 */	
		Material matter() const {return matter_;}
};

#endif
