#include "camera.h"



Camera::Camera(const Vector3f & pos, const Vector3f & dir)
{
	position_ = pos;
	direction_ = dir;
	direction_.normalize();
}


Camera::Camera(const Camera & r)
{
	position_ = r.position();
	direction_ = r.direction();
}



Vector3f Camera::position() const
{
	return position_;
}

Vector3f Camera::direction() const
{
	return direction_;
}



Camera & Camera::operator=(const Camera & r)
{
	if (this != &r)
	{
		position_ = r.position();
		direction_ = r.direction();
	}

	return *this;
}



std::ostream & operator<<(std::ostream & st, const Camera & c)
{
	st << "position : " << c.position() << std::endl;
	st << "direction : " << c.direction();

	return st;
}