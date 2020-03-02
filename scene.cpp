#include "scene.h"
#include <png.h>
#include <math.h> //fmin

#include <iostream>



Scene::Scene(Camera camera, Shape* *shapes, Ray3f source) : camera_(camera), shapes_(shapes), source_(source)
{

}


Scene::Scene(const Scene & s) : camera_(s.camera()), shapes_(s.shapes()), source_(s.source())
{

}



Camera Scene::camera() const
{
	return camera_;
}


Shape* *Scene::shapes() const
{
	return shapes_;
}


Ray3f Scene::source() const
{
	return source_;
}



void Scene::render(int width, int height, int nb_pixel_row, int nb_pixel_col, int nb_shapes, char* filename, int ref_max, bool shading)
{
	/*--------------------------------Copié de la doc de libpng-------------------------------------*/
	FILE *f = fopen(filename, "wb");
	if (!f) throw "Echec de la création du fichier";

	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr)
    {
    	fclose(f);
    	throw "Echec allocation png_ptr";
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
       fclose(f);
       png_destroy_write_struct(&png_ptr, (png_infopp) NULL);
       throw "Echec allocation info_ptr";
    }

    png_init_io(png_ptr, f);
    /*----------------------------------------------------------------------------------------------*/


    //Set header
    png_set_IHDR(png_ptr, info_ptr, nb_pixel_row, nb_pixel_col, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    
    //Set text
    png_text title_text;
	title_text.compression = PNG_TEXT_COMPRESSION_NONE;
	title_text.text = filename;
	png_set_text(png_ptr, info_ptr, &title_text, 0);

	png_write_info(png_ptr, info_ptr);


	//Mémoire allouée pour une ligne de pixels (rgb => 3 bytes par pixel)
	png_bytep row = (png_bytep) png_malloc(png_ptr, 3*nb_pixel_row*sizeof(png_byte));

	ref_max++;
	float pw = (float) width / (float) nb_pixel_col; //largeur d'un pixel
	float ph = (float) height / (float) nb_pixel_row; //hauteur d'un pixel
	float min_dist;
	float hit_dist;

	Ray3f *ray[ref_max];
	float shine[ref_max-1];
	float coef[ref_max-1];

	bool shadow;
	float intensity;
	float incidence;
	Vector3f S;
	Vector3f N;




	for (int i=nb_pixel_col-1; i>=0; i--) //on remplit l'image par le bas à droite
	{
		for (int j=0; j<nb_pixel_row; j++)
		{
			Vector3f Pij(j*pw, i*ph, 0); //point de la grille par laquelle on regarde
			Ray3f camera_to_grid(camera_.position(), Pij-camera_.position());
			ray[0]=new Ray3f(camera_to_grid);

			reflected_rays(ray, nb_shapes, ref_max, shine);
			coeff(shine, coef, ref_max);

			row[3*(nb_pixel_row-1-j)] = 0;
			row[3*(nb_pixel_row-1-j) + 1] = 0;
			row[3*(nb_pixel_row-1-j) + 2] = 0;

			

			for(int r=0;r<ref_max-1;r++)
			{
				int k = closer(nb_shapes, *ray[r]);
				
				if (k != -1)
				{
					Ray3f reflected(shapes_[k]->reflect(*ray[r]));
					shadow = false;
					Ray3f reflect_to_source(reflected.origin(), source_.origin()-reflected.origin());

					if(shading)
					{
						S=reflect_to_source.direction();
						N=(ray[r+1]->direction()-ray[r]->direction());

						incidence = fmax(0.5, (N*S)/(N.norm()*S.norm()));
					}
					else
					{
						incidence=1;
					}



					for (int l=0; l<nb_shapes; l++)
					{
						if (l != k) //pour éviter que l'objet se cache lui-même
							if (shapes_[l]->is_hit(reflect_to_source))
								if (  dist(reflected.origin() , shapes_[l]->reflect(reflect_to_source).origin())
									< dist(reflected.origin() , source_.origin())  )
								{
									shadow = true;
									break;
								}
					}

					//intensité pour harmoniser les ombres selon la distance
					intensity = dist(reflected.origin(), source_.origin());
					intensity = 5000/(intensity*intensity);

					if (shadow)
					{
						row[3*(nb_pixel_row-1-j)] = row[3*(nb_pixel_row-1-j)] + incidence*coef[r]*fmin(50, 50*intensity);
						row[3*(nb_pixel_row-1-j) + 1] = row[3*(nb_pixel_row-1-j) + 1] + incidence*coef[r]*fmin(50, 50*intensity);
						row[3*(nb_pixel_row-1-j) + 2] = row[3*(nb_pixel_row-1-j) + 2] + incidence*coef[r]*fmin(50, 50*intensity);

					}

					else
					{
						Ray3f source_to_reflect(source_.origin(), reflected.origin()-source_.origin());

						//self_shadow
						//au lieu de diviser par une constante (2.) diviser par l'angle ?
						if (  dist(reflect_to_source.origin() , shapes_[k]->reflect(source_to_reflect).origin()) > 0.05  )
						{
							row[3*(nb_pixel_row-1-j)] = row[3*(nb_pixel_row-1-j)] + incidence*coef[r]*fmin(shapes_[k]->matter().r()/2. * intensity, shapes_[k]->matter().r()/2.);
							row[3*(nb_pixel_row-1-j) + 1] =row[3*(nb_pixel_row-1-j) + 1] + incidence*coef[r]*fmin(shapes_[k]->matter().g()/2. * intensity, shapes_[k]->matter().g()/2.);
							row[3*(nb_pixel_row-1-j) + 2] =row[3*(nb_pixel_row-1-j) + 2] + incidence*coef[r]*fmin(shapes_[k]->matter().b()/2. * intensity, shapes_[k]->matter().b()/2.);

						}

						else //il faut rajouter la réflexion et l'angle
						{
							row[3*(nb_pixel_row-1-j)] = row[3*(nb_pixel_row-1-j)] + incidence*coef[r]*fmin(shapes_[k]->matter().r() * intensity, 255.);
							row[3*(nb_pixel_row-1-j) + 1] = row[3*(nb_pixel_row-1-j) + 1] + incidence*coef[r]*fmin(shapes_[k]->matter().g() * intensity, 255.);
							row[3*(nb_pixel_row-1-j) + 2] = row[3*(nb_pixel_row-1-j) + 2] + incidence*coef[r]*fmin(shapes_[k]->matter().b() * intensity, 255.);
						}
					}
				}
			}

			for (int r=0; r<ref_max;r++)
				delete ray[r];	
		}


		png_write_row(png_ptr, row);

	}

	
	png_free(png_ptr,row);

	png_write_end(png_ptr, NULL);

	png_destroy_write_struct(&png_ptr, &info_ptr);

	


	fclose(f);

	f=NULL;
}



/*
arg : le nombre d'objets
	  le rayon pour lequel on veut savoir quel objet il va rencontrer

ret : -1 si le rayon ne rencontre rien
	  l'indice de la shape la plus proche (celle où il faudra faire les calculs)
*/
int Scene::closer(int nb_shapes, Ray3f start)
{
	float min_dist = 1000;
	float hit_dist;
	int res = -1;

	for (int k=0; k<nb_shapes; k++)
		if (shapes_[k]->is_hit(start))
		{
			Ray3f reflected(shapes_[k]->reflect(start));
			hit_dist = dist(reflected.origin() , start.origin());

			if ( hit_dist < min_dist )
			{
				min_dist = hit_dist;
				res = k;
			}
		}

	return res;
}



/*modifie ray et shine, ray est de taille (ref_max) et shine de taille (ref_max-1) à la fin
ray doit contenir le rayon camera Pij initialement

à la fin on rajoute à ray toutes les reflexions et à shines
les coeff des couleurs càd
coef={(1-a1) , a1*(1-a2) , a1*a2*(1-a3) ...}*/
void Scene::reflected_rays(Ray3f **ray, int nb_shapes, int ref_max,  float* shine)
{
	bool vide=false;

	float min_dist;
	float hit_dist;

	for(int r=0;r<(ref_max-1);r++)
	{
		Ray3f current_Ray=Ray3f(Vector3f(0,0,0),Vector3f(0,0,0));
		min_dist=1000;
		for (int k=0; k<nb_shapes; k++)
		{

			if (shapes_[k]->is_hit(*ray[r]))
			{
				Ray3f reflected(shapes_[k]->reflect(*ray[r]));
				hit_dist = dist(reflected.origin() , camera_.position());


				if ( hit_dist < min_dist ) //on regarde l'objet le plus proche de la caméra
				{
					min_dist = hit_dist;

					current_Ray =Ray3f(reflected);

					shine[r] = shapes_[k]->matter().shiness();
	
				}
			}
		}
		ray[r+1] =new Ray3f(current_Ray);
	}
}


void Scene::coeff(float* shine, float* coef, int ref_max)
{

	for(int r=0;r<ref_max;r++)
	{
		coef[r]=1;
		for(int i=0;i<r;i++)
		{
			coef[r]=coef[r]*shine[i];
		}
		coef[r]=coef[r]*(1-shine[r]);
	}
}