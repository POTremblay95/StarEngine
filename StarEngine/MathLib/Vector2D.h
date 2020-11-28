#pragma once

namespace math2D {

	class Vector2D
	{
	public:
		
		//Attributes
		float x;
		float y;

		/*Methods*/
		
		//Constructors
		Vector2D();
		Vector2D(float x, float y);
		Vector2D(const Vector2D v);

		//Destructors
		~Vector2D();
		
		// TODO toString method

		//Other methods
		float norm(); //Return norm of vector
		float norm2(); //Return norm square of vector

		void normalize(); //Normalize this vector
		Vector2D normalized(); //Return a copy of this vector normalized without normalizing this vector

		float length();

		float dot(Vector2D v); //Dot (scalar) product
		//Cross product not needed for now

		//Operators overload

		Vector2D operator+(Vector2D v);
		void operator+=(Vector2D v);

		Vector2D operator-(Vector2D v);
		void operator-=(Vector2D v);

		Vector2D operator*(float v);
		Vector2D operator*(int v);
		void operator*=(float v);
		void operator*=(int v);

		Vector2D operator/(float v);
		Vector2D operator/(int v);
		void operator/=(float v);
		void operator/=(int v);

		//2 Vectors are equals or not if they have the same coordinates
		bool operator==(Vector2D v);
		bool operator!=(Vector2D v);

	};
}

