#include "Vector3D.h"

#include <cmath>

namespace math3D {
	/**
	* Default constructor for a null vector
	*/
	Vector3D::Vector3D()
	{
		x = 0;
		y = 0;
		z = 0;
	}
	/**
	* Normal constructor with default values to 0
	*/
	Vector3D::Vector3D(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	/**
	* Copy constructor
	*/
	Vector3D::Vector3D(const Vector3D& v)
	{
		*this = v;
	}
	/**
	* Default destructor
	*/
	Vector3D::~Vector3D()
	{
	}
	/**
	* Norm of the vector
	*/
	double Vector3D::norm()
	{
		return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
	}
	/**
	* Norm squared of the vector
	*/
	double Vector3D::norm2()
	{
		return pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2);
	}
	/**
	* Normalize this vector
	*/
	void Vector3D::normalize()
	{
		double length = this->norm();
		if (length > 0) {
			this->x /= length;
			this->y /= length;
			this->z /= length;
		}
	}
	/**
	* Copy this vector than normalize the copy
	*/
	Vector3D Vector3D::normalized()
	{
		Vector3D copy = Vector3D(*this);
		copy.normalize();
		return copy;
	}
	/**
	* Reverse this vector
	*/
	void Vector3D::reverse()
	{
		this->x *= -1;
		this->y *= -1;
		this->z *= -1;
	}
	/**
	* Create a new vector which is the reverse of this vector
	*/
	Vector3D Vector3D::reversed()
	{
		return Vector3D(this->x * -1, this->y * -1, this->z * -1);
	}
	/**
	* Dot (scalar) product between the vectors
	*/
	double Vector3D::dot(const Vector3D& v)
	{
		return this->x * v.x + this->y * v.y + this->z * v.z;
	}
	/**
	* Cross product between the two vectors (doesn't modify this vector)
	*/
	Vector3D Vector3D::cross(const Vector3D& v)
	{

		Vector3D crossResult = Vector3D(
			this->y*v.z-this->z*v.y,
			this->z*v.x-this->x*v.z,
			this->x*v.y-this->y*v.x);
		return crossResult;
	}
	/**
	* Vector-matrix multiplication
	*/
	Vector3D Vector3D::matMult(const Matrix3D& m)
	{
		return Vector3D(
			this->x * m.data[0][0] + this->y * m.data[1][0] + this->z * m.data[2][0],
			this->x * m.data[0][1] + this->y * m.data[1][1] + this->z * m.data[2][1],
			this->x * m.data[0][2] + this->y * m.data[1][2] + this->z * m.data[2][2]);
	}
	/*Operators overload*/

	/**
	* Vectors addition (create a new vector)
	*/
	Vector3D Vector3D::operator+(const Vector3D& v)
	{
		return Vector3D(this->x + v.x, this->y + v.y, this->z + v.z);
	}
	/**
	* Vectors addition (modify this vector)
	*/
	void Vector3D::operator+=(const Vector3D& v)
	{
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
	}
	/**
	* Vectors substraction (creates a new vector)
	*/
	Vector3D Vector3D::operator-(const Vector3D& v)
	{
		return Vector3D(this->x - v.x, this->y - v.y, this->z - v.z);
	}
	/**
	* Vectors substraction (modify this vector)
	*/
	void Vector3D::operator-=(const Vector3D& v)
	{
		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;
	}	
	/**
	* Scalar product (creates new vector)
	*/
	Vector3D Vector3D::operator*(double v)
	{
		return Vector3D(this->x * v, this->y * v, this->z * v);
	}
	/**
	* Vector-Matrix multiplication (creates a new vector)
	*/
	Vector3D Vector3D::operator*(const Matrix3D& m)
	{
		return this->matMult(m);
	}
	/**
	* Dot product
	*/
	double Vector3D::operator*(const Vector3D& v)
	{
		return this->dot(v);
	}
	/**
	* Scalar product (modify this vector)
	*/
	void Vector3D::operator*=(double v)
	{
		this->x *= v;
		this->y *= v;
		this->z *= v;
	}
	/**
	* Vector-Matrix multiplication (modify this vector)
	*/
	void Vector3D::operator*=(const Matrix3D& m)
	{
		Vector3D multResult = *this * m;
		this->x = multResult.x;
		this->y = multResult.y;
		this->z = multResult.z;
	}
	/**
	* Scalar division (creates a new vector)
	*/
	Vector3D Vector3D::operator/(double v)
	{
		return Vector3D(this->x / v, this->y / v, this->z / v);
	}
	/**
	* Scalar division (modify this vector)
	*/
	void Vector3D::operator/=(double v)
	{
		this->x /= v;
		this->y /= v;
		this->z /= v;
	}
	/**
	* Cross product (creates a new vector)
	*/
	Vector3D Vector3D::operator%(const Vector3D& v)
	{
		return this->cross(v);
	}
	/**
	* Cross product (modify this vector)
	*/
	void Vector3D::operator%=(const Vector3D& v)
	{
		Vector3D crossProduct = this->cross(v);
		this->x = crossProduct.x;
		this->y = crossProduct.y;
		this->z = crossProduct.z;
	}
	/**
	* Check if two vectors are equals (only if all coordinates are equals)
	*/
	bool Vector3D::operator==(const Vector3D& v)
	{
		return this->x == v.x && this->y == v.y && this->z == v.z;
	}
	/**
	* Check if two vectors aren't equals (only if all coordinates aren't equals)
	*/
	bool Vector3D::operator!=(const Vector3D& v)
	{
		return this->x != v.x || this->y != v.y || this->z != v.z;
	}


}