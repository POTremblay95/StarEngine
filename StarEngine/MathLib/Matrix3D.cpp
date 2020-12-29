#include "Matrix3D.h"

/**
* Matrix3D default constructor (identity matrix)
*/
math3D::Matrix3D::Matrix3D()
{
	data[0][0] = 1;
	data[1][1] = 1;
	data[2][2] = 1;
}
/**
* Matrix3D constructor with all elements
*/
math3D::Matrix3D::Matrix3D(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33)
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
math3D::Matrix3D::Matrix3D(const Matrix3D& copyMat)
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
* Matrix3D constructor with 3 column vectors
*/
math3D::Matrix3D::Matrix3D(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3)
{
	data[0][0] = v1.x;
	data[0][1] = v2.x;
	data[0][2] = v3.x;
	data[1][0] = v1.y;
	data[1][1] = v2.y;
	data[1][2] = v3.y;
	data[2][0] = v1.z;
	data[2][1] = v2.z;
	data[2][2] = v3.z;
}
/**
* Matrix3D destructor
*/
math3D::Matrix3D::~Matrix3D()
{
}

/**
* Change this matrix to identity matrix
*/
void math3D::Matrix3D::identity()
{
	*this = Matrix3D();
}
