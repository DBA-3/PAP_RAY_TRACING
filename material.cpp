#include "material.h"



Material::Material(float r, float g, float b, float shiness)
{
	r = (r<0) ? 0 : r;
	r_ = (r<256) ? r : 255;

	g = (g<0) ? 0 : g;
	g_ = (g<256) ? g : 255;

	b = (b<0) ? 0 : b;
	b_ = (b<256) ? b : 255;

	shiness = (shiness<0) ? 0 : shiness;
	shiness_ = (shiness<1) ? shiness : 1;
};

Material::Material(const Material & m)
{
	r_ = m.r();
	g_ = m.g();
	b_ = m.b();
	shiness_ = m.shiness();
}



float Material::r() const
{
	return r_;
}

float Material::g() const
{
	return g_;
}

float Material::b() const
{
	return b_;
}



float Material::shiness() const
{
	return shiness_;
}



std::ostream & operator<<(std::ostream & st, const Material & m)
{
	st << "r : " << m.r() << std::endl;
	st << "g : " << m.g() << std::endl;
	st << "b : " << m.b() << std::endl;
	st << "shiness : " << m.shiness();

	return st;
}