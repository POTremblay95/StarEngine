#include "Vector2D.h"

#include <cmath>

//Constructors
math2D::Vector2D::Vector2D()
{
	this->x = 0;
	this->y = 0;
	this->length = 0;
}

math2D::Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
	this->length = sqrt(pow(x, 2) + pow(y, 2));
}

math2D::Vector2D::Vector2D(const Vector2D v)
{
	this->x = v.x;
	this->y = v.y;
	this->length = sqrt(pow(x, 2) + pow(y, 2));
}

//Destructor
math2D::Vector2D::~Vector2D()
{
}


//Methods
float math2D::Vector2D::norm()
{
	return this->length;
}

float math2D::Vector2D::norm2()
{
	float length = this->length();

	return pow(length, 2);
}

void math2D::Vector2D::normalize()
{
	float length = this->length();

	if (this->length != 0) {
		this->x /= length;
		this->y /= length;
	}
}

Vector2D math2D::Vector2D::normalized()
{
	Vector2D normalizedVector = Vector2D(this);
	normalizedVector.normalize();

	return normalizedVector;
}

float math2D::Vector2D::length()
{
	return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

float math2D::Vector2D::dot(Vector2D v)
{
	return this->x * v.x + this->y * v.y;
}

Vector2D math2D::Vector2D::operator+(Vector2D v)
{
	return Vector2D(this->x + v.x, this->y + v.y);
}

void math2D::Vector2D::operator+=(Vector2D v)
{
	this->x += v.x;
	this->y += v.y;
}

Vector2D math2D::Vector2D::operator-(Vector2D v)
{
	return Vector2D(this->x - v.x, this->y - v.y);
}

void math2D::Vector2D::operator-=(Vector2D v)
{
	this->x -= v.x;
	this->y -= v.y;
}

Vector2D math2D::Vector2D::operator*(float v)
{
	return Vector2D(this.x * v, this->y * v);
}

Vector2D math2D::Vector2D::operator*(int v)
{
	return Vector2D(this->x * v, this->y * v);
}

void math2D::Vector2D::operator*=(float v)
{
	this->x *= v;
	this->y *= v;
}

void math2D::Vector2D::operator*=(int v)
{
	this->x *= v;
	this->y *= v;
}

Vector2D math2D::Vector2D::operator/(float v)
{
	return Vector2D(this->x / v, this->y / v);
}

Vector2D math2D::Vector2D::operator/(int v)
{
	return Vector2D(this->x / v, this->y / v);
}

void math2D::Vector2D::operator/=(float v)
{
	this->x /= v;
	this->y /= v;
}

void math2D::Vector2D::operator/=(int v)
{
	this->x /= v;
	this->y /= v;
}

bool math2D::Vector2D::operator==(Vector2D v)
{
	return this->x == v.x && this->y == v.y;
}

bool math2D::Vector2D::operator!=(Vector2D v)
{
	return this->x != v.x || this->y != v.y;
}

