#include "pch.h"
#include "CppUnitTest.h"

#include "Vector3D.h"
#include "Matrix4D.h"
#include "Vector4D.h"
#include "Quaternion.h"
#include <iostream>

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

		/*The rotations has been tested with the debugger and worked fine.
		It cannot be tested without using the definition in the cpp files because of numerical errors.*/

		/*Tests for the definition of the scaling matrix*/
		TEST_METHOD(TestScalingMat)
		{
			Matrix3D test = Matrix3D();
			test.scalingMat(0, 0, 0);
			Assert::IsTrue(Matrix3D(0, 0, 0, 0, 0, 0, 0, 0, 0) == test);

			test.scalingMat(1, 1, 1);
			Assert::IsTrue(Matrix3D() == test);

			test.scalingMat(1.5, 0.75, 0.5);
			Assert::IsTrue(Matrix3D(1.5, 0, 0, 0, 0.75, 0, 0, 0, 0.5) == test);

			test.scalingMat(-5 / 8, 1, 2.46);
			Assert::IsTrue(Matrix3D(-5 / 8, 0, 0, 0, 1, 0, 0, 0, 2.46) == test);
		}

		/*Tests for matrix multiplication*/
		TEST_METHOD(TestMatMultiplication)
		{
			Matrix3D test = Matrix3D(28, 33, 29, 28, 31, 31, 28, 33, 29);
			Assert::IsTrue(test == Matrix3D(1, 2, 3, 3, 2, 1, 1, 2, 3).matMult(Matrix3D(4, 5, 6, 6, 5, 4, 4, 6, 5)));

			Assert::IsTrue(test == test.matMult(Matrix3D()));

			test = Matrix3D(4, 13, 13, -4, -11, -15, 4, 13, 13);
			Assert::IsTrue(test == Matrix3D(1, 2, 3, -3, -2, -1, 1, 2, 3).matMult(Matrix3D(4, 5, 6, -6, -5, -4, 4, 6, 5)));
		}

		/*Tests for scalar multiplication*/
		TEST_METHOD(TestScalarMultiplication)
		{
			Matrix3D test = Matrix3D();
			test.scalarMult(5.0 / 9);

			Assert::IsTrue(Matrix3D(5.0 / 9, 0, 0, 0, 5.0 / 9, 0, 0, 0, 5.0 / 9) == test);

			test = Matrix3D(1, 2, 3, 4, 5, 6, 7, 8, 9);
			test.scalarMult(7);
			Assert::IsTrue(Matrix3D(7, 14, 21, 28, 35, 42, 49, 56, 63) == test);
		}

		/*Tests for the trace of the matrix*/
		TEST_METHOD(TestTrace)
		{
			Matrix3D test = Matrix3D();
			Assert::AreEqual(3.0, test.trace());

			test = Matrix3D(1, 2, 3, 4, 5, 6, 7, 8, 9);
			Assert::AreEqual(15.0, test.trace());

			test = Matrix3D(1, 2, 3, 4, 5, 6, 7, 8, -9);
			Assert::AreEqual(-3.0, test.trace());

			test = Matrix3D(1, 2, 3, -3, -2, -1, 2, 3, 1);
			Assert::AreEqual(0.0, test.trace());
		}

		/*Test for the determinant of the matrix*/
		TEST_METHOD(TestDeterminant)
		{
			Matrix3D test = Matrix3D();
			Assert::AreEqual(1.0, test.determinant());

			test = Matrix3D(1, 2, 3, 4, 5, 6, 7, 8, 9);
			Assert::AreEqual(0.0, test.determinant());

			test = Matrix3D(1, 2, 3, -3, -2, -1, 2, 3, 1);
			Assert::AreEqual(-12.0, test.determinant());
		}

		/*Test for the transpose of the matrix*/
		TEST_METHOD(TestTranspose)
		{
			Matrix3D test = Matrix3D();
			test.transpose();
			Assert::IsTrue(Matrix3D() == test);

			test = Matrix3D(1, 2, 3, 3, 2, 1, 2, 1, 3);
			test.transpose();
			Assert::IsTrue(Matrix3D(1, 3, 2, 2, 2, 1, 3, 1, 3) == test);

			test = Matrix3D(12, 5, 8, 89, 45, 23, 1.02, 2.5, 0.75);
			test.transpose();
			Assert::IsTrue(Matrix3D(12, 89, 1.02, 5, 45, 2.5, 8, 23, 0.75) == test);

			//Check if the transposed give the right result and doesn't modify this
			test = Matrix3D(1, 2, 3, 3, 2, 1, 2, 1, 3);
			Matrix3D trans = test.transposed();
			Assert::IsTrue(Matrix3D(1, 3, 2, 2, 2, 1, 3, 1, 3) == trans);
			Assert::IsTrue(test != trans);

			test = Matrix3D(12, 5, 8, 89, 45, 23, 1.02, 2.5, 0.75);
			trans = test.transposed();
			Assert::IsTrue(Matrix3D(12, 89, 1.02, 5, 45, 2.5, 8, 23, 0.75) == trans);
			Assert::IsTrue(test != trans);
		}

		/*Tests for the inverse of matrix*/
		TEST_METHOD(TestInverseMatrix)
		{
			Matrix3D test = Matrix3D();
			test.inverse();
			Assert::IsTrue(Matrix3D() == test);

			test = Matrix3D(1, 2, 3, 4, 5, 6, 7, 8, 9);
			test.inverse();
			//If it cannot be inverse, it stay the same
			Assert::IsTrue(Matrix3D(1, 2, 3, 4, 5, 6, 7, 8, 9) == test);
			
			test = Matrix3D(1, 2, 3, -2, -3, -6, 7, 8, 9);
			test.inverse();
			Matrix3D result = Matrix3D(-21, -6, 3, 24, 12, 0, -5, -6, -1);
			result.scalarMult(1.0 / 12);

			Assert::IsTrue(result == test);

			//Check if the inversed gives the right result and doesn't modify this
			test = Matrix3D(1, 2, 3, 4, 5, 6, 7, 8, 9);
			Matrix3D inversed = test.inversed();
			Assert::IsTrue(test == inversed);

			test = Matrix3D(1, 2, 3, -2, -3, -6, 7, 8, 9);
			inversed = test.inversed();
			result = Matrix3D(-21, -6, 3, 24, 12, 0, -5, -6, -1);
			result.scalarMult(1.0 / 12.0);
			Assert::IsTrue(result == inversed);
			Assert::IsTrue(inversed != test);

			result = test.matMult(inversed);
			Assert::IsTrue(Matrix3D() == result);
		}

		/*Tests for the operators overloaded*/
		TEST_METHOD(TestOperators)
		{
			//Tests for addition
			Matrix3D test = Matrix3D();
			Matrix3D result = Matrix3D() + test;
			Assert::IsTrue(Matrix3D(2, 0, 0, 0, 2, 0, 0, 0, 2) == result);

			test += Matrix3D();
			Assert::IsTrue(Matrix3D(2, 0, 0, 0, 2, 0, 0, 0, 2) == test);

			test = Matrix3D(1, 2, 3, 4, 5, 6, 7, 8, 9);
			result = test + Matrix3D(-1.0 / 2, -1, -2.5, -3, -4.5, -5, -6.5, -7, -8.5);
			Assert::IsTrue(Matrix3D(1.0 / 2, 1, 1.0 / 2, 1, 1.0 / 2, 1, 1.0 / 2, 1, 1.0 / 2) == result);
			test += Matrix3D(-1.0 / 2, -1, -2.5, -3, -4.5, -5, -6.5, -7, -8.5);
			Assert::IsTrue(Matrix3D(1.0 / 2, 1, 1.0 / 2, 1, 1.0 / 2, 1, 1.0 / 2, 1, 1.0 / 2) == test);

			//Tests for substraction
			test = Matrix3D();
			result = Matrix3D() - test;
			Assert::IsTrue(Matrix3D(0, 0, 0, 0, 0, 0, 0, 0, 0) == result);

			test = Matrix3D(1, 2, 3, 4, 5, 6, 7, 8, 9);
			test -= Matrix3D(9, 8, 7, 6, 5, 4, 3, 2, 1);
			Assert::IsTrue(Matrix3D(-8, -6, -4, -2, 0, 2, 4, 6, 8) == test);

			//Tests for scalar multiplication
			test = Matrix3D();
			Assert::IsTrue(Matrix3D(1.0 / 3, 0, 0, 0, 1.0 / 3, 0, 0, 0, 1.0 / 3) == test * (1.0 / 3));
			Assert::IsTrue(Matrix3D() == test);

			test = Matrix3D(1, 2, 3, 3, 2, 1, 2, 1, 3);
			test *= 9;
			Assert::IsTrue(Matrix3D(9, 18, 27, 27, 18, 9, 18, 9, 27) == test);

			//Tests for Matrix multiplication
			test = Matrix3D();
			test.rotationX(30);
			result = Matrix3D() * test;
			Assert::IsTrue(result == test);

			test = Matrix3D(1, 2, 3, 4, 5, 6, 7, 8, 9);
			result = test * Matrix3D(1, 2, 3, 1, 2, 3, 1, 2, 3);
			Assert::IsTrue(Matrix3D(6, 12, 18, 15, 30, 45, 24, 48, 72) == result);

			test = Matrix3D(1, 2, 3, 4, 5, 6, 7, 8, 9);
			test *= test;
			Assert::IsTrue(Matrix3D(30, 36, 42, 66, 81, 96, 102, 126, 150) == test);
			result = Matrix3D(1, 2, 3, 4, 5, 6, 7, 8, 9);
			Assert::IsTrue(result != test);

			//Tests for scalar division
			test = Matrix3D();
			result = test / 3;
			Assert::IsTrue(Matrix3D(1.0 / 3, 0, 0, 0, 1.0 / 3, 0, 0, 0, 1.0 / 3) == result);

			test = Matrix3D(5, 10, 15, 20, 25, 30, 35, 40, 45);
			test /= 5;
			Assert::IsTrue(Matrix3D(1, 2, 3, 4, 5, 6, 7, 8, 9) == test);
			result = Matrix3D(5, 10, 15, 20, 25, 30, 35, 40, 45);
			Assert::IsTrue(result != test);

			/*The boolean operators are done in the assertions*/
		}
		
	};

	/*Tests for matrix 4D*/
	TEST_CLASS(TestMatrix4D) {

		/*Tests for the identity method and all constructors*/
		TEST_METHOD(TestIdentity)
		{
			math4D::Matrix4D test = math4D::Matrix4D();
			
			Assert::IsTrue(test == math4D::Matrix4D());

			test = math4D::Matrix4D(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
			test.identity();

			Assert::IsTrue(math4D::Matrix4D() == test);

			test = math4D::Matrix4D(Matrix3D(1, 2, 3, 4, 5, 6, 7, 8, 9));
			Assert::IsTrue(math4D::Matrix4D(1, 2, 3, 0, 4, 5, 6, 0, 7, 8, 9, 0, 0, 0, 0, 1) == test);

			test.identity();
			Assert::IsTrue(math4D::Matrix4D() == test);

			test = math4D::Matrix4D(Vector3D(1, 2, 3));
			Assert::IsTrue(math4D::Matrix4D(1, 0, 0, 1, 0, 1, 0, 2, 0, 0, 1, 3, 0, 0, 0, 1) == test);

			test = math4D::Matrix4D(Matrix3D(1, 2, 3, 4, 5, 6, 7, 8, 9), Vector3D(10, 11, 12));
			Assert::IsTrue(math4D::Matrix4D(1, 2, 3, 10, 4, 5, 6, 11, 7, 8, 9, 12, 0, 0, 0, 1) == test);

			math4D::Matrix4D test2 = math4D::Matrix4D(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
			test = math4D::Matrix4D(test2);
			Assert::IsTrue(test == test2);
			
			//Check if a modification of test2 doesn't change test
			test2.identity();
			Assert::IsTrue(test != test2);
			Assert::IsTrue(math4D::Matrix4D() == test2);
		}

		/*Since the tests for the rotations matrices in 3D and the constructors for the matrix4D are done,
		it is not necessary to do unit tests for the rotation matrices for the matrix4D.
		
		For the same reason mentioned before, it is not necessary to do unit tests for the scaling and translate matrices.*/

		/*Tests for matrix multiplication*/
		TEST_METHOD(TestMatrixMultiplication)
		{
			math4D::Matrix4D test = math4D::Matrix4D(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

			Assert::IsTrue(math4D::Matrix4D(0, 0, -6, -8, 0, 0, -6, -8, 0, 0, -6, -8, 0, 0, -6, -8) == test.matMult(math4D::Matrix4D(1, 2, 3, 4, -1, -2, -3, -4, -1, -2, 3, 4, 1, 2, -3, -4)));
		
			Assert::IsTrue(math4D::Matrix4D(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16) == test);

			Assert::IsTrue(test == test.matMult(math4D::Matrix4D()));

			Assert::IsTrue(math4D::Matrix4D(90, 100, 110, 120, 202, 228, 254, 280, 314, 356, 398, 440, 426, 484, 542, 600) == test.matMult(test));
		}

		/*Tests for the operators*/
		TEST_METHOD(TestOperators)
		{
			/*We only need to test the multiplication because the boolean are done in the other tests*/

			math4D::Matrix4D test = math4D::Matrix4D(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
		
			Assert::IsTrue(math4D::Matrix4D(250, 260, 270, 280, 618, 644, 670, 696, 986, 1028, 1070, 1112, 1354, 1412, 1470, 1528) == test * math4D::Matrix4D(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32));
			Assert::IsTrue(math4D::Matrix4D(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16) == test);
			
			test *= math4D::Matrix4D(111, 11, 1, 1111, 11, 55, 103, 95, 2523, 125, 92, 870, 7, 2, 8, 3);
			Assert::IsTrue(math4D::Matrix4D(7730, 504, 515, 3923, 18338, 1276, 1331, 12239, 28946, 2048, 2147, 20555, 39554, 2820, 2963, 28871) == test);
		}
	};

	/*Tests for the vector4D*/
	TEST_CLASS(TestVector4D)
	{
		/*Tests for the constructors*/
		TEST_METHOD(TestConstructors)
		{
			math4D::Vector4D test = math4D::Vector4D();

			Assert::IsTrue(test.coordinates == Vector3D() && test.w == 1.0);

			test = math4D::Vector4D(1, 2, 3, 4);
			Assert::IsTrue(test.coordinates == Vector3D(1, 2, 3) && test.w == 4.0);

			test = math4D::Vector4D(1, 2, 3);
			Assert::IsTrue(test.coordinates == Vector3D(1, 2, 3) && test.w == 1.0);

			test = math4D::Vector4D(Vector3D(4, 5, 6));
			Assert::IsTrue(test.coordinates == Vector3D(4, 5, 6) && test.w == 1.0);

			math4D::Vector4D test2 = math4D::Vector4D(7, 8, 9, 2);
			test = math4D::Vector4D(test2);
			Assert::IsTrue(test == test2);
			test2 = math4D::Vector4D(1, 2, 3, 4);
			Assert::IsTrue(test == math4D::Vector4D(7, 8, 9, 2));
			Assert::IsTrue(test != test2);
		}

		/*Tests for the w normalization*/
		TEST_METHOD(TestWNormalize)
		{
			math4D::Vector4D test = math4D::Vector4D(1, 2, 3, 0);
			test.wNormalize();
			Assert::IsTrue(math4D::Vector4D(1, 2, 3, 0) == test);

			test = math4D::Vector4D(4, 6, 8, 2);
			test.wNormalize();
			Assert::IsTrue(math4D::Vector4D(2, 3, 4, 1) == test);

			test = math4D::Vector4D(5, 8, 7, 0.1);
			test.wNormalize();
			Assert::IsTrue(math4D::Vector4D(50, 80, 70, 1) == test);
		}

		/*Tests for the vector/matrix multiplication*/
		TEST_METHOD(TestVectMatMultiplication)
		{
			math4D::Vector4D test = math4D::Vector4D(2, 3, 4, 1);
			Assert::IsTrue(math4D::Vector4D(10354, 689, 687, 5990) == test.matMult(math4D::Matrix4D(111, 11, 1, 1111, 11, 55, 103, 95, 2523, 125, 92, 870, 7, 2, 8, 3)));

			Assert::IsTrue(math4D::Vector4D(66, 76, 86, 96) == test.matMult(math4D::Matrix4D(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16)));

			test = math4D::Vector4D(0, 5, 6, 9);
			Assert::IsTrue(math4D::Vector4D(196, 216, 236, 256) == test.matMult(math4D::Matrix4D(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16)));

			Assert::IsTrue(math4D::Vector4D(146, 96, 166, 112) == test.matMult(math4D::Matrix4D(1, 2, 3, 4, -5, 6, -7, 8, 9, -10, 11, -12, 13, 14, 15, 16)));
		}

		/*Tests for the operators*/
		TEST_METHOD(TestOperators)
		{
			/*Only the multiplications tests will be done because the boolean operators are done implicitly in the other tests.*/
			math4D::Vector4D test = math4D::Vector4D(-5, 4, -8, 1);
			Assert::IsTrue(math4D::Vector4D(-84, 108, -116, 124) == test * math4D::Matrix4D(1, 2, 3, 4, -5, 6, -7, 8, 9, -10, 11, -12, 13, 14, 15, 16));

			Assert::IsTrue(math4D::Vector4D(-5, 4, -8, 1) == test);

			Assert::IsTrue(test == test * math4D::Matrix4D());

			test = math4D::Vector4D(1, 2, 3, 1);
			test *= math4D::Matrix4D(1, 2, 3, 4, -5, 6, -7, 8, 9, -10, 11, -12, 13, 14, 15, 16);
			Assert::IsTrue(math4D::Vector4D(31, -2, 37, 0) == test);

			test = math4D::Vector4D(1, 2, 3, 1);
			test *= math4D::Matrix4D(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
			Assert::IsTrue(math4D::Vector4D(51, 58, 65, 72) == test);
		}
	};

	/*Tests for the quaternion*/
	TEST_CLASS(TestsQuaternions)
	{
		/*Tests for the constructors*/
		TEST_METHOD(TestsConstructor)
		{
			Assert::IsTrue(math4D::Quaternion() == math4D::Quaternion());
			math4D::Quaternion quatTest = math4D::Quaternion();

			Assert::AreEqual(quatTest.scalar, 1.0);
			Assert::IsTrue(quatTest.vector == Vector3D());

			Vector3D test = Vector3D(1, 2, 3);
			quatTest = math4D::Quaternion(2 / 5);
			Assert::IsTrue(quatTest.scalar == 2 / 5 && quatTest.vector == Vector3D());

			quatTest = math4D::Quaternion(0, test);
			Assert::IsTrue(quatTest.scalar == 0 && quatTest.vector == Vector3D(1, 2, 3));

			//Euler angles
			quatTest = math4D::Quaternion(90, 90, 0);
			Assert::IsTrue(math4D::Quaternion(1.0/2.0,Vector3D(1.0/2.0,1.0/2.0,-1.0/2.0)) == quatTest);
			
			quatTest = math4D::Quaternion(0, 0, 0);
			Assert::IsTrue(math4D::Quaternion() == quatTest);

			//Copy constructors
			quatTest = math4D::Quaternion(1.0 / 2.0, Vector3D(1, 2, 3));
			math4D::Quaternion test2 = math4D::Quaternion(quatTest);
			Assert::IsTrue(test2 == quatTest);

			quatTest = math4D::Quaternion(25);
			Assert::IsTrue(test2 != quatTest && quatTest != math4D::Quaternion(1.0 / 2.0, Vector3D(1, 2, 3)));
		}

		/*Tests for the norm and normalize methods*/
	};
}
