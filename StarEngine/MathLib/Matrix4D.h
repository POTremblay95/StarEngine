#pragma once
#include "Vector3D.h"
#include "Matrix3D.h"
namespace math4D {
	struct Matrix4D
	{
		//Attribute
		double data[4][4] = { 0.0 };

		//Constructors
		Matrix4D();
		Matrix4D(double a00, double a01, double a02, double a03,
			double a10, double a11, double a12, double a13,
			double a20, double a21, double a22, double a23,
			double a30, double a31, double a32, double a33);
		Matrix4D(const math3D::Matrix3D& m);
		Matrix4D(const math3D::Vector3D& v);
		Matrix4D(const math3D::Matrix3D& m, const math3D::Vector3D& v);
		Matrix4D(const Matrix4D& m);

		//Destructor
		~Matrix4D();

		/*Other methods*/

		/*Different matrix definition*/
		void identity();

		void rotationX(double theta);
		void rotationY(double theta);
		void rotationZ(double theta);

		void scalingMat(double sx, double sy, double sz);

		void translateMat(double tx, double ty, double tz);

		/*Matrix operations*/
		/*In homogeneous coordinates the only interesting operation is the matrix multiplication*/
		Matrix4D matMult(const Matrix4D& m);

		/*Operators overload*/

		//Matrix product
		Matrix4D operator*(const Matrix4D& m);
		void operator*=(const Matrix4D& m);

		//2 Vectors are equals or not if they have or not the same coordinates
		bool operator==(const Matrix4D& m);
		bool operator!=(const Matrix4D& m);
	};
}

