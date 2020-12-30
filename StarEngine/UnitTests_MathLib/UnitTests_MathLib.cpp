#include "pch.h"
#include "CppUnitTest.h"
#include "Vector3D.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace math3D;

namespace UnitTestsMathLib
{	

	TEST_CLASS(UnitTestsVector3D)
	{
	public:
		/*Test for methods norm and norm2*/
		TEST_METHOD(TestNormNorm2)
		{
			//Null vectors test
			Assert::AreEqual(0.0, Vector3D().norm());
			Assert::AreEqual(0.0, Vector3D().norm2());

			//Unit vectors tests
			Assert::AreEqual(1.0, Vector3D(1,0,0).norm());
			Assert::AreEqual(1.0, Vector3D(0,0,1).norm2());

			//Other length tests
			Assert::AreEqual(3.0, Vector3D(0,0,3).norm());
			Assert::AreEqual(9.0, Vector3D(3,0,0).norm2());

			//Non negative test
			Assert::IsTrue(Vector3D(0, -1, 1).norm() >= 0);
			Assert::IsTrue(Vector3D(-1, -1, -1).norm2() >= 0);
		}

		/*Test for methods normalize and normalized*/
		TEST_METHOD(TestNormalizeNormalized) 
		{
			//Length = 1
			Vector3D test1 = Vector3D(2, 23, 65);
			test1.normalize();

			Assert::AreEqual(1.0, test1.norm());
			Assert::AreEqual(1.0, Vector3D(12, 45, 6).normalized().norm());

			//No normalization if length of vector is 0
			Vector3D test2 = Vector3D();
			test2.normalize();

			Assert::AreNotEqual(1.0, test2.norm());
			Assert::AreNotEqual(1.0, Vector3D().normalized().norm());
		}

		/*Test for method dot product*/
		TEST_METHOD(TestDot)
		{
			//Orthogonal vectors or product with null vector
			Assert::AreEqual(0.0, Vector3D().dot(Vector3D(1, 54, 78)));
			Assert::AreEqual(0.0, Vector3D(1, 0, 0).dot(Vector3D(0, 0, 1)));

			//Equals something else
			Assert::AreEqual(6.0, Vector3D(1, 1, 1).dot(Vector3D(1, 2, 3)));
			Assert::AreEqual(-31.0, Vector3D(1, -6, -8).dot(Vector3D(-3, -10, 11)));
		}

		/*Test for method cross product*/
		TEST_METHOD(TestCross)
		{
			//Cross product between two linear dependent vectors
			Assert::IsTrue(Vector3D() == Vector3D(0, 0, 0).cross(Vector3D(1, 654, 98)));
			Assert::IsTrue(Vector3D() == Vector3D(1, 2, 3).cross(Vector3D(5, 10, 15)));
			Assert::IsTrue(Vector3D() == Vector3D(-1, 0, 5).cross(Vector3D(-5, 0, 25)));

			//Cross product between other vectors
			Assert::IsTrue(Vector3D(0, 0, 1) == Vector3D(1, 0, 0).cross(Vector3D(0, 1, 0)));
			Assert::IsTrue(Vector3D(0, 0, -1) == Vector3D(0, 1, 0).cross(Vector3D(1, 0, 0)));
			Assert::IsTrue(Vector3D(-3, 6, -3) == Vector3D(1, 2, 3).cross(Vector3D(4, 5, 6)));
			Assert::IsTrue(Vector3D(3, -6, 3) == Vector3D(4, 5, 6).cross(Vector3D(1, 2, 3)));	
		}

		/*Test for vector-matrix multiplication method*/
		TEST_METHOD(TestMatMult)
		{
			//Null result
			Matrix3D test = Matrix3D();
			test.rotationX(30.0);

			Assert::IsTrue(Vector3D() == Vector3D().matMult(Matrix3D()));
			Assert::IsTrue(Vector3D() == Vector3D().matMult(test));
			
			//Other results
			Assert::IsTrue(Vector3D(1, sqrt(3) + 1.5, -1 + 3 * sqrt(3) / 2) == Vector3D(1, 2, 3).matMult(test));

		}

		/*Tests for operators*/
		TEST_METHOD(TestOperators)
		{
			//Addition
			Assert::IsTrue(Vector3D(5, 7, 9) == (Vector3D(1, 2, 3) + Vector3D(4, 5, 6)));
			Assert::IsTrue(Vector3D(5, 3, 9) == (Vector3D(1, -2, 3) + Vector3D(4, 5, 6)));
			Assert::IsTrue(Vector3D(55, 89, 0) == (Vector3D(0, 0, 0) + Vector3D(55, 89, 0)));
			Assert::IsTrue(Vector3D(55, 89, 0) == (Vector3D(55, 89, 0) + Vector3D()));

			Vector3D test = Vector3D(1, 2, 3);
			test += Vector3D(4, 5, 6);
			Assert::IsTrue(Vector3D(5, 7, 9) == test);

			//Substraction
			Assert::IsTrue(Vector3D(-3, -3, -3) == (Vector3D(1, 2, 3) - Vector3D(4, 5, 6)));
			Assert::IsTrue(Vector3D(-3, -7, -3) == (Vector3D(1, -2, 3) - Vector3D(4, 5, 6)));
			Assert::IsTrue(Vector3D(5, 12, 3) == (Vector3D(5, 12, 3) - Vector3D()));
			Assert::IsTrue(Vector3D(-5, -12, -3) == (Vector3D() - Vector3D(5, 12, 3)));

			test = Vector3D(1, 2, 3);
			test -= Vector3D(4, 5, 6);
			Assert::IsTrue(Vector3D(-3, -3, -3) == test);

			//Dot and scalar product
			Assert::AreEqual(0.0, Vector3D() * Vector3D(5, 6, 2));
			Assert::AreEqual(0.0, Vector3D(1, 0, 0) * Vector3D(0, 1, 0));

			Assert::AreEqual(6.0, Vector3D(1, 1, 1) * Vector3D(1, 2, 3));

			Assert::IsTrue(Vector3D()== Vector3D(1, 2, 3) * 0);
			Assert::IsTrue(Vector3D(-15, 60, 20) == Vector3D(-3, 12, 4) * 5);
			Assert::IsTrue(Vector3D(0.5, 0.75, 0.25) == Vector3D(2, 3, 1) * 0.25);

			//Vector-Matrix multiplicator
			Matrix3D test1 = Matrix3D();
			test1.rotationX(30.0);
			Assert::IsTrue(Vector3D(32, 54, 85) == Vector3D(32, 54, 85) * Matrix3D());
			Assert::IsTrue(Vector3D(1, sqrt(3) + 1.5, -1 + 3 * sqrt(3) / 2) == Vector3D(1, 2, 3) * test1);

			//Scalar division
			Assert::IsTrue(Vector3D() == Vector3D() / 2);
			Assert::IsTrue(Vector3D(1, 2, 3) == Vector3D(1, 2, 3) / 1.0);
			Assert::IsTrue(Vector3D(-3, 12, 4) == Vector3D(-15, 60, 20) / 5.0);
			Assert::IsTrue(Vector3D(0.5, 0.75, 0.25) == Vector3D(2, 3, 1) / 4);

			//Cross Product
			test = Vector3D(1, 0, 0);
			test %= Vector3D(0, 1, 0);
			
			Assert::IsTrue(Vector3D(0, 0, 1) == test);
			Assert::IsTrue(Vector3D(-3, 6, -3) == Vector3D(1, 2, 3) % Vector3D(4, 5, 6));
			
			//Not equals
			Assert::IsTrue(Vector3D() != Vector3D(1, 0, 0));
			Assert::IsTrue(Vector3D(1, 0, 0) != Vector3D(0, 1, 0));
		}
	};

	//TODO Rendu là (dois faire les tests pour matrix3D)
	TEST_CLASS(UnitTestsMatrix3D) {

		/*Test the identity method*/
		TEST_METHOD(TestIdentity)
		{
			//Check if the identity method resets the matrix to identity
			Matrix3D test = Matrix3D();
			test.identity();

			Assert::IsTrue(Matrix3D() == test);
			test = Matrix3D(1, 2, 3, 4, 5, 6, 7, 8, 9);
			test.identity();
			Assert::IsTrue(Matrix3D() == test);
		}

		/*Test for the rotation matrices*/
		TEST_METHOD(TestRotationsMatrices)
		{
			//Check for the rotation by the x axis
			Matrix3D test = Matrix3D();
			test.rotationX(30.0);
			Assert::IsTrue(Matrix3D(1, 0, 0, 0, sqrt(3) / 2, -1 / 2, 0, 1 / 2, sqrt(3) / 2) == test);

			test.identity();
			test.rotationX(45.0);
			Assert::IsTrue(Matrix3D(1, 0, 0, 0, 1 / sqrt(2), -1 / sqrt(2), 0, 1 / sqrt(2), 1 / sqrt(2)) == test);

			test.identity();
			test.rotationX(180);
			Assert::IsTrue(Matrix3D(1, 0, 0, 0, -1, 0, 0, 0, -1) == test);

			//Check for the rotation by the y axis
			test.identity();
			test.rotationY(30.0);
			Assert::IsTrue(Matrix3D(sqrt(3) / 2, 0, 1 / 2, 0, 1, 0, -1 / 2, 0, sqrt(3)) == test);

			test.identity();
			test.rotationY(45.0);
			Assert::IsTrue(Matrix3D(1 / sqrt(2), 0, 1 / sqrt(2), 0, 1, 0, -1 / sqrt(2), 0, 1 / sqrt(2)) == test);

			test.identity();
			test.rotationY(180);
			Assert::IsTrue(Matrix3D(-1, 0, 0, 0, 1, 0, 0, 0, -1) == test);

			//Check for the rotation by the z axis
			test.identity();
			test.rotationZ(30.0);
			Assert::IsTrue(Matrix3D(sqrt(3) / 2, -1 / 2, 0, 1 / 2, sqrt(3) / 2, 0, 0, 0, 1) == test);

			test.identity();
			test.rotationZ(45.0);
			Assert::IsTrue(Matrix3D(1 / sqrt(2), -1 / sqrt(2), 0, 1 / sqrt(2), 1 / sqrt(2), 0, 0, 0, 1) == test);

			test.identity();
			test.rotationZ(180);
			Assert::IsTrue(Matrix3D(-1, 0, 0, 0, -1, 0, 0, 0, 1) == test);
		}
	};
}
