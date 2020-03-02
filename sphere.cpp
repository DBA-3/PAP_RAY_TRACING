#include "sphere.h"

#include <math.h>
#include <iostream>


Sphere::Sphere(Material matter, Vector3f origin, float radius) : Shape(matter)
{
	origin_ = origin;
	radius_ = radius;
}



bool Sphere::is_hit(const Ray3f ray)
{
	Vector3f D = ray.origin()-origin_;
	Vector3f u = ray.direction();

	if (D.norm() < radius_) return false;

	if (D*u > 0)  return false;

	if( (D^u).norm()/u.norm() > radius_ ) return false;

	return true;
}



Ray3f Sphere::reflect(const Ray3f ray) const
{
	float u = ray.direction().x();
	float v = ray.direction().y();
	float w = ray.direction().z();

	float X = ray.origin().x()-origin_.x();
	float Y = ray.origin().y()-origin_.y();
	float Z = ray.origin().z()-origin_.z();

	float a = u*u + v*v + w*w;
	float b = 2*(X*u + Y*v + Z*w);
	float c = X*X + Y*Y + Z*Z - radius_*radius_;

	float delta = b*b - 4*a*c;

	//Si delta<0, l'objet n'est pas rencontré
	//Or cette condition est vérifiée avant par is_hit
	//delta<0 si il ya des erreurs d'arrondis seulement
	if(delta<0)	delta = -delta;

	float k = (-b-sqrt(delta)) / (2*a);

	Vector3f hit = ray.origin() + k*ray.direction();
	Vector3f N = hit-origin_;
	N.normalize();

	Vector3f I = ray.direction();

	return Ray3f(hit, I-2*(I*N)*N);
}



Vector3f Sphere::origin() const
{
	return origin_;
}



float Sphere::radius() const
{
	return radius_;
}



std::ostream & operator<<(std::ostream & st, const Sphere & s)
{
	st << "matter" << std::endl << s.matter() << std::endl;
	st << "origin : " << s.origin() << std::endl;
	st << "radius : " << s.radius() << std::endl;

	return st;
}
