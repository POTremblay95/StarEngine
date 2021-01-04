#define _USE_MATH_DEFINES

#include "Matrix3D.h"
#include <iostream>
#include <cmath>

namespace math3D {
	/**
	* Matrix3D default constructor (identity matrix)
	*/
	Matrix3D::Matrix3D()
	{
		data[0][0] = 1;
		data[1][1] = 1;
		data[2][2] = 1;
	}
	/**
	* Matrix3D constructor with all elements
	*/
	Matrix3D::Matrix3D(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33)
	{
		data[0][0] = a11;
		data[0][1] = a12;
		data[0][2] = a13;
		data[1][0] = a21;
		data[1][1] = a22;
		data[1][2] = a23;
		data[2][0] = a31;
		data[2][1] = a32;
		data[2][2] = a33;
	}
	/**
	* Matrix3D copy constructor
	*/
	Matrix3D::Matrix3D(const Matrix3D& copyMat)
	{
		data[0][0] = copyMat.data[0][0];
		data[0][1] = copyMat.data[0][1];
		data[0][2] = copyMat.data[0][2];
		data[1][0] = copyMat.data[1][0];
		data[1][1] = copyMat.data[1][1];
		data[1][2] = copyMat.data[1][2];
		data[2][0] = copyMat.data[2][0];
		data[2][1] = copyMat.data[2][1];
		data[2][2] = copyMat.data[2][2];

	}
	
	/**
	* Matrix3D destructor
	*/
	Matrix3D::~Matrix3D()
	{
	}

	/**
	* Change this matrix to identity matrix
	*/
	void Matrix3D::identity()
	{
		*this = Matrix3D();
	}
	/**
	* Define this matrix as a rotation matrix of x axis by theta in degree
	*/
	void Matrix3D::rotationX(double theta)
	{
		this->data[0][0] = 1;
		this->data[0][1] = 0;
		this->data[0][2] = 0;
		this->data[1][0] = 0;
		this->data[1][1] = cos(theta * M_PI / 180);
		this->data[1][2] = -sin(theta * M_PI / 180);
		this->data[2][0] = 0;
		this->data[2][1] = sin(theta * M_PI / 180);
		this->data[2][2] = cos(theta * M_PI / 180);
	}
	/**
	* Define this matrix as a rotation matrix of y axis by theta in degree
	*/
	void Matrix3D::rotationY(double theta)
	{
		this->data[0][0] = cos(theta * M_PI / 180);
		this->data[0][1] = 0;
		this->data[0][2] = sin(theta * M_PI / 180);
		this->data[1][0] = 0;
		this->data[1][1] = 1;
		this->data[1][2] = 0;
		this->data[2][0] = -sin(theta * M_PI / 180);
		this->data[2][1] = 0;
		this->data[2][2] = cos(theta * M_PI / 180);
	}
	/**
	* Define this matrix as a rotation matrix of z axis by theta in degree
	*/
	void Matrix3D::rotationZ(double theta)
	{
		this->data[0][0] = cos(theta * M_PI / 180);
		this->data[0][1] = -sin(theta * M_PI / 180);
		this->data[0][2] = 0;
		this->data[1][0] = sin(theta * M_PI / 180);
		this->data[1][1] = cos(theta * M_PI / 180);
		this->data[1][2] = 0;
		this->data[2][0] = 0;
		this->data[2][1] = 0;
		this->data[2][2] = 1;
	}
	/**
	* Defines this matrix as a scaling matrix with a scaling in x,y,z
	*/
	void Matrix3D::scalingMat(double sx, double sy, double sz)
	{
		this->data[0][0] = sx;
		this->data[0][1] = 0;
		this->data[0][2] = 0;
		this->data[1][0] = 0;
		this->data[1][1] = sy;
		this->data[1][2] = 0;
		this->data[2][0] = 0;
		this->data[2][1] = 0;
		this->data[2][2] = sz;
	}
	/**
	* Creates a matrix of the multiplication of this and m
	*/
	Matrix3D Matrix3D::matMult(const Matrix3D& m)
	{
		return Matrix3D(
			this->data[0][0] * m.data[0][0] + this->data[0][1] * m.data[1][0] + this->data[0][2] * m.data[2][0],
			this->data[0][0] * m.data[0][1] + this->data[0][1] * m.data[1][1] + this->data[0][2] * m.data[2][1],
			this->data[0][0] * m.data[0][2] + this->data[0][1] * m.data[1][2] + this->data[0][2] * m.data[2][2],
			this->data[1][0] * m.data[0][0] + this->data[1][1] * m.data[1][0] + this->data[1][2] * m.data[2][0],
			this->data[1][0] * m.data[0][1] + this->data[1][1] * m.data[1][1] + this->data[1][2] * m.data[2][1],
			this->data[1][0] * m.data[0][2] + this->data[1][1] * m.data[1][2] + this->data[1][2] * m.data[2][2],
			this->data[2][0] * m.data[0][0] + this->data[2][1] * m.data[1][0] + this->data[2][2] * m.data[2][0],
			this->data[2][0] * m.data[0][1] + this->data[2][1] * m.data[1][1] + this->data[2][2] * m.data[2][1],
			this->data[2][0] * m.data[0][2] + this->data[2][1] * m.data[1][2] + this->data[2][2] * m.data[2][2]);
	}
	/**
	* Multiply this matrix by a scalar
	*/
	void Matrix3D::scalarMult(double a)
	{
		this->data[0][0] *= a;
		this->data[0][1] *= a;
		this->data[0][2] *= a;
		this->data[1][0] *= a;
		this->data[1][1] *= a;
		this->data[1][2] *= a;
		this->data[2][0] *= a;
		this->data[2][1] *= a;
		this->data[2][2] *= a;
	}
	/**
	* Multiply this matrix by a scalar
	*/
	void Matrix3D::scalarMult(int a)
	{
		this->data[0][0] *= a;
		this->data[0][1] *= a;
		this->data[0][2] *= a;
		this->data[1][0] *= a;
		this->data[1][1] *= a;
		this->data[1][2] *= a;
		this->data[2][0] *= a;
		this->data[2][1] *= a;
		this->data[2][2] *= a;
	}
	/**
	* Trace of this matrix
	*/
	double Matrix3D::trace()
	{
		return this->data[0][0] + this->data[1][1] + this->data[2][2];
	}
	/**
	* Determinant of this matrix
	*/
	double Matrix3D::determinant()
	{
		return this->data[0][0] * this->data[1][1] * this->data[2][2]
			+ this->data[0][1] * this->data[1][2] * this->data[2][0]
			+ this->data[0][2] * this->data[1][0] * this->data[2][1]
			- this->data[0][2] * this->data[1][1] * this->data[2][0]
			- this->data[0][1] * this->data[1][0] * this->data[2][2]
			- this->data[0][0] * this->data[1][2] * this->data[2][1];
	}
	/**
	* Tranpose this matrix
	*/
	void Matrix3D::transpose()
	{
		Matrix3D copy = Matrix3D(*this);
		this->data[0][1] = copy.data[1][0];
		this->data[0][2] = copy.data[2][0];
		this->data[1][0] = copy.data[0][1];
		this->data[1][2] = copy.data[2][1];
		this->data[2][0] = copy.data[0][2];
		this->data[2][1] = copy.data[1][2];
	}
	/**
	* Creates a matrix of the transpose of this matrix
	*/
	Matrix3D Matrix3D::transposed()
	{
		Matrix3D copy = Matrix3D(*this);
		copy.transpose();
		return copy;
	}
	/**
	* Inverse this matrix
	*/
	void Matrix3D::inverse()
	{
		double det = this->determinant();
		if (det != 0) {

			Matrix3D copy = Matrix3D(*this);

			this->data[0][0] = copy.data[1][1] * copy.data[2][2] - copy.data[1][2] * copy.data[2][1];
			this->data[0][1] = -copy.data[0][1] * copy.data[2][2] + copy.data[2][1] * copy.data[0][2];
			this->data[0][2] = copy.data[0][1] * copy.data[1][2] - copy.data[1][1] * copy.data[0][2];
			this->data[1][0] = -copy.data[1][0] * copy.data[2][2] + copy.data[1][2] * copy.data[2][0];
			this->data[1][1] = copy.data[0][0] * copy.data[2][2] - copy.data[0][2] * copy.data[2][0];
			this->data[1][2] = -copy.data[0][0] * copy.data[1][2] + copy.data[1][0] * copy.data[0][2];
			this->data[2][0] = copy.data[1][0] * copy.data[2][1] - copy.data[1][1] * copy.data[2][0];
			this->data[2][1] = -copy.data[0][0] * copy.data[2][1] + copy.data[0][1] * copy.data[2][0];
			this->data[2][2] = copy.data[0][0] * copy.data[1][1] - copy.data[0][1] * copy.data[1][0];

			this->scalarMult(1/det);
		}
	}
	/**
	* Creates a matrix of the inverse of this matrix
	*/
	Matrix3D Matrix3D::inversed()
	{
		Matrix3D copy = Matrix3D(*this);
		copy.inverse();

		return copy;
	}
	/**
	* Matrix addition (creates a new matrix)
	*/
	Matrix3D Matrix3D::operator+(const Matrix3D& v)
	{
		return Matrix3D(
			this->data[0][0]+v.data[0][0],
			this->data[0][1]+v.data[0][1],
			this->data[0][2]+v.data[0][2],
			this->data[1][0] + v.data[1][0],
			this->data[1][1] + v.data[1][1],
			this->data[1][2] + v.data[1][2],
			this->data[2][0] + v.data[2][0],
			this->data[2][1] + v.data[2][1],
			this->data[2][2] + v.data[2][2]);
	}
	/**
	* Matrix addition (modify this matrix)
	*/
	void Matrix3D::operator+=(const Matrix3D& v)
	{
		this->data[0][0] += v.data[0][0];
		this->data[0][1] += v.data[0][1];
		this->data[0][2] += v.data[0][2];
		this->data[1][0] += v.data[1][0];
		this->data[1][1] += v.data[1][1];
		this->data[1][2] += v.data[1][2];
		this->data[2][0] += v.data[2][0];
		this->data[2][1] += v.data[2][1];
		this->data[2][2] += v.data[2][2];
	}
	/**
	* Matrix substraction (creates a new matrix)
	*/
	Matrix3D Matrix3D::operator-(const Matrix3D& v)
	{
		return Matrix3D(
			this->data[0][0] - v.data[0][0],
			this->data[0][1] - v.data[0][1],
			this->data[0][2] - v.data[0][2],
			this->data[1][0] - v.data[1][0],
			this->data[1][1] - v.data[1][1],
			this->data[1][2] - v.data[1][2],
			this->data[2][0] - v.data[2][0],
			this->data[2][1] - v.data[2][1],
			this->data[2][2] - v.data[2][2]);
	}
	/**
	* Matrix substraction (modify this matrix)
	*/
	void Matrix3D::operator-=(const Matrix3D& v)
	{
		this->data[0][0] -= v.data[0][0];
		this->data[0][1] -= v.data[0][1];
		this->data[0][2] -= v.data[0][2];
		this->data[1][0] -= v.data[1][0];
		this->data[1][1] -= v.data[1][1];
		this->data[1][2] -= v.data[1][2];
		this->data[2][0] -= v.data[2][0];
		this->data[2][1] -= v.data[2][1];
		this->data[2][2] -= v.data[2][2];
	}
	/*Operators overload*/

	/**
	* Scalar multiplication (creates a new matrix)
	*/
	Matrix3D Matrix3D::operator*(double v)
	{
		Matrix3D copy = Matrix3D(*this);
		copy.scalarMult(v);

		return copy;
	}
	/**
	* Scalar multiplication (creates a new matrix)
	*/
	Matrix3D Matrix3D::operator*(int v)
	{
		Matrix3D copy = Matrix3D(*this);
		copy.scalarMult(v);

		return copy;
	}
	/**
	* Matrix multiplication (creates a new matrix)
	*/
	Matrix3D Matrix3D::operator*(const Matrix3D& m)
	{
		return this->matMult(m);
	}
	/**
	* Scalar multiplication (modify this matrix)
	*/
	void Matrix3D::operator*=(double v)
	{
		this->scalarMult(v);
	}
	/**
	* Scalar multiplication (modify this matrix)
	*/
	void Matrix3D::operator*=(int v)
	{
		this->scalarMult(v);
	}
	/**
	* Matrix multiplication (modify this matrix)
	*/
	void Matrix3D::operator*=(const Matrix3D& m)
	{
		*this = this->matMult(m);
	}
	/**
	* Scalar division (creates a new matrix)
	*/
	Matrix3D Matrix3D::operator/(double v)
	{
		Matrix3D copy = Matrix3D(*this);
		copy.scalarMult(1.0 / v);

		return copy;
	}
	/**
	* Scalar division (creates a new matrix)
	*/
	Matrix3D Matrix3D::operator/(int v)
	{
		Matrix3D copy = Matrix3D(*this);
		copy.scalarMult(1.0 / v);

		return copy;
	}
	/**
	* Scalar division (modify this matrix)
	*/
	void Matrix3D::operator/=(double v)
	{
		this->scalarMult(1.0 / v);
	}
	/**
	* Scalar division (modify this matrix)
	*/
	void Matrix3D::operator/=(int v)
	{
		this->scalarMult(1.0 / v);
	}
	/**
	* Check if two matrices are equals (if all elements are the same)
	*/
	bool Matrix3D::operator==(const Matrix3D &m)
	{
		double epsilon = 1e-15; //Numerical error authorised
		return this->data[0][0] <= m.data[0][0] + epsilon && this->data[0][0] >= m.data[0][0] - epsilon
			&& this->data[0][1] <= m.data[0][1] + epsilon && this->data[0][1] >= m.data[0][1] - epsilon
			&& this->data[0][2] <= m.data[0][2] + epsilon && this->data[0][2] >= m.data[0][2] - epsilon
			&& this->data[1][0] <= m.data[1][0] + epsilon && this->data[1][0] >= m.data[1][0] - epsilon
			&& this->data[1][1] <= m.data[1][1] + epsilon && this->data[1][1] >= m.data[1][1] - epsilon
			&& this->data[1][2] <= m.data[1][2] + epsilon && this->data[1][2] >= m.data[1][2] - epsilon
			&& this->data[2][0] <= m.data[2][0] + epsilon && this->data[2][0] >= m.data[2][0] - epsilon
			&& this->data[2][1] <= m.data[2][1] + epsilon && this->data[2][1] >= m.data[2][1] - epsilon
			&& this->data[2][2] <= m.data[2][2] + epsilon && this->data[2][2] >= m.data[2][2] - epsilon;
	}

	bool Matrix3D::operator!=(const Matrix3D &m)
	{
		return !(*this == m);
	}

}
