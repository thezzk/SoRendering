#include "pch.h"
#include "raymath.h"
#include "SoMath.h"
#include "CppUnitTest.h"
#include <Eigen/Core>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{
	TEST_CLASS(TransformABTest)
	{
	public:
		bool QuatCompare(Quaternion rayQuat, SoRendering::SoQuaternion soQuat)
		{
			return
				SoRendering::SoMath::EqualWithEpsilon(rayQuat.x, soQuat[0]) &&
				SoRendering::SoMath::EqualWithEpsilon(rayQuat.y, soQuat[1]) &&
				SoRendering::SoMath::EqualWithEpsilon(rayQuat.z, soQuat[2]) &&
				SoRendering::SoMath::EqualWithEpsilon(rayQuat.w, soQuat[3]);

		}

		bool Vector3Compare(Vector3 rayVec3, SoRendering::SoVector3f soVec3)
		{
			return
				SoRendering::SoMath::EqualWithEpsilon(rayVec3.x, soVec3[0]) &&
				SoRendering::SoMath::EqualWithEpsilon(rayVec3.y, soVec3[1]) &&
				SoRendering::SoMath::EqualWithEpsilon(rayVec3.z, soVec3[2]);
		}

		bool MatrixCompare(Matrix rayMat, SoRendering::SoMatrix4f soMat)
		{
			return
				SoRendering::SoMath::EqualWithEpsilon(soMat(0, 0), rayMat.m0) &&
				SoRendering::SoMath::EqualWithEpsilon(soMat(0, 0), rayMat.m0) &&
				SoRendering::SoMath::EqualWithEpsilon(soMat(1, 0), rayMat.m1) &&
				SoRendering::SoMath::EqualWithEpsilon(soMat(2, 0), rayMat.m2) &&
				SoRendering::SoMath::EqualWithEpsilon(soMat(3, 0), rayMat.m3) &&
				SoRendering::SoMath::EqualWithEpsilon(soMat(0, 1), rayMat.m4) &&
				SoRendering::SoMath::EqualWithEpsilon(soMat(1, 1), rayMat.m5) &&
				SoRendering::SoMath::EqualWithEpsilon(soMat(2, 1), rayMat.m6) &&
				SoRendering::SoMath::EqualWithEpsilon(soMat(3, 1), rayMat.m7) &&
				SoRendering::SoMath::EqualWithEpsilon(soMat(0, 2), rayMat.m8) &&
				SoRendering::SoMath::EqualWithEpsilon(soMat(1, 2), rayMat.m9) &&
				SoRendering::SoMath::EqualWithEpsilon(soMat(2, 2), rayMat.m10) &&
				SoRendering::SoMath::EqualWithEpsilon(soMat(3, 2), rayMat.m11) &&
				SoRendering::SoMath::EqualWithEpsilon(soMat(0, 3), rayMat.m12) &&
				SoRendering::SoMath::EqualWithEpsilon(soMat(1, 3), rayMat.m13) &&
				SoRendering::SoMath::EqualWithEpsilon(soMat(2, 3), rayMat.m14) &&
				SoRendering::SoMath::EqualWithEpsilon(soMat(3, 3), rayMat.m15);
		}


		TEST_METHOD(TranslationTest)
		{
			SoRendering::SoTransform soTrans;
			Matrix rayTrans;

			soTrans.SetPosition(SoRendering::SoVector3f(0.3f, 88.0f, 99.0f));
			rayTrans = MatrixTranslate(0.3f, 88.0f, 99.0f);
			Assert::IsTrue(MatrixCompare(rayTrans, soTrans.GetMatrix()));

			soTrans.SetPosition(SoRendering::SoVector3f(-10.3f, 9999.0f, -1999.0f));
			rayTrans = MatrixTranslate(-10.3f, 9999.0f, -1999.0f);
			Assert::IsTrue(MatrixCompare(rayTrans, soTrans.GetMatrix()));

			soTrans.SetPosition(SoRendering::SoVector3f(-0.005f, -7888.0f, 345.0f));
			rayTrans = MatrixTranslate(-0.005f, -7888.0f, 345.0f);
			Assert::IsTrue(MatrixCompare(rayTrans, soTrans.GetMatrix()));
		}

		TEST_METHOD(ScaleTest)
		{
			SoRendering::SoTransform soScale;
			Matrix rayScale;

			soScale.SetScale(SoRendering::SoVector3f(767.f, 12.0f, -909.0f));
			rayScale = MatrixScale(767.f, 12.0f, -909.0f);
			Assert::IsTrue(MatrixCompare(rayScale, soScale.GetMatrix()));

			soScale.SetScale(SoRendering::SoVector3f(46.f, -36.f, 882.0f));
			rayScale = MatrixScale(46.f, -36.f, 882.0f);
			Assert::IsTrue(MatrixCompare(rayScale, soScale.GetMatrix()));

			soScale.SetScale(SoRendering::SoVector3f(-23.f, 332.0f, 0.012f));
			rayScale = MatrixScale(-23.f, 332.0f, 0.012f);
			Assert::IsTrue(MatrixCompare(rayScale, soScale.GetMatrix()));
		}

		TEST_METHOD(RotateTest)
		{
			SoRendering::SoTransform soRotate;
			Matrix rayRotate;
			const Vector3 rayTestPoint = {0.f, 0.f, 1.f};
			const SoRendering::SoVector4f soTestPoint = SoRendering::SoVector4f(0.f, 0.f, 1.f, 0.f);

			soRotate.SetRotation(SoRendering::SoMath::GetQuaternionFromEulerAngle
				(SoRendering::SoVector3f(
					SoRendering::SO_DEG2RAD * 60.f,
					SoRendering::SO_DEG2RAD * 60.f,
					SoRendering::SO_DEG2RAD * 60.f)));
			rayRotate = QuaternionToMatrix(QuaternionFromEuler(DEG2RAD * 60.f, DEG2RAD * 60.f, DEG2RAD * 60.f));
			Assert::IsTrue(Vector3Compare(Vector3Transform(rayTestPoint, rayRotate), (soRotate.GetMatrix() * soTestPoint).head<3>()));


			soRotate.SetRotation(SoRendering::SoMath::GetQuaternionFromEulerAngle
			(SoRendering::SoVector3f(
				SoRendering::SO_DEG2RAD * 30.f,
				SoRendering::SO_DEG2RAD * 20.f,
				SoRendering::SO_DEG2RAD * 0.f)));
			rayRotate = QuaternionToMatrix(QuaternionFromEuler(DEG2RAD * 30.f, DEG2RAD * 20.f, DEG2RAD * 0.f));
			Assert::IsTrue(Vector3Compare(Vector3Transform(rayTestPoint, rayRotate), (soRotate.GetMatrix() * soTestPoint).head<3>()));


			soRotate.SetRotation(SoRendering::SoMath::GetQuaternionFromEulerAngle
			(SoRendering::SoVector3f(
				SoRendering::SO_DEG2RAD * -90.f,
				SoRendering::SO_DEG2RAD * 600.f,
				SoRendering::SO_DEG2RAD * 1000.f)));
			rayRotate = QuaternionToMatrix(QuaternionFromEuler(DEG2RAD * -90.f, DEG2RAD * 600.f, DEG2RAD * 1000.f));
			Assert::IsTrue(Vector3Compare(Vector3Transform(rayTestPoint, rayRotate), (soRotate.GetMatrix() * soTestPoint).head<3>()));

		}

		TEST_METHOD(TranformTest)
		{
			SoRendering::SoTransform soTransform;
			Matrix rayTrans;
			Matrix rayRotate;
			Matrix rayScale;
			
			const Vector3 rayTestPoint = { 0.f, 0.f, 1.f };
			const SoRendering::SoVector4f soTestPoint = SoRendering::SoVector4f(0.f, 0.f, 1.f, 1.f);
			Vector3 rayVec3;
			SoRendering::SoVector3f soVec3;

			soTransform.SetPosition(SoRendering::SoVector3f(0.3f, 88.0f, 99.0f));
			soTransform.SetRotation(SoRendering::SoMath::GetQuaternionFromEulerAngle
			(SoRendering::SoVector3f(
				SoRendering::SO_DEG2RAD * 60.f,
				SoRendering::SO_DEG2RAD * 60.f,
				SoRendering::SO_DEG2RAD * 60.f)));
			soTransform.SetScale(SoRendering::SoVector3f(767.f, 12.0f, -909.0f));
			rayTrans = MatrixTranslate(0.3f, 88.0f, 99.0f);
			rayRotate = QuaternionToMatrix(QuaternionFromEuler(DEG2RAD * 60.f, DEG2RAD * 60.f, DEG2RAD * 60.f));
			 rayScale = MatrixScale(767.f, 12.0f, -909.0f);
			rayVec3 = Vector3Transform(Vector3Transform(Vector3Transform(rayTestPoint, rayScale), rayRotate), rayTrans);
			soVec3 = (soTransform.GetMatrix() * soTestPoint).head<3>();
			Assert::IsTrue(Vector3Compare(rayVec3, soVec3));


			soTransform.SetPosition(SoRendering::SoVector3f(99.f, 12.0f, 33.0f));
			soTransform.SetRotation(SoRendering::SoMath::GetQuaternionFromEulerAngle
			(SoRendering::SoVector3f(
				SoRendering::SO_DEG2RAD * 0.2f,
				SoRendering::SO_DEG2RAD * 900.f,
				SoRendering::SO_DEG2RAD * -30.f)));
			soTransform.SetScale(SoRendering::SoVector3f(1.f, 100.0f, -8.8f));
			rayTrans = MatrixTranslate(99.f, 12.0f, 33.0f);
			rayRotate = QuaternionToMatrix(QuaternionFromEuler(DEG2RAD * 0.2f, DEG2RAD * 900.f, DEG2RAD * -30.f));
			rayScale = MatrixScale(1, 100.0f, -8.8f);
			rayVec3 = Vector3Transform(Vector3Transform(Vector3Transform(rayTestPoint, rayScale), rayRotate), rayTrans);
			soVec3 = (soTransform.GetMatrix() * soTestPoint).head<3>();
			Assert::IsTrue(Vector3Compare(rayVec3, soVec3));
		}


		TEST_METHOD(QuaternionEulerAngleTransTest)
		{
			//From Quaternion to Euler Angle
			SoRendering::SoQuaternion soQuat;
			Quaternion rayQuat;
			SoRendering::SoVector3f soAngle;
			Vector3 rayAngle;

			rayQuat = { 0.1968829f, 0.4331424f, 0.7875317f, 0.3916868f };
			soQuat= SoRendering::SoQuaternion(0.1968829f, 0.4331424f, 0.7875317f, 0.3916868f);
			rayAngle = QuaternionToEuler(rayQuat);
			soAngle = SoRendering::SoMath::GetEulerAngleFromQuaternion(soQuat);
			Assert::IsTrue(Vector3Compare(rayAngle, soAngle));


			rayQuat = { -0.5202704f, -0.3267298f, -0.6243245f, -0.4824782f };
			soQuat = SoRendering::SoQuaternion(-0.5202704f, -0.3267298f, -0.6243245f, -0.4824782f);
			rayAngle = QuaternionToEuler(rayQuat);
			soAngle = SoRendering::SoMath::GetEulerAngleFromQuaternion(soQuat);
			Assert::IsTrue(Vector3Compare(rayAngle, soAngle));

			rayQuat = { 0.5588597f, 0.7451462f, -0.3104776f, 0.1898333f };
			soQuat = SoRendering::SoQuaternion(0.5588597f, 0.7451462f, -0.3104776f, 0.1898333f);
			rayAngle = QuaternionToEuler(rayQuat);
			soAngle = SoRendering::SoMath::GetEulerAngleFromQuaternion(soQuat);
			Assert::IsTrue(Vector3Compare(rayAngle, soAngle));
			//From Euler Angle to Quaternion
			

			rayAngle = {DEG2RAD * 60.f, DEG2RAD * 30.f, DEG2RAD * 120.f};
			soAngle = SoRendering::SoVector3f(SoRendering::SO_DEG2RAD * 60.f, SoRendering::SO_DEG2RAD * 30.f, SoRendering::SO_DEG2RAD * 120.f);
			rayQuat = QuaternionFromEuler(rayAngle.x, rayAngle.y, rayAngle.z);
			soQuat = SoRendering::SoMath::GetQuaternionFromEulerAngle(soAngle);
			Assert::IsTrue(QuatCompare(rayQuat, soQuat));

			rayAngle = { DEG2RAD * -120.f, DEG2RAD * 0.f, DEG2RAD * 2000.f };
			soAngle = SoRendering::SoVector3f(SoRendering::SO_DEG2RAD * -120.f, SoRendering::SO_DEG2RAD * 0.f, SoRendering::SO_DEG2RAD * 2000.f);
			rayQuat = QuaternionFromEuler(rayAngle.x, rayAngle.y, rayAngle.z);
			soQuat = SoRendering::SoMath::GetQuaternionFromEulerAngle(soAngle);
			Assert::IsTrue(QuatCompare(rayQuat, soQuat));

			rayAngle = { DEG2RAD * -1.f, DEG2RAD * 0.5f, DEG2RAD * -99.8f };
			soAngle = SoRendering::SoVector3f(SoRendering::SO_DEG2RAD * -1.f, SoRendering::SO_DEG2RAD * 0.5f, SoRendering::SO_DEG2RAD * -99.8f);
			rayQuat = QuaternionFromEuler(rayAngle.x, rayAngle.y, rayAngle.z);
			soQuat = SoRendering::SoMath::GetQuaternionFromEulerAngle(soAngle);
			Assert::IsTrue(QuatCompare(rayQuat, soQuat));
		}

	};
}
