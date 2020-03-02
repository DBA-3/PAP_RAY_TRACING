#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "shape.h"


/*!
 * \file scene.h
 * \brief Représentation de la scène
 */

/*!
 * \class Scene
 * \brief Classe permettant le rendu de la scène
 *
 * Contient toutes les informations pour pouvoir faire le rendu: la caméra, la lumière, et la liste des pointeurs sur les formes
 */
class Scene
{

	Camera camera_;         /*!< La camera */
	Shape* *shapes_;        /*!< Tableau de pointeurs des formes */
	Ray3f source_;          /*!< Source de lumiere */

	public:
	/*!
	 * \brief Constructeur
	 *
	 * Constructeur de la classe Scene
	 * \param camera la camera
	 * \param Shape tableau abstrait contenant des pointeurs vers des shapes
	 * \param source Ray3f qui représente la source de lumiere
	 */
		Scene(Camera camera, Shape* *shapes, Ray3f source);
	/*!
	 * \brief Constructeur de Copie
	 *
	 * \param s La scene dont les paramètre sont copiées
	 */
		Scene(const Scene & s);

	/*!
	* \brief Getter pour la camera de la scene
	*/
		Camera camera() const;
	/*!
	* \brief Getter pour le pointeur des shapes
	*/
		Shape* *shapes() const;
	/*!
	* \brief Getter pour la source de lumière de la scene
	*/
		Ray3f source() const;

	/*!
	 * \brief Rendu de la scene
	 *
	 * La fonction principale du projet. Cree un rendu de la scene vu depuis la camera, au nom de filename. nb_shapes doit contenir le nombre de formes dans shapes_ à afficher. ref_max est le nombre de reflections maximales  à réaliser pour chaque rayon. Shading est un bool qui indique si on doit prendre en compte l'angle d'incidence sur les objet. Plus cet angle est grand plus la lumière est atténuée.
	 * L'image est creee dans le dossier contenant l'executable
	 * \param width largeur de l'image > 0
	 * \param height hauteur de l'image > 0
	 * \param nb_pixel_rox nombre de pixels sur les lignes
	 * \param nb_pixel_col nombre de pixels sur les colonnes 
	 * \param nb_shapes le nombre de formes à afficher 
	 * \param filename string non vide
	 * \param ref_max nombre de reflections maximales à réaliser
	 * \param shading booléen, si vrai prend en compte l'incidence de la lumière sur les objets pour le rendu
	 */
		void render(int width, int height, int nb_pixel_row, int nb_pixel_col, int nb_shapes, char* filename, int ref_max, bool shading);

	/*!
	* \brief renvoie l'indice de shapes du premier objet touché par le rayon, si aucun objet n'est touché, renvoie -1
	*
	* \param nb_shapes nombre de shapes
	* \param start Rayon dont on cherche le premier objet touché 
	*/
		int closer(int nb_shapes, Ray3f start);

	/*!
	* \brief modifie ray et shine 
	*
	*	modifie les tableaux pour qu'ils contiennent respectivement les rayon réfléchis et les coeffiscients de shiness des objets touchés en prenant en compte un nombre maximal de reflexions.
	* \param ray doit contenir un premier rayon représentant la direction de la camera
	* \param nb_shapes nombre des formes
	* \param ref_max nombre maximal de reflections
	* \param shines tableau de flotant 
	*/	
		void reflected_rays(Ray3f **ray, int nb_shapes, int ref_max, float* shine);

	/*!
	* \brief récupère le tableau de shiness et modifie les coeffiscients de reflexion
	*
	* En prenant en compte les coeffiscients de shiness des objets successifs touchés par un rayon, modifie le tableau coef pour qu'il contienne les coeffiscients de reflection des objets successifs touchés.
	* \param shine tableau de flotant
	* \param coef tableau de flotant
	* \param ref_max nombre maximal de reflections
	*/
		void coeff(float* shine, float* coef, int ref_max);
};



#endif
