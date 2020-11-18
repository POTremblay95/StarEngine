#include "Vector2D.h"

#include <cmath>
math2D::Vector2D::Vector2D()
{
	this->x = 0;
	this->y = 0;
	this->length = 0;
}

math2D::Vector2D::Vector2D(double& x, double& y)
{
	this->x = x;
	this->y = y;
	this->length = sqrt(pow(x, 2) + pow(y, 2));
}

math2D::Vector2D::Vector2D(const Vector2D& v)
{
	this->x = v.x;
	this->y = v.y;
	this->length = sqrt(pow(x, 2) + pow(y, 2));
}

double math2D::Vector2D::norm()
{
	return this->length;
}

double math2D::Vector2D::norm2()
{
	return pow(this->length,2);
}

