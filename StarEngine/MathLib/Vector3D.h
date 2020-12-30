#pragma once

#include "Matrix3D.h"

#include <string>

namespace math3D {

	//TODO toString method

	struct Vector3D
	{

		//Attributes
		double x;
		double y;
		double z;

		/*Methods*/

		//Constructors
		Vector3D();
		Vector3D(double x, double y, double z);
		Vector3D(const Vector3D &v);

		//Destructors
		~Vector3D();

		//Other methods
		double norm(); //Return norm of vector
		double norm2(); //Return norm square of vector

		void normalize(); //Normalize this vector
		Vector3D normalized(); //Return a copy of this vector normalized without normalizing this vector

		double dot(const Vector3D &v); //Dot (scalar) product
		
		Vector3D cross(const Vector3D &v); //Cross product

		Vector3D matMult(const Matrix3D &m); //Matrix multiplication

		/*Operators overload*/

		//Vectors addition
		Vector3D operator+(const Vector3D &v);
		void operator+=(const Vector3D &v);

		//Vectors substraction
		Vector3D operator-(const Vector3D &v);
		void operator-=(const Vector3D &v);

		//Dot and scalar product
		Vector3D operator*(double v);
		Vector3D operator*(int v);
		Vector3D operator*(const Matrix3D &m);
		double operator*(const Vector3D &v);
		void operator*=(double v);
		void operator*=(int v);
		void operator*=(const Matrix3D& m);

		//Scalar division
		Vector3D operator/(double v);
		Vector3D operator/(int v);
		void operator/=(double v);
		void operator/=(int v);

		//Cross product
		Vector3D operator%(const Vector3D& v);
		void operator%=(const Vector3D& v);

		//2 Vectors are equals or not if they have or not the same coordinates
		bool operator==(Vector3D v);
		bool operator!=(Vector3D v);

	};
}
