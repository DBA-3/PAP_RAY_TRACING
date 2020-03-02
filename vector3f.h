#ifndef VECTOR3F_H
#define VECTOR3F_H


/*!
 * \file vector3f.h
 * \brief Implémentation des vecteurs 3D
 */
#include <ostream>





/*!
 * \class Vector3f
 * \brief Classe représentant un vecteur dans l'espace
 *
 * La classe permet de générer des vecteurs et de réaliser des calculs sur ceux-ci
 */
class Vector3f
{
	private:
		float x_;      /*!< coordonnée sur l'axe X*/
		float y_;      /*!< coordonnée sur l'axe Y*/
		float z_;      /*!< coordonnée sur l'axe Z*/

	public:

	/*!
	 * \brief Constructeur
	 *
	 * Constructeur de la classe Vector3f
	 * \param <x> coordonnée du vecteur sur l'axe X
	 * \param <y> coordonnée du vecteur sur l'axe Y
	 * \param <z> coordonnée du vecteur sur l'axe Z
	 */
		Vector3f(float x, float y, float z);

	/*!
	 * \brief Constructeur de copie
	 *
	 * Constructeur de copie de la classe Vector3f
	 * \param v le vecteur à copier dans this
	 */
		Vector3f(const Vector3f & v);
		Vector3f();

		Vector3f & operator=(const Vector3f & v);

		/*!
		 * \brief Getter de la coordonnée sur l'axe X
		 */
		float x() const;
		/*!
		 * \brief Getter de la coordonnée sur l'axe Y
		 */
		float y() const;
		/*!
		 * \brief Getter de la coordonnée sur l'axe Z
		 */
		float z() const;

		/*!
		 * \brief calcul de la norme du vecteur
		 */
		float norm() const;

		/*!
		 * \brief normalise le vecteur en divisant tous les paramètres par la norme
		 */		
		void normalize();
};

	/*!
	* \brief Opérateur d'affichage des paramètres du vecteur
	* \param v Le vecteur à afficher
	*/
std::ostream & operator<<(std::ostream & st, const Vector3f & v);

	/*!
	* \brief Opérateur d'addition de vecteurs
	* \param v1 Le premier vecteur
	* \parma v2 Le deuxième vecteur
	*/
Vector3f operator+(const Vector3f & v1, const Vector3f & v2);

	/*!
	* \brief Opérateur de soustracton de vecteurs
	* \param v1 Le premier vecteur
	* \parma v2 Le deuxième vecteur
	*/
Vector3f operator-(const Vector3f & v1, const Vector3f & v2);

	/*!
	* \brief Renvoie le produit scalaire entre deux vecteurs
	* \param v1 Le premier vecteur
	* \parma v2 Le deuxième vecteur
	*/
float operator*(const Vector3f & v1, const Vector3f & v2);

	/*!
	* \brief Opérateur de multiplication de vecteurs par des sclaires
	* \param v Le premier vecteur
	* \pram d flotant
	*/
Vector3f operator*(const Vector3f & v, float d);

	/*!
	* \brief Opérateur de multiplication de vecteurs par des sclaires
	* \param d flotant
	* \param v Le premier vecteur
	*/
Vector3f operator*(float d, const Vector3f & v);

	/*!
	* \brief Opérateur de division de vecteurs par des sclaires
	* \param v1 Le premier vecteur
	* \param d flotant
	*/
Vector3f operator/(const Vector3f & v, float d);

	/*!
	* \brief Opérateur de preoduit vectoriel entre deux vecteurs
	* \param v1 Le premier vecteur
	* \parma v2 Le deuxième vecteur
	*/
Vector3f operator^(const Vector3f & v1, const Vector3f & v2);

	/*!
	* \brief Renvoie la distance entre deux vecteur de l'espace
	* \param v1 Le premier vecteur
	* \parma v2 Le deuxième vecteur
	*/
float dist(const Vector3f & v1, const Vector3f & v2);


#endif
