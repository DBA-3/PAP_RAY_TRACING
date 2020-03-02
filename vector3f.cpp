#include "vector3f.h"

#include <math.h>



Vector3f::Vector3f(float x, float y, float z)
{
	x_ = x;
	y_ = y;
	z_ = z;
}


Vector3f::Vector3f(const Vector3f & v)
{
	x_ = v.x();
	y_ = v.y();
	z_ = v.z();
}


Vector3f::Vector3f()
{
	x_ = 0;
	y_ = 0;
	z_ = 0;
}


float Vector3f::x() const
{
	return x_;
}

float Vector3f::y() const
{
	return y_;
}

float Vector3f::z() const
{
	return z_;
}



Vector3f & Vector3f::operator=(const Vector3f & v)
{
	if (this != &v)
	{
		x_ = v.x();
		y_ = v.y();
		z_ = v.z();
	}

	return *this;
}



float Vector3f::norm() const
{
	return sqrt(x_*x_ + y_*y_ + z_*z_);
}



void Vector3f::normalize()
{
	float norm = this->norm();

	x_=x_/norm;
	y_=y_/norm;
	z_=z_/norm;
}



std::ostream & operator<<(std::ostream & st, const Vector3f & v)
{
	st << "( ";
	st << v.x() << ", ";
	st << v.y() << ", ";
	st << v.z() << " )";

	return st;
}


Vector3f operator+(const Vector3f & v1, const Vector3f & v2)
{
	return Vector3f(  v1.x()+v2.x(), v1.y()+v2.y(), v1.z()+v2.z()  );
}


Vector3f operator-(const Vector3f & v1, const Vector3f & v2)
{
	return Vector3f(  v1.x()-v2.x(), v1.y()-v2.y(), v1.z()-v2.z()  );
}


float operator*(const Vector3f & v1, const Vector3f & v2)
{
	return v1.x()*v2.x() + v1.y()*v2.y() + v1.z()*v2.z() ;
}



Vector3f operator*(const Vector3f & v, float d)
{
	return Vector3f(d*v.x(), d*v.y(), d*v.z());
}

Vector3f operator*(float d, const Vector3f & v)
{
	return Vector3f(d*v.x(), d*v.y(), d*v.z());
}



Vector3f operator/(const Vector3f & v, float d)
{
	if (d==0.0)
		throw "Division d'un vecteur par un scalaire nul";

	return Vector3f(v.x()/d, v.y()/d, v.z()/d);
}


Vector3f operator^(const Vector3f & v1, const Vector3f & v2)
{
	return Vector3f(v1.y()*v2.z()-v1.z()*v2.y(),
					v1.z()*v2.x()-v1.x()*v2.z(),
					v1.x()*v2.y()-v1.y()*v2.x()) ;
}


float dist(const Vector3f & v1, const Vector3f & v2)
{
	return sqrt( (v1.x()-v2.x())*(v1.x()-v2.x()) +
				 (v1.y()-v2.y())*(v1.y()-v2.y()) +
				 (v1.z()-v2.z())*(v1.z()-v2.z()) );
}



