#ifndef QUAD_H
#define QUAD_H

#include "shape.h"

/*!
 * \file quad.h
 * \brief Implémentation des Parallélépipèdes rectangles
 */


/*!
 * \class Quad
 * \brief Représentation des Parallélépipèdes rectangles
 *
 * Classe dérivant de Shape : Représentation des Parallélépipèdes rectangles par le centre du Parallélépipède, sa hauteur, sa largeur et sa longueur.
 */
class Quad : public Shape
{

	private:
		Vector3f origin_;  /*!Coordonnées du centre du Parallélépipède*/
		float width_;      /*!Largeur du Parallélépipède*/
		float height_;     /*!Hauteur du Parallélépipède*/
		float depth_;      /*!Longueur du Parallélépipède*/

	public:
	/*!
	 * \brief Constructeur
	 *
	 * Constructeur de la classe Quad
	 * Attention, si les paramètres de taille ne sont pas positifs le constructeur ne crée pas l'instance
	 * \param <matter> le matériau dont est fait le Quad
	 * \param <origin> le centre du Quad
	 * \param <width> la largeur du Quad
	 * \param <height> la hauteur du Quad
	 * \param <depth> la longueur du Quad
	 */
		Quad(Material matter, Vector3f origin, float width, float height, float depth);

		bool is_hit(const Ray3f ray);
		Ray3f reflect(const Ray3f ray) const;

    /*!
	* \brief Getter pour le vecteur au centre du Quad
    */
		Vector3f origin() const;
	/*!
	* \brief Getter pour la largeur du Quad
    */
		float width() const;
	/*!
	* \brief Getter pour la hauteur du Quad
    */
		float height() const;
	/*!
	* \brief Getter pour la longueur du Quad
    */
		float depth() const;
};

	/*!
	* \brief Opérateur d'affichage des paramètres du Quad
	*/
std::ostream & operator<<(std::ostream & st, const Quad & q);


#endif