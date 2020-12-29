#pragma once
namespace math3D {

	struct Vector3D
	{

		//Attributes
		float x;
		float y;
		float z;

		/*Methods*/

		//Constructors
		Vector3D();
		Vector3D(float x=0.0, float y=0.0, float z=0.0);
		Vector3D(const Vector3D &v);

		//Destructors
		~Vector3D();

		// TODO toString method

		//Other methods
		float norm(); //Return norm of vector
		float norm2(); //Return norm square of vector

		void normalize(); //Normalize this vector
		Vector3D normalized(); //Return a copy of this vector normalized without normalizing this vector

		float dot(const Vector3D &v); //Dot (scalar) product
		//Cross product
		Vector3D cross(const Vector3D &v);

		/*Operators overload*/

		//Vectors addition
		Vector3D operator+(const Vector3D &v);
		void operator+=(const Vector3D &v);

		//Vectors substraction
		Vector3D operator-(const Vector3D &v);
		void operator-=(const Vector3D &v);

		//Dot and scalar product
		Vector3D operator*(float &v);
		Vector3D operator*(int &v);
		float operator*(const Vector3D &v);
		void operator*=(float &v);
		void operator*=(int &v);

		/*TODO : Je suis rendu là*/
		//Scalar division
		Vector3D operator/(float &v);
		Vector3D operator/(int &v);
		void operator/=(float &v);
		void operator/=(int &v);

		//Cross product
		Vector3D operator%(float& v);
		Vector3D operator%(int& v);
		Vector3D operator%(const Vector3D& v);
		void operator%=(float& v);
		void operator%=(int& v);
		void operator%=(const Vector3D& v);

		//2 Vectors are equals or not if they have or not the same coordinates
		bool operator==(Vector3D v);
		bool operator!=(Vector3D v);

	};
}
