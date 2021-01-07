#define _USE_MATH_DEFINES

#include "Quaternion.h"
#include <cmath>

namespace math4D {
	/**
	* Default Quaternion : vector = (0,0,0) and scalar = 1
	*/
	Quaternion::Quaternion()
	{
		this->vector = math3D::Vector3D();
		this->scalar = 1;
	}
	/**
	* Constructor with a scalar and a vector
	*/
	Quaternion::Quaternion(double scalar, const math3D::Vector3D& vector)
	{
		this->vector = vector;
		this->scalar = scalar;
	}
	/**
	* Constructor with Euler angles in degrees (roll=x, pitch=y, yaw=z)
	*/
	Quaternion::Quaternion(double x, double y, double z)
	{
		x *= M_PI / 180;
		y *= M_PI / 180;
		z *= M_PI / 180;

		this->scalar = cos(x / 2) * cos(y / 2) * cos(z / 2) + sin(x / 2) * sin(y / 2) * sin(z / 2);
		this->vector = math3D::Vector3D(
			sin(x / 2) * cos(y / 2) * cos(z / 2) - cos(x / 2) * sin(y / 2) * sin(z / 2),
			cos(x / 2) * sin(y / 2) * cos(z / 2) - sin(x / 2) * cos(y / 2) * sin(z / 2),
			cos(x / 2) * cos(y / 2) * sin(z / 2) - sin(x / 2) * sin(y / 2) * cos(z / 2)
		);
	}
	/**
	* Copy constructor
	*/
	Quaternion::Quaternion(const Quaternion& quat)
	{
		*this = quat;
	}
	/**
	* Default destructor
	*/
	Quaternion::~Quaternion()
	{
	}
	/**
	* Norm squared of the quaternion
	*/
	double Quaternion::norm()
	{
		return pow(this->scalar, 2) + this->vector.norm2();
	}
	/**
	* Normalize this quaternion (every quaternion must be normalized by definition)
	*/
	void Quaternion::normalize()
	{
		double length = this->norm();
		this->vector /= length;
		this->scalar /= length;
	}
	/**
	* Conjugate this quaternion
	*/
	Quaternion Quaternion::conjugate()
	{
		return Quaternion(this->scalar, this->vector.reversed());
	}
	/**
	* Quaternion additions (creates a new quaternion)
	*/
	Quaternion Quaternion::addQuat(const Quaternion& quat)
	{
		return Quaternion(
			this->scalar + quat.scalar,
			this->vector + quat.vector
		);
	}
	/**
	* Scalar multiplication (creates a new quaternion)
	*/
	Quaternion Quaternion::scalarMult(double s)
	{
		return Quaternion(this->scalar * s, this->vector * s);
	}
	/**
	* Quaternion multiplication (creates a new quaternion)
	*/
	Quaternion Quaternion::quatMult(const Quaternion& quat)
	{
		return Quaternion(
			this->scalar * quat.scalar - this->vector * quat.vector,
			math3D::Vector3D(quat.vector) * this->scalar + this->vector * quat.scalar + this->vector % quat.vector
		);
	}
	/**
	* Quaternion/vector multiplication
	*/
	Quaternion Quaternion::vectMult(const math3D::Vector3D& v)
	{
		return Quaternion(
			-(this->vector * v),
			math3D::Vector3D(v.x * this->scalar + this->vector.y * v.z - this->vector.z * v.y,
				v.y * this->scalar + this->vector.x * v.z - this->vector.z * v.x,
				v.z * this->scalar + this->vector.y * v.x - this->vector.x * v.y)
		);
	}
	/**
	* Get the rotation angle from the axis of the quaternion
	*/
	double Quaternion::rotationAngle()
	{
		return 2 * acos(this->scalar);
	}
	/**
	* Get the rotation axis of the quaternion 
	*/
	math3D::Vector3D Quaternion::rotationAxis()
	{
		return this->vector.normalized();
	}
	/**
	* Rotate the Quaternion by quat (creates a new quaternion)
	*/
	Quaternion Quaternion::rotateQuat(const Quaternion& quat)
	{
		Quaternion q = Quaternion(quat);
		return q.quatMult(*this).quatMult(q.conjugate());
	}
	/**
	* Rotate the vector by the quaternion (creates a new vector)
	*/
	math3D::Vector3D Quaternion::rotateVector(const math3D::Vector3D& v)
	{
		return this->vectMult(v).quatMult(this->conjugate()).vector;
	}
	/**
	* Get the Euler angles in degrees from the quaternion in the form (x,y,z)=(roll,pitch,yaw)
	*/
	math3D::Vector3D Quaternion::eulerAngles()
	{
		return math3D::Vector3D(
			atan((2 * this->vector.z * this->vector.y + 2 * this->vector.x * this->scalar) / (pow(this->scalar, 2) - pow(this->vector.x, 2) - pow(this->vector.y, 2) + pow(this->vector.z, 2))),
			asin(2 * this->vector.y * this->scalar - 2 * this->vector.z * this->vector.x),
			atan((2 * this->vector.x * this->vector.y + 2 * this->vector.z * this->scalar) / (pow(this->scalar, 2) + pow(this->vector.x, 2) - pow(this->vector.y, 2) - pow(this->vector.z, 2)))
		) * 180 / M_PI;
	}
	/**
	* Get the rotation matrix from the quaternion (3x3)
	*/
	math3D::Matrix3D Quaternion::rotationMatrix()
	{
		return math3D::Matrix3D(
			pow(this->scalar, 2) + pow(this->vector.x, 2) - pow(this->vector.y, 2) - pow(this->vector.z, 2),
			2 * this->vector.x * this->vector.y - 2 * this->vector.z * this->scalar,
			2 * this->vector.x * this->vector.z + 2 * this->vector.y * this->scalar,
			2 * this->vector.x * this->vector.y + 2 * this->vector.z * this->scalar,
			pow(this->scalar, 2) - pow(this->vector.x, 2) + pow(this->vector.y, 2) - pow(this->vector.z, 2),
			2 * this->vector.y * this->vector.z - 2 * this->vector.x * this->scalar,
			2 * this->vector.z * this->vector.x - 2 * this->vector.y * this->scalar,
			2 * this->vector.z * this->vector.y + 2 * this->vector.x * this->scalar,
			pow(this->scalar, 2) - pow(this->vector.x, 2) - pow(this->vector.y, 2) + pow(this->vector.z, 2)
		);
	}
	/*Operators overload*/
	/**
	* Quaternion addition (creates a new quaternion)
	*/
	Quaternion Quaternion::operator+(const Quaternion& quat)
	{
		return this->addQuat(quat);
	}
	/**
	* Quaternion addition (modify this quaternion)
	*/
	void Quaternion::operator+=(const Quaternion& quat)
	{
		*this = *this + quat;
	}
	/**
	* Quaternion substraction (creates a new quaternion)
	*/
	Quaternion Quaternion::operator-(const Quaternion& quat)
	{
		return Quaternion(this->scalar - quat.scalar,
			this->vector - quat.vector);
	}
	/**
	* Quaternion substraction (modify this quaternion)
	*/
	void Quaternion::operator-=(const Quaternion& quat)
	{
		*this = *this - quat;
	}
	/**
	* Scalar multiplication (creates a new quaternion)
	*/
	Quaternion Quaternion::operator*(double s)
	{
		return this->scalarMult(s);
	}
	/**
	* Scalar multiplication (modify this quaternion)
	*/
	void Quaternion::operator*=(double s)
	{
		*this = *this * s;
	}
	/**
	* Quaternion multiplication (creates a new quaternion)
	*/
	Quaternion Quaternion::operator*(const Quaternion& quat)
	{
		return this->quatMult(quat);
	}
	/**
	* Quaternion multiplication (modify this quaternion)
	*/
	void Quaternion::operator*=(const Quaternion& quat)
	{
		*this = *this * quat;
	}
	/**
	* Vector multiplication (creates a new quaternion)
	*/
	Quaternion Quaternion::operator*(const math3D::Vector3D& v)
	{
		return this->vectMult(v);
	}
	/**
	* Vector multiplication (modify this quaternion)
	*/
	void Quaternion::operator*=(const math3D::Vector3D& v)
	{
		*this = *this * v;
	}
	/**
	* Scalar division (creates a new quaternion)
	*/
	Quaternion Quaternion::operator/(double s)
	{
		return this->scalarMult(1.0 / s);
	}
	/**
	* Scalar division (modify this quaternion)
	*/
	void Quaternion::operator/=(double s)
	{
		*this = *this / s;
	}
	/**
	* Check if two quaternions are equals
	*/
	bool Quaternion::operator==(const Quaternion& quat)
	{
		return this->scalar == quat.scalar && this->vector == quat.vector;
	}
	/**
	* Check if two quaternions aren't equals
	*/
	bool Quaternion::operator!=(const Quaternion& quat)
	{
		return !(*this == quat);
	}


}
