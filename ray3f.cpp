#include "ray3f.h"



Ray3f::Ray3f(const Vector3f & ori, const Vector3f & dir)
{
	origin_ = ori;
	direction_ = dir;
	direction_.normalize();
}


Ray3f::Ray3f(const Ray3f & r)
{
	origin_ = r.origin();
	direction_ = r.direction();
}



Vector3f Ray3f::origin() const
{
	return origin_;
}

Vector3f Ray3f::direction() const
{
	return direction_;
}



Ray3f & Ray3f::operator=(const Ray3f & r)
{
	if (this != &r)
	{
		origin_ = r.origin();
		direction_ = r.direction();
	}

	return *this;
}



std::ostream & operator<<(std::ostream & st, const Ray3f & r)
{
	st << "origin : " << r.origin() << std::endl;
	st << "direction : " << r.direction() << std::endl;

	return st;
}

