#include "quad.h"



Quad::Quad(Material matter, Vector3f origin, float width, float height, float depth) : Shape(matter)
{
	origin_ = origin;
	width_ = width;
	height_ = height;
	depth_ = depth;
}


//ici on suppose que le rayon va vers l'objet
bool Quad::is_hit(const Ray3f ray)
{
	//Equations des faces
	float x1 = origin_.x() + width_/2; //après
	float y2 = origin_.y() + height_/2; //dessus
	float z3 = origin_.z() + depth_/2; //devant
	float x4 = origin_.x() - width_/2; //avant
	float y5 = origin_.y() - height_/2; //dessous
	float z6 = origin_.z() - depth_/2; //derrière

	//Informations du rayon
	float a = ray.direction().x();
	float b = ray.direction().y();
	float c = ray.direction().z();
	float X = ray.origin().x();
	float Y = ray.origin().y();
	float Z = ray.origin().z();


	//Calculs des coordonnées d'intersection avec les faces et vérification
	float t, x, y, z;

	//Face 1
	if(a!=0)
	{
		t = (x1 - X) / a ;
		//x = x1;
		y = Y + b*t;
		z = Z + c*t;
		if (Vector3f(1,0,0)*ray.direction()<0 && t>0 && y5<=y && y<=y2 && z6<=z && z<=z3)
		return true;
	}

	//Face 2
	if(b!=0)
	{
		t = (y2 - Y) / b ;
		x = X + a*t;
		//y = y2;
		z = Z + c*t;
		if (Vector3f(0,1,0)*ray.direction()<0 && t>0 && x4<=x && x<=x1 && z6<=z && z<=z3)
		return true;
	}


	//Face 3
	if(c!=0)
	{
		t = (z3 - Z) / c ;
		x = X + a*t;
		y = Y + b*t;
		//z = z3;
		if (Vector3f(0,0,1)*ray.direction()<0 && t>0 && x4<=x && x<=x1 && y5<=y && y<=y2)
		return true;
	}


	//Face 4
	if(a!=0)
	{
		t = (x4 - X) / a ;
		//x = x4;
		y = Y + b*t;
		z = Z + c*t;
		if (Vector3f(-1,0,0)*ray.direction()<0 && t>0 && y5<=y && y<= y2 && z6<=z && z<=z3)
		return true;
	}


	//Face 5
	if(b!=0)
	{
		t = (y5 - Y) / b ;
		x = X + a*t;
		//y = y5;
		z = Z + c*t;
		if (Vector3f(0,-1,0)*ray.direction()<0 && t>0 && x4<=x && x<=x1 && z6<=z && z<=z3)
		return true;
	}


	//Face 6
	if(c!=0)
	{
		t = (z6 - Z) / c ;
		x = X + a*t;
		y = Y + b*t;
		//z = z6;
		if (Vector3f(0,0,-1)*ray.direction()<0 && t>0 && x4<=x && x<=x1 && y5<=y && y<=y2)
		return true;
	}

	return false;
}



Ray3f Quad::reflect(const Ray3f ray) const
{
	//Equations des faces
	float x1 = origin_.x() + width_/2; //après
	float y2 = origin_.y() + height_/2; //dessus
	float z3 = origin_.z() + depth_/2; //devant
	float x4 = origin_.x() - width_/2; //avant
	float y5 = origin_.y() - height_/2; //dessous
	float z6 = origin_.z() - depth_/2; //derrière

	//Informations du rayon
	float a = ray.direction().x();
	float b = ray.direction().y();
	float c = ray.direction().z();
	float X = ray.origin().x();
	float Y = ray.origin().y();
	float Z = ray.origin().z();


	//Calculs des coordonnées d'intersection avec les faces et vérification
	float t, x, y ,z;


	Vector3f hit;
	Vector3f N;
	Vector3f I = ray.direction();


	//Face 1
	if(a!=0 && Vector3f(1,0,0)*ray.direction()<0)
	{

		t = (x1 - X) / a ;
		//x = X;
		y = Y + b*t;
		z = Z + c*t;

		if (y5<=y && y<=y2 && z6<=z && z<=z3)
		{

			Vector3f hit = ray.origin() + t*ray.direction();
			Vector3f N = Vector3f(1,0,0);
			N.normalize();
			return Ray3f(hit, I-2*(I*N)*N);
		}

	}


	//Face 2
	if(b!=0 && Vector3f(0,1,0)*ray.direction()<0)
	{

		t = (y2 - Y) / b ;
		x = X + a*t;
		//y = y2;
		z = Z + c*t;
		if (x4<=x && x<=x1 && z6<=z && z<=z3)
		{
			Vector3f hit = ray.origin() + t*ray.direction();
			Vector3f N = Vector3f(0,1,0);
			N.normalize();

			return Ray3f(hit, I-2*(I*N)*N);
		}

	}


	//Face 3
	if(c!=0 && Vector3f(0,0,1)*ray.direction()<0)
	{
		t = (z3 - Z) / c ;
		x = X + a*t;
		y = Y + b*t;
		//z = z3;
		if (x4<=x && x<=x1 && y5<=y && y<=y2)
		{
			Vector3f hit = ray.origin() + t*ray.direction();
			Vector3f N = Vector3f(0,0,1);
			N.normalize();
			return Ray3f(hit, I-2*(I*N)*N);
		}
	}
	

	//Face 4
	if(a!=0 && Vector3f(-1,0,0)*ray.direction()<0)
	{ 
		t = (x4 - X) / a ;
		//x = X;
		y = Y + b*t;
		z = Z + c*t;
		if (y5<=y && y<=y2 && z6<=z && z<=z3)
		{
			Vector3f hit = ray.origin() + t*ray.direction();
			Vector3f N = Vector3f(-1,0,0);
			N.normalize();
			return Ray3f(hit, I-2*(I*N)*N);
		}

	}



	//Face 5
	if(b!=0 && Vector3f(0,-1,0)*ray.direction()<0)
	{
		t = (y5 - Y) / b ;
		x = X + a*t;
		//y = y5;
		z = Z + c*t;
		if (x4<=x && x<=x1 && z6<=z && z<=z3)
		{
			Vector3f hit = ray.origin() + t*ray.direction();
			Vector3f N = Vector3f(0,-1,0);
			N.normalize();
			return Ray3f(hit, I-2*(I*N)*N);
		}
	}


	//Face 6
	if(c!=0 && Vector3f(0,0,-1)*ray.direction()<0)
	{

		t = (z6 - Z) / c ;
		x = X + a*t;
		y = Y + b*t;
		//z = z6;
		if (x4<=x && x<=x1 && y5<=y && y<=y2)
		{
			Vector3f hit = ray.origin() + t*ray.direction();
			Vector3f N = Vector3f(0,0,-1);
			N.normalize();
			return Ray3f(hit, I-2*(I*N)*N);
		}
	}

	return(Ray3f(Vector3f(0,0,0),Vector3f(1,0,0)));
}



Vector3f Quad::origin() const
{
	return origin_;
}



float Quad::width() const
{
	return width_;
}



float Quad::height() const
{
	return height_;
}



float Quad::depth() const
{
	return depth_;
}



std::ostream & operator<<(std::ostream & st, const Quad & q)
{
	st << "matter" << std::endl << q.matter() << std::endl;
	st << "origin : " << q.origin() << std::endl;
	st << "width : " << q.width() << std::endl;
	st << "height : " << q.height() << std::endl;
	st << "depth : " << q.depth();

	return st;
}
