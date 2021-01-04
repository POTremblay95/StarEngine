#pragma once
#include "Vector3D.h"
#include "Matrix4D.h"

namespace math4D {
	struct Vector4D
	{
		/*Attributes*/
		math3D::Vector3D coordinates; //Coordinates in the 3D space
		double w; //Homogeneous coordinate

		//Constructors
		Vector4D();
		Vector4D(double x, double y, double z, double w = 1.0);
		Vector4D(const math3D::Vector3D& v);
		Vector4D(const Vector4D& v);

		//Destructor
		~Vector4D();

		//Other methods
		double norm(); //Return norm of vector
		double norm2(); //Return norm square of vector

		void normalize(); //Normalize this vector
		Vector4D normalized(); //Return a copy of this vector normalized without normalizing this vector

		void reverse(); //Reverse this vector (only the 3D coordinates)
		Vector4D reversed(); //Creates a new vector which is the reverse of this vector

		double dot(const Vector4D& v); //Dot (scalar) product

		Vector4D cross(const Vector4D& v); //Cross product

		Vector4D matMult(const Matrix4D& m); //Matrix multiplication

		/*Operators overload*/

		//Vectors addition
		Vector4D operator+(const Vector4D& v);
		void operator+=(const Vector4D& v);

		//Vectors substraction
		Vector4D operator-(const Vector4D& v);
		void operator-=(const Vector4D& v);

		//Dot and scalar product
		Vector4D operator*(double v);
		Vector4D operator*(int v);
		Vector4D operator*(const Matrix4D& m);
		double operator*(const Vector4D& v);
		void operator*=(double v);
		void operator*=(int v);
		void operator*=(const Matrix4D& m);

		//Scalar division
		Vector4D operator/(double v);
		Vector4D operator/(int v);
		void operator/=(double v);
		void operator/=(int v);

		//Cross product
		Vector4D operator%(const Vector4D& v);
		void operator%=(const Vector4D& v);

		//2 Vectors are equals or not if they have or not the same coordinates
		bool operator==(Vector4D v);
		bool operator!=(Vector4D v);
	};
}

