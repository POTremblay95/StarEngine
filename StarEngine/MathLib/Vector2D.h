#pragma once

namespace math2D {

	class Vector2D
	{
	public:
		
		//Attributes
		double x;
		double y;

		/*Methods*/
		
		//Constructors
		Vector2D();
		Vector2D(double &x, double &y);
		Vector2D(const Vector2D &v);

		//Destructors
		~Vector2D(); //Check how to do it

		//Other methods
		double norm();
		double norm2();

		//TODO scalar product, cross product, normalization

		//Operators overload

		//TODO +,+=,-,-=,*,*=,/,/=, ==, !=, >, >=, <, <=


	private:
		double length;
	};
}

