#pragma once
#include "Matrix4D.h"
#include "Vector3D.h"


namespace math4D {
	struct Quaternion
	{
		/*Attributes*/
		double scalar;
		math3D::Vector3D vector;

		//Constructors
		Quaternion();
		Quaternion(double scalar, const math3D::Vector3D& vector);
		Quaternion(double x, double y, double z); //Make quaternion from Euler angles (roll=x, pitch=y, yaw=z)
		Quaternion(const Quaternion& quat);

		//Destructor
		~Quaternion();

		/*Other methods*/
		double norm(); //Norm (Magnitude)
		void normalize(); //Every quaternion must be normalized
		void conjugate(); //Conjugate the quaternion

		Quaternion addQuat(const Quaternion& quat);
		Quaternion scalarMult(double s);
		Quaternion quatMult(const Quaternion& quat);
		Quaternion vectMult(const math3D::Vector3D& v);

		double rotationAngle();
		math3D::Vector3D rotationAxis();
		Quaternion rotateQuat();

		math3D::Vector3D rotateVector(const math3D::Vector3D& v); //Rotate vector by this quaternion
		math3D::Vector3D eulerAngles(); //Get Euler angles from this quaternion
		Matrix4D rotationMatrix(); //Get rotation matrix4x4

		/*Operators overload*/
		
		//Quaternions addition
		Quaternion operator+(const Quaternion& quat);
		void operator+=(const Quaternion& quat);

		//Quaternions substraction
		Quaternion operator-(const Quaternion& quat);
		void operator-=(const Quaternion& quat);

		//Scalar multiplication
		Quaternion operator*(double s);
		Quaternion operator*(int s);
		void operator*=(double v);
		void operator*=(int v);

		//Quaternion multiplication
		Quaternion operator*(const Quaternion& quat);
		void operator*=(const Quaternion& quat);

		//Vector multiplication
		Quaternion operator*(const math3D::Vector3D& v);
		void operator*=(const math3D::Vector3D& v);

		//Scalar division
		Quaternion operator/(double s);
		Quaternion operator/(int s);
		void operator/=(double s);
		void operator/=(int s);

		//2 Vectors are equals or not if they have or not the same vector and scalar
		bool operator==(const Quaternion& quat);
		bool operator!=(const Quaternion& quat);
	};
}

