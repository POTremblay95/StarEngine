#include "Vector4D.h"
#include "Matrix4D.h"

namespace math4D {
	/**
	* Default constructor coordinates = (0,0,0) and w = 1
	*/
	Vector4D::Vector4D()
	{
		this->coordinates = math3D::Vector3D();
		this->w = 1;
	}
	/**
	* Constructor with all elements
	*/
	Vector4D::Vector4D(double x, double y, double z, double w)
	{
		this->coordinates = math3D::Vector3D(x, y, z);
		this->w = w;
	}
	/**
	* Constructor with the coordinates only (w=1 by default)
	*/
	Vector4D::Vector4D(const math3D::Vector3D& v)
	{
		this->coordinates = v;
		this->w = 1;
	}
	/**
	* Copy constructor
	*/
	Vector4D::Vector4D(const Vector4D& v)
	{
		*this = v;
	}
	/**
	* Default destructor
	*/
	Vector4D::~Vector4D()
	{
	}
	/**
	* Normalize the w coordinate of this vector
	*/
	void Vector4D::wNormalize()
	{
		this->coordinates /= this->w;
		this->w = 1;
	}
	/**
	* Multiply this vector by a transformation matrix (creates a new vector)
	*/
	Vector4D Vector4D::matMult(const Matrix4D& m)
	{
		return Vector4D(
			this->coordinates.x * m.data[0][0] + this->coordinates.y * m.data[1][0] + this->coordinates.z * m.data[2][0] + this->w * m.data[3][0],
			this->coordinates.x * m.data[0][1] + this->coordinates.y * m.data[1][1] + this->coordinates.z * m.data[2][1] + this->w * m.data[3][1],
			this->coordinates.x * m.data[0][2] + this->coordinates.y * m.data[1][2] + this->coordinates.z * m.data[2][2] + this->w * m.data[3][2],
			this->coordinates.x * m.data[0][3] + this->coordinates.y * m.data[1][3] + this->coordinates.z * m.data[2][3] + this->w * m.data[3][3]
			);
	}

}
