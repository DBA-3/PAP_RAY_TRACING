#ifndef CAMERA_H
#define CAMERA_H


/*!
 * \file camera.h
 * \brief Représentation d'une camera, similaire à un rayon
 */

#include "vector3f.h"


/*!
 * \class Camera
 * \brief Classe représentant la caméra
 *
 * Représentation d'une caméra dans l'espace avec une implémentation similaire à Ray3f
 */

class Camera
{
	private:
		Vector3f position_;           /*!< Position de la caméra */
		Vector3f direction_;          /*!< Direction de la caméra */

	public:
		/*!
		 * \brief Constructeur
		 *
		 * Constructeur de la classe Camera
		 * \param <pos> la position de la caméra
		 * \param <dir> la direction de la caméra
		 */
		Camera(const Vector3f & pos, const Vector3f & dir);

		/*!
		 * \brief Constructeur de Copie
		 *
		 * Constructeur de Copie de la classe Camera
		 * \param <r> référence d'une Camera
		 */
		Camera(const Camera & r);

		//TODO//
		Camera & operator=(const Camera & r);

		/*!
		 * \brief Getter de la position de la Camera
		 * retourne le Vector3f de la position de la Camera
		 */
		Vector3f position() const;
		/*!
		 * \brief Getter pour la direction de la Camera
		 * retourne le Vector3f de la direction de la Camera
		 */
		Vector3f direction() const;
};

   /*!
	* \brief Opérateur d'affichage des paramètres de la Camera
	*/

std::ostream & operator<<(std::ostream & st, const Camera & c);


#endif