#pragma once

namespace math3D {

	struct Matrix3D {

		//Attributes
		double data[3][3] = {0.0};

		/*Methods*/
		
		//Constructor
		Matrix3D();
		Matrix3D(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33);
		Matrix3D(const Matrix3D& copyMat);

		//Destructor
		~Matrix3D();

		/*Other methods*/

		/*Different matrix definition*/
		void identity();

		void rotationX(double theta);
		void rotationY(double theta);
		void rotationZ(double theta);

		void scalingMat(double sx, double sy, double sz);

		/*Matrix operations*/
		Matrix3D matMult(const Matrix3D& m);
		void scalarMult(double a);
		void scalarMult(int a);

		double trace();
		double determinant();

		void transpose();
		Matrix3D transposed();

		void inverse();
		Matrix3D inversed();

		/*Operators overload*/

		//Matrix addition
		Matrix3D operator+(const Matrix3D& v);
		void operator+=(const Matrix3D& v);

		//Matrix substraction
		Matrix3D operator-(const Matrix3D& v);
		void operator-=(const Matrix3D& v);

		//Scalar and matrix product
		Matrix3D operator*(double v);
		Matrix3D operator*(int v);
		Matrix3D operator*(const Matrix3D& m);
		void operator*=(double v);
		void operator*=(int v);
		void operator*=(const Matrix3D& m);

		//Scalar division
		Matrix3D operator/(double v);
		Matrix3D operator/(int v);
		void operator/=(double v);
		void operator/=(int v);

		//2 Vectors are equals or not if they have or not the same coordinates
		bool operator==(const Matrix3D &m);
		bool operator!=(const Matrix3D &m);

	};

}

