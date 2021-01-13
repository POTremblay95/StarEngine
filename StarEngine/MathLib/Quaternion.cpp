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
	* Constructor with the scalar and all coordinates
	*/
	Quaternion::Quaternion(double scalar, double x, double y, double z)
	{
		this->vector = math3D::Vector3D(x, y, z);
		this->scalar = scalar;
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
		double roll = x * M_PI / 180;
		double pitch = y * M_PI / 180;
		double yaw = z * M_PI / 180;

		this->scalar = cos(roll / 2) * cos(pitch / 2) * cos(yaw / 2) + sin(roll / 2) * sin(pitch / 2) * sin(yaw / 2);
		this->vector = math3D::Vector3D(
			sin(roll / 2) * cos(pitch / 2) * cos(yaw / 2) - cos(roll / 2) * sin(pitch / 2) * sin(yaw / 2),
			cos(roll / 2) * sin(pitch / 2) * cos(yaw / 2) + sin(roll / 2) * cos(pitch / 2) * sin(yaw / 2),
			cos(roll / 2) * cos(pitch / 2) * sin(yaw / 2) - sin(roll / 2) * sin(pitch / 2) * cos(yaw / 2)
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
	* Norm (magnitude) of the quaternion
	*/
	double Quaternion::norm()
	{
		return sqrt(pow(this->scalar, 2) + this->vector.norm2());
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
	* Quaternion conjugate normalized
	*/
	Quaternion Quaternion::inverse()
	{
		Quaternion result = this->conjugate();
		result.normalize();

		return result;
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
				v.y * this->scalar + this->vector.z * v.x - this->vector.x * v.z,
				v.z * this->scalar + this->vector.x * v.y - this->vector.y * v.x)
		);
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
		double epsilon = 1e-15; //Numerical error authorised
		return this->scalar <= quat.scalar + epsilon && this->scalar >= quat.scalar - epsilon && this->vector == quat.vector;
	}
	/**
	* Check if two quaternions aren't equals
	*/
	bool Quaternion::operator!=(const Quaternion& quat)
	{
		return !(*this == quat);
	}


}
