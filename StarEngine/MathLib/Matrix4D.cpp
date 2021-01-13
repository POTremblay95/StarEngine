#define _USE_MATH_DEFINES

#include "Matrix4D.h"
#include <cmath>

namespace math4D {

	/**
	* Default constructor (identity matrix)
	*/
	Matrix4D::Matrix4D()
	{
		this->data[0][0] = 1;
		this->data[0][1] = 0;
		this->data[0][2] = 0;
		this->data[0][3] = 0;
		this->data[1][0] = 0;
		this->data[1][1] = 1;
		this->data[1][2] = 0;
		this->data[1][3] = 0;
		this->data[2][0] = 0;
		this->data[2][1] = 0;
		this->data[2][2] = 1;
		this->data[2][3] = 0;
		this->data[3][0] = 0;
		this->data[3][1] = 0;
		this->data[3][2] = 0;
		this->data[3][3] = 1;
	}

	/**
	* Normal constructor with all elements
	*/
	Matrix4D::Matrix4D(double a00, double a01, double a02, double a03, double a10, double a11, double a12, double a13, double a20, double a21, double a22, double a23, double a30, double a31, double a32, double a33)
	{
		this->data[0][0] = a00;
		this->data[0][1] = a01;
		this->data[0][2] = a02;
		this->data[0][3] = a03;
		this->data[1][0] = a10;
		this->data[1][1] = a11;
		this->data[1][2] = a12;
		this->data[1][3] = a13;
		this->data[2][0] = a20;
		this->data[2][1] = a21;
		this->data[2][2] = a22;
		this->data[2][3] = a23;
		this->data[3][0] = a30;
		this->data[3][1] = a31;
		this->data[3][2] = a32;
		this->data[3][3] = a33;
	}

	/**
	* Defines the matrix with a transformation matrix (scaling, rotation or a combination of the two)
	*/
	Matrix4D::Matrix4D(const math3D::Matrix3D& m)
	{
		this->data[0][0] = m.data[0][0];
		this->data[0][1] = m.data[0][1];
		this->data[0][2] = m.data[0][2];
		this->data[0][3] = 0;
		this->data[1][0] = m.data[1][0];
		this->data[1][1] = m.data[1][1];
		this->data[1][2] = m.data[1][2];
		this->data[1][3] = 0;
		this->data[2][0] = m.data[2][0];
		this->data[2][1] = m.data[2][1];
		this->data[2][2] = m.data[2][2];
		this->data[2][3] = 0;
		this->data[3][0] = 0;
		this->data[3][1] = 0;
		this->data[3][2] = 0;
		this->data[3][3] = 1;
	}
	/**
	* Defines a matrix with a translation vector
	*/
	Matrix4D::Matrix4D(const math3D::Vector3D& v)
	{
		this->data[0][0] = 1;
		this->data[0][1] = 0;
		this->data[0][2] = 0;
		this->data[0][3] = v.x;
		this->data[1][0] = 0;
		this->data[1][1] = 1;
		this->data[1][2] = 0;
		this->data[1][3] = v.y;
		this->data[2][0] = 0;
		this->data[2][1] = 0;
		this->data[2][2] = 1;
		this->data[2][3] = v.z;
		this->data[3][0] = 0;
		this->data[3][1] = 0;
		this->data[3][2] = 0;
		this->data[3][3] = 1;
	}
	/**
	* Defines a matrix with a 3x3 transformation matrix and a translation vector
	*/
	Matrix4D::Matrix4D(const math3D::Matrix3D& m, const math3D::Vector3D& v)
	{
		this->data[0][0] = m.data[0][0];
		this->data[0][1] = m.data[0][1];
		this->data[0][2] = m.data[0][2];
		this->data[0][3] = v.x;
		this->data[1][0] = m.data[1][0];
		this->data[1][1] = m.data[1][1];
		this->data[1][2] = m.data[1][2];
		this->data[1][3] = v.y;
		this->data[2][0] = m.data[2][0];
		this->data[2][1] = m.data[2][1];
		this->data[2][2] = m.data[2][2];
		this->data[2][3] = v.z;
		this->data[3][0] = 0;
		this->data[3][1] = 0;
		this->data[3][2] = 0;
		this->data[3][3] = 1;
	}
	/**
	* Copy constructor
	*/
	Matrix4D::Matrix4D(const Matrix4D& m)
	{
		this->data[0][0] = m.data[0][0];
		this->data[0][1] = m.data[0][1];
		this->data[0][2] = m.data[0][2];
		this->data[0][3] = m.data[0][3];
		this->data[1][0] = m.data[1][0];
		this->data[1][1] = m.data[1][1];
		this->data[1][2] = m.data[1][2];
		this->data[1][3] = m.data[1][3];
		this->data[2][0] = m.data[2][0];
		this->data[2][1] = m.data[2][1];
		this->data[2][2] = m.data[2][2];
		this->data[2][3] = m.data[2][3];
		this->data[3][0] = m.data[3][0];
		this->data[3][1] = m.data[3][1];
		this->data[3][2] = m.data[3][2];
		this->data[3][3] = m.data[3][3];
	}
	/**
	* Destructor
	*/
	Matrix4D::~Matrix4D()
	{
	}
	/**
	* Defines this matrix as an identity matrix
	*/
	void Matrix4D::identity()
	{
		*this = Matrix4D();
	}
	/**
	* Defines this matrix as a rotation in the x-axis by theta in degree
	*/
	void Matrix4D::rotationX(double theta)
	{
		math3D::Matrix3D rotation = math3D::Matrix3D();
		rotation.rotationX(theta);
		*this = Matrix4D(rotation);
	}
	/**
	* Defines this matrix as a rotation in y-axis by theta in degree
	*/
	void Matrix4D::rotationY(double theta)
	{
		math3D::Matrix3D rotation = math3D::Matrix3D();
		rotation.rotationY(theta);
		*this = Matrix4D(rotation);
	}
	/**
	* Defines this matrix as a rotation in z-axis by theta in degree
	*/
	void Matrix4D::rotationZ(double theta)
	{
		math3D::Matrix3D rotation = math3D::Matrix3D();
		rotation.rotationZ(theta);
		*this = Matrix4D(rotation);
	}
	/**
	* Defines this matrix as a scaling matrix
	*/
	void Matrix4D::scalingMat(double sx, double sy, double sz)
	{
		math3D::Matrix3D scaling = math3D::Matrix3D();
		scaling.scalingMat(sx, sy, sz);
		*this = Matrix4D(scaling);
	}
	/**
	* Defines this matrix as a translation matrix
	*/
	void Matrix4D::translateMat(double tx, double ty, double tz)
	{
		math3D::Vector3D translate = math3D::Vector3D(tx, ty, tz);
		*this = Matrix4D(translate);
	}
	/**
	* Multiply this matrix with another
	*/
	Matrix4D Matrix4D::matMult(const Matrix4D& m)
	{
		return Matrix4D(
		this->data[0][0]*m.data[0][0]+this->data[0][1]*m.data[1][0]+this->data[0][2]*m.data[2][0]+this->data[0][3]*m.data[3][0],
		this->data[0][0] * m.data[0][1] + this->data[0][1] * m.data[1][1] + this->data[0][2] * m.data[2][1] + this->data[0][3] * m.data[3][1],
			this->data[0][0] * m.data[0][2] + this->data[0][1] * m.data[1][2] + this->data[0][2] * m.data[2][2] + this->data[0][3] * m.data[3][2],
			this->data[0][0] * m.data[0][3] + this->data[0][1] * m.data[1][3] + this->data[0][2] * m.data[2][3] + this->data[0][3] * m.data[3][3],
			this->data[1][0] * m.data[0][0] + this->data[1][1] * m.data[1][0] + this->data[1][2] * m.data[2][0] + this->data[1][3] * m.data[3][0],
			this->data[1][0] * m.data[0][1] + this->data[1][1] * m.data[1][1] + this->data[1][2] * m.data[2][1] + this->data[1][3] * m.data[3][1],
			this->data[1][0] * m.data[0][2] + this->data[1][1] * m.data[1][2] + this->data[1][2] * m.data[2][2] + this->data[1][3] * m.data[3][2],
			this->data[1][0] * m.data[0][3] + this->data[1][1] * m.data[1][3] + this->data[1][2] * m.data[2][3] + this->data[1][3] * m.data[3][3],
			this->data[2][0] * m.data[0][0] + this->data[2][1] * m.data[1][0] + this->data[2][2] * m.data[2][0] + this->data[2][3] * m.data[3][0],
			this->data[2][0] * m.data[0][1] + this->data[2][1] * m.data[1][1] + this->data[2][2] * m.data[2][1] + this->data[2][3] * m.data[3][1],
			this->data[2][0] * m.data[0][2] + this->data[2][1] * m.data[1][2] + this->data[2][2] * m.data[2][2] + this->data[2][3] * m.data[3][2],
			this->data[2][0] * m.data[0][3] + this->data[2][1] * m.data[1][3] + this->data[2][2] * m.data[2][3] + this->data[2][3] * m.data[3][3],
			this->data[3][0] * m.data[0][0] + this->data[3][1] * m.data[1][0] + this->data[3][2] * m.data[2][0] + this->data[3][3] * m.data[3][0],
			this->data[3][0] * m.data[0][1] + this->data[3][1] * m.data[1][1] + this->data[3][2] * m.data[2][1] + this->data[3][3] * m.data[3][1],
			this->data[3][0] * m.data[0][2] + this->data[3][1] * m.data[1][2] + this->data[3][2] * m.data[2][2] + this->data[3][3] * m.data[3][2],
			this->data[3][0] * m.data[0][3] + this->data[3][1] * m.data[1][3] + this->data[3][2] * m.data[2][3] + this->data[3][3] * m.data[3][3]
		);
	}
	/**
	* Matrix multiplication (creates a new matrix)
	*/
	Matrix4D Matrix4D::operator*(const Matrix4D& m)
	{
		return this->matMult(m);
	}
	/**
	* Matrix multiplication (modify this matrix)
	*/
	void Matrix4D::operator*=(const Matrix4D& m)
	{
		*this = this->matMult(m);
	}
	/**
	* Check if two matrices are equals
	*/
	bool Matrix4D::operator==(const Matrix4D& m)
	{
		double epsilon = 1e-13; //Numerical error authorised
		return this->data[0][0] <= m.data[0][0] + epsilon && this->data[0][0] >= m.data[0][0] - epsilon
			&& this->data[0][1] <= m.data[0][1] + epsilon && this->data[0][1] >= m.data[0][1] - epsilon
			&& this->data[0][2] <= m.data[0][2] + epsilon && this->data[0][2] >= m.data[0][2] - epsilon
			&& this->data[0][3] <= m.data[0][3] + epsilon && this->data[0][3] >= m.data[0][3] - epsilon
			&& this->data[1][0] <= m.data[1][0] + epsilon && this->data[1][0] >= m.data[1][0] - epsilon
			&& this->data[1][1] <= m.data[1][1] + epsilon && this->data[1][1] >= m.data[1][1] - epsilon
			&& this->data[1][2] <= m.data[1][2] + epsilon && this->data[1][2] >= m.data[1][2] - epsilon
			&& this->data[1][3] <= m.data[1][3] + epsilon && this->data[1][3] >= m.data[1][3] - epsilon
			&& this->data[2][0] <= m.data[2][0] + epsilon && this->data[2][0] >= m.data[2][0] - epsilon
			&& this->data[2][1] <= m.data[2][1] + epsilon && this->data[2][1] >= m.data[2][1] - epsilon
			&& this->data[2][2] <= m.data[2][2] + epsilon && this->data[2][2] >= m.data[2][2] - epsilon
			&& this->data[2][3] <= m.data[2][3] + epsilon && this->data[2][3] >= m.data[2][3] - epsilon
			&& this->data[3][0] <= m.data[3][0] + epsilon && this->data[3][0] >= m.data[3][0] - epsilon
			&& this->data[3][1] <= m.data[3][1] + epsilon && this->data[3][1] >= m.data[3][1] - epsilon
			&& this->data[3][2] <= m.data[3][2] + epsilon && this->data[3][2] >= m.data[3][2] - epsilon
			&& this->data[3][3] <= m.data[3][3] + epsilon && this->data[3][3] >= m.data[3][3] - epsilon;
	}
	/**
	* Check if two matrices aren't equals
	*/
	bool Matrix4D::operator!=(const Matrix4D& m)
	{
		return !(*this == m);
	}
}