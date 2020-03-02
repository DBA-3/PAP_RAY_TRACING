#include "camera.h"
#include "quad.h"
#include "sphere.h"
#include "scene.h"

#include <iostream>
#include <string>



int main()
{
	try
	{

		//----------MISE EN PLACE DE LA SCENE----------
		Material red(255, 0, 0, 0);
		Material green(0, 255, 0, 0);
		Material blue(0, 0, 255, 0);
		Material yellow(255, 255, 0, 0);
		Material magenta(255, 0, 255, 0.3);
		Material cyan(0, 255, 255, 0);
		Material white(255, 255, 255, 0);
		Material grey(122, 122, 122, 0);
		Material black(0, 0, 0, 0);
		Material mirror(0, 0, 0, 0.9);

		int nb_shapes = 8;
		float width = 100; //x
		float height = 100; //y
		float depth = 100; //z

		/*	   y
			   ^
		       |
		       |
		x <----X z*/
		Shape *shapes[nb_shapes];
		shapes[0] = new Quad(yellow, Vector3f(width/2, height/2, depth), width, height, 0); //mur du fond
		shapes[1] = new Quad(magenta, Vector3f(width, height/2, depth/2), 0, height, depth); //mur gauche
		shapes[2] = new Quad(white, Vector3f(width/2, height, depth/2), width, 0, depth); //plafond
		shapes[3] = new Quad(cyan, Vector3f(0, height/2, depth/2), 0, height, depth); //mur droit
		shapes[4] = new Quad(green, Vector3f(width/2, 0, depth/2), width, 0, depth); //sol
		shapes[5] = new Quad(red, Vector3f(22, 15, 20), 10, 10, 10); //cube
		shapes[6] = new Sphere(red, Vector3f(75, 20, 70), 20); //sphere
		shapes[7] = new Sphere(mirror, Vector3f(25, 20, 70), 20); //sphere

		Camera camera(Vector3f(width/2, height/2, -50), Vector3f(0, 0, 1)); //on met la caméra un peu en recul
		Ray3f source(Vector3f(width/2, height-10, depth/3), Vector3f(0, -1, 0)); //lumière au plafond
		Scene scene(camera, shapes, source);


		//----------CALCUL ET SAUVEGARDE DE L'IMAGE----------
		std::cout << "Création des images..." << std::endl;
		std::string filename = "basic_ray_tracing.png";
		std::string filename2 = "ray_tracing_reflexion.png";
		std::string filename3 = "ray_tracing_shading.png";
		scene.render(width, height, 1080, 1080, nb_shapes, (char *) filename.c_str(),1,false);
		std::cout<<"l'image est générée dans le fichier "<<filename<<std::endl;
		scene.render(width, height, 1080, 1080, nb_shapes, (char *) filename2.c_str(),4,false);
		std::cout<<"l'image est générée dans le fichier "<<filename2<<std::endl;
		scene.render(width, height, 1080, 1080, nb_shapes, (char *) filename3.c_str(),4,true);
		std::cout<<"l'image est générée dans le fichier "<<filename3<<std::endl;
		std::cout << "Image sauvegardée" << std::endl;

		//----------LIBERATION DE LA MEMOIRE----------
		for (int i=0; i<nb_shapes; i++)
			delete shapes[i];


	}

	catch (const char* s)
	{
		std::cout << std::endl << "ERROR : " << s << std::endl;
		return 1;
	}

	return 0;
}
