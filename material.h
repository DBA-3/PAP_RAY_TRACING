#ifndef MATERIAL_H
#define MATERIAL_H

#include <ostream>


/*!
 * \file material.h
 * \brief Représentation d'un matériau
 */


class Material
{
	/*!
 * \class Material
 * \brief Classe représentant un matériau
 *
 * La classe représente un matériau par sa couleur et sa brillance
 */
	private:
		float r_;        /*!< niveau de rouge valant entre 0 et 255 */
		float g_;        /*!< niveau de vert valant entre 0 et 255 */
		float b_;	     /*!< niveau de bleu valant entre 0 et 255 */
		float shiness_;  /*!< Brillance*/

	public:
	/*!
	 * \brief Constructeur
	 *
	 * Constructeur de la classe Material
	 *
	 * \param <r> niveau de Rouge de la couleur
	 * \param <g> niveau de Vert de la couleur
	 * \param <b> niveau de Bleu de la couleur
	 * \param <s> Brillance du matériau
	 */
		Material(float r, float g, float b, float shiness);
	/*!
	 * \brief Constructeur de Copie
	 *
	 * Constructeur de copie de la classe Material
	 *
	 * \param <Material & m> référence à un autre matériau
	 */
		Material(const Material & m);
	
	/*!
	* \brief Getter du niveau de rouge du matériau
	*/
		float r() const;
	/*!
	* \brief Getter du niveau de vert du matériau
	*/
		float g() const;
	/*!
	* \brief Getter du niveau de bleu du matériau
	*/
		float b() const;
	/*!
	* \brief Getter de la brillance du matériau
	*/
		float shiness() const;
};

	/*!
	* \brief Opérateur d'affichage des niveaux de couleur et de la brillance du matériau
	*/

std::ostream & operator<<(std::ostream & st, const Material & m);


#endif
